// SPDX-License-Identifier: GPL-2.0-only
/*
 * Built-in Kdump
 *
 * Copyright (C) 2024 LG Electronics
 *
 * Author : Jaehyun Kim <jehn.kim@lge.com>
 */

#include <linux/fs.h>
#include <linux/mount.h>
#include <uapi/linux/mount.h>
#include <linux/namei.h>
#include <linux/fs_struct.h>
#include "../../init/do_mounts.h"
#include <linux/net.h>
#include <linux/inet.h>
#include <linux/in.h>
#include <linux/socket.h>
#include <linux/netdevice.h>
#include <linux/rtnetlink.h>


#define FTPCMD_BUFSZ	1024
// To do: buffer size optimization
#define FILESND_BUFSZ	PAGE_SIZE * 2
#define SRC_FILE	"/proc/vmcore"
#define DST_FILE	"/mnt/vmcore"
#define INTERFACE_NAME	"eth0"
#define EMPTY_FILE	".dummy4kdump.tmp"

static DECLARE_COMPLETION(kdump_done);

static struct task_struct *usb_thread;
static struct task_struct *ftp_thread;

#define MAX_LEN	128
static char FTP_HOST[MAX_LEN], FTP_USER[MAX_LEN];
static char FTP_PASS[MAX_LEN], FTP_PATH[MAX_LEN];

static char mac_str[13];

static int is_ftp = 0;	// 0: USB, 1: FTP

/* ftp=user:pass@address/path/to */
static int __init get_ftp_account(char *str)
{
	int ret;

	if (!str)
		return -EINVAL;

	is_ftp = 1;

	ret = sscanf(str, "%49[^:]:%49[^@]@%49[^/]/%99s",
		FTP_USER, FTP_PASS, FTP_HOST, FTP_PATH);

	if (ret == 4) {
        int len = strlen(FTP_PATH);
        if (FTP_PATH[len - 1] != '/') {
            if (len < sizeof(FTP_PATH) - 1) {
                FTP_PATH[len] = '/';
                FTP_PATH[len + 1] = '\0';
            }
        }
	} else if (ret == 3) {
		FTP_PATH[0] = '\0';
	}

	return 1;
}
__setup("ftp=", get_ftp_account);

static int get_mac_address(void)
{
	struct net_device *dev;
	unsigned char *mac;

	dev = dev_get_by_name(&init_net, INTERFACE_NAME);
	if (!dev) {
		pr_err("kdump: failed to find device: %s\n", INTERFACE_NAME);
		return -ENODEV;
	}

	mac = dev->dev_addr;

	snprintf(mac_str, sizeof(mac_str), "%02X%02X%02X%02X%02X%02X",
		 mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	pr_info("kdump: MAC address of %s is %s\n", INTERFACE_NAME, mac_str);

	dev_put(dev);

	return 0;
}

static void avoid_collision(char *file_path)
{
	struct file *dest_file;
	int i = 0;

	snprintf(file_path, MAX_LEN, "%s-%s", DST_FILE, mac_str);

	dest_file = filp_open(file_path, O_WRONLY | O_CREAT | O_LARGEFILE | O_EXCL, 0644);

	while (IS_ERR(dest_file) && PTR_ERR(dest_file) == -EEXIST) {
		snprintf(file_path, MAX_LEN, "%s-%s(%d)", DST_FILE, mac_str, ++i);
		dest_file = filp_open(file_path, O_WRONLY | O_CREAT | O_LARGEFILE | O_EXCL, 0644);
	}
	pr_info("kdump: filename is %s\n", file_path);
}

static int usb_copy_file(void)
{
	char *buf;
	char file_path[MAX_LEN];
	int copy_progress = 0, last_progress = 0;
	struct file *src_file, *dst_file;
	ssize_t bytes_read, bytes_written;
	loff_t src_size, src_offset = 0, dst_offset = 0;

	buf = kmalloc(FILESND_BUFSZ, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	src_file = filp_open(SRC_FILE, O_RDONLY, 0);
	if (IS_ERR(src_file)) {
		kfree(buf);
		return PTR_ERR(src_file);
	}

	avoid_collision(file_path);

	dst_file = filp_open(file_path, O_WRONLY | O_CREAT | O_LARGEFILE, 0644);
	if (IS_ERR(dst_file)) {
		filp_close(src_file, NULL);
		kfree(buf);
		return PTR_ERR(dst_file);
	}

	src_size = src_file->f_inode->i_size;

	while ((bytes_read = vfs_read(src_file, buf, FILESND_BUFSZ, &src_offset)) > 0) {
		bytes_written = vfs_write(dst_file, buf, bytes_read, &dst_offset);

		copy_progress = (int)(src_offset * 100 / src_size);

		if (copy_progress % 10 == 0 && copy_progress != last_progress) {
			printk("kdump: copy progress: %d%%\n", copy_progress);
			last_progress = copy_progress;
		}

		if (bytes_written < 0) {
			printk("kdump: copy progress: 100%%\n");
			break;
		}
	}

	filp_close(src_file, NULL);
	filp_close(dst_file, NULL);
	kfree(buf);

	return 0;
}

static int vmcore_to_usb(void *data)
{
	int ret;
	struct path path;
	struct vfsmount *vfsmnt;
	struct file_system_type *fs_type_vfat;
	struct file_system_type *fs_type_exfat;
	struct file_system_type *fs_type_ntfs;

	char *fs_type = "vfat";	// default fs type is vfat
	const char *devdir = "/dev/sda1";
	const char *mntdir = "/mnt";

	/* wait for probe usb device */
	pr_info("kdump: waiting for usb device created\n");

	while (!kthread_should_stop()) {
		ret = kern_path(devdir, LOOKUP_FOLLOW, &path);
		if (!ret) {
			pr_info("kdump: %s found\n", devdir);
			break;
		} else if (ret == -ENOENT) {
			pr_info("kdump: %s not found, retrying...\n", devdir);
		} else {
			pr_info("kdump: failed to find %s: %d\n", devdir, ret);
			return -1;
		}
		msleep(3000);
	}

	fs_type_vfat = get_fs_type("vfat");
	if (!fs_type_vfat) {
		pr_err("kdump: failed to get vfat type\n");
		return -1;
	}

	fs_type_exfat = get_fs_type("exfat");
	if (!fs_type_exfat) {
		pr_err("kdump: failed to get exfat type\n");
		return -1;
	}

	fs_type_ntfs = get_fs_type("ntfs");
	if (!fs_type_ntfs) {
		pr_err("kdump: failed to get ntfs type\n");
		return -1;
	}

	/* create mount point of /dev/sda1 */
	vfsmnt = vfs_kern_mount(fs_type_vfat, 0, devdir, NULL);
	if (IS_ERR(vfsmnt)) {
		pr_err("kdump: this is not vfat. try with exfat\n");

		vfsmnt = vfs_kern_mount(fs_type_exfat, 0, devdir, NULL);
		if (IS_ERR(vfsmnt)) {
			pr_err("kdump: this is not exfat. try with ntfs\n");

			vfsmnt = vfs_kern_mount(fs_type_ntfs, 0, devdir, NULL);
			if (IS_ERR(vfsmnt)) {
				pr_err("kdump: failed to mount ntfs filesystem\n");
				return PTR_ERR(vfsmnt);
			} else
				fs_type = "ntfs";
		} else
			fs_type = "exfat";
	}

	/* make directory /mnt */
	ret = init_mkdir(mntdir, 0755);
	if (ret < 0) {
		pr_err("kdump: failed to make dir %s: %d\n", mntdir, ret);
		return ret;
	}

	pr_info("kdump: %s make successfully\n", mntdir);

	/* mount /dev/sda1 to /mnt */
	ret = do_mount(devdir, mntdir, fs_type, MS_NOATIME, NULL);
	if (ret) {
		pr_err("kdump: failed to mount %s to %s: %d\n", devdir, mntdir, ret);
		return ret;
	}

	pr_info("kdump: %s to %s mounted\n", devdir, mntdir);
	pr_info("kdump: starting to copy vmcore...\n");

	if (usb_copy_file() < 0) {
		pr_err("kdump: failed to copy vmcore file: %d\n", ret);
		return -1;
	}

	kern_unmount(vfsmnt);

	pr_info("kdump: file send successfully\n");
	complete(&kdump_done);
	return 0;
}

static int check_network_ready(void)
{
	struct net_device *dev;
	int ready = 0;

	rtnl_lock();
	for_each_netdev(&init_net, dev) {
		if (netif_running(dev) && netif_carrier_ok(dev)) {
			ready = 1;
			break;
		}
	}
	rtnl_unlock();

	return ready;
}

static int ftp_send(struct socket *sock, char *data, size_t data_len)
{
	struct msghdr msg;
	struct kvec vec;
	int ret;

	memset(&msg, 0, sizeof(msg));
	vec.iov_base = data;
	vec.iov_len = data_len;

	ret = kernel_sendmsg(sock, &msg, &vec, 1, data_len);
	if (ret < 0)
		return ret;

	return 0;
}

static int ftp_recv(struct socket *sock, char *response)
{
	struct msghdr msg;
	struct kvec vec;
	int ret;

	memset(&msg, 0, sizeof(msg));
	vec.iov_base = response;
	vec.iov_len = FTPCMD_BUFSZ;

	ret = kernel_recvmsg(sock, &msg, &vec, 1, FTPCMD_BUFSZ, 0);
	if (ret < 0)
		return ret;

	response[ret] = '\0';

	return ret;
}

static int ftp_cmd(struct socket *sock, char *buffer, const char *cmd,
		   const char *arg, const char *expected_response)
{
	int ret;

	if (arg != NULL)
		snprintf(buffer, FTPCMD_BUFSZ, cmd, arg);
	else
		snprintf(buffer, FTPCMD_BUFSZ, "%s", cmd);

	ret = ftp_send(sock, buffer, strlen(buffer));
	if (ret < 0)
		return ret;
	pr_info("kdump: sendmsg: %s", buffer);

	ret = ftp_recv(sock, buffer);
	if (ret < 0)
		return ret;
	pr_info("kdump: recvmsg: %s", buffer);

	if (strncmp(buffer, expected_response, 3) != 0)
		return -EIO;

	return 0;
}

static int ftp_connect(struct socket **sock, __be32 s_addr, unsigned short port)
{
	struct sockaddr_in saddr;
	int ret;

	ret = sock_create_kern(&init_net, AF_INET,
			       SOCK_STREAM, IPPROTO_TCP, sock);
	if (ret < 0)
		return ret;

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = s_addr;
	saddr.sin_port = htons(port);

	ret = kernel_connect(*sock, (struct sockaddr *)&saddr, sizeof(saddr), 0);
	if (ret < 0) {
		sock_release(*sock);
		return ret;
	}

	return 0;
}

static int ftp_login(struct socket *sock, const char *ftp_user, const char *ftp_pass)
{
	char buffer[FTPCMD_BUFSZ];
	int ret;

	/* USER: send username of account */
	ret = ftp_cmd(sock, buffer, "USER %s\r\n", ftp_user, "331");
	if (ret < 0)
		return ret;

	/* PASS: send password */
	ret = ftp_cmd(sock, buffer, "PASS %s\r\n", ftp_pass, "230");
	if (ret < 0)
		return ret;

	return 0;
}

static int release_data_sock(struct socket *sock, struct socket *dsock)
{
	char buf[FTPCMD_BUFSZ];
	int ret;

	sock_release(dsock);

	ret = ftp_recv(sock, buf);
	if (ret < 0)
		return ret;

	pr_info("kdump: recvmsg: %s", buf);

	if (strncmp(buf, "226", 3) != 0)
		return -EIO;

	return 0;
}

static int ftp_dele_file(struct socket *sock)
{
	char buf[FTPCMD_BUFSZ];
	int ret;

	snprintf(buf, FTPCMD_BUFSZ, "DELE %s%s\r\n", FTP_PATH, EMPTY_FILE);

	ret = ftp_cmd(sock, buf, buf, NULL, "250");
	if (ret < 0)
		return ret;

	return 0;
}

static int ftp_send_empty_file(struct socket *sock)
{
	struct socket *data_sock;
	char buf[FTPCMD_BUFSZ];
	unsigned int h1, h2, h3, h4, p1, p2;
	unsigned int port;
	int ret;

	ret = ftp_cmd(sock, buf, "PASV\r\n", NULL, "227");
	if (ret < 0)
		return ret;

	sscanf(buf, "227 Entering Passive Mode (%u,%u,%u,%u,%u,%u)",
		&h1, &h2, &h3, &h4, &p1, &p2);

	port = (p1 * 256) + p2;

	ret = ftp_connect(&data_sock,
			  htonl((h1 << 24) | (h2 << 16) | (h3 << 8) | h4),
			  port);
	if (ret < 0)
		return ret;

	snprintf(buf, FTPCMD_BUFSZ, "STOR %s%s\r\n", FTP_PATH, EMPTY_FILE);

	ret = ftp_cmd(sock, buf, buf, NULL, "150");
	if (ret < 0)
		return ret;

	release_data_sock(sock, data_sock);

	return 0;
}

static int ftp_get_timestamp(struct socket *sock, char *timestamp)
{
	char buf[FTPCMD_BUFSZ];
	int ret;

	snprintf(buf, FTPCMD_BUFSZ, "MDTM %s%s\r\n", FTP_PATH, EMPTY_FILE);

	ret = ftp_cmd(sock, buf, buf, NULL, "213");
	if (ret < 0)
		return ret;

	sscanf(buf, "213 %s", timestamp);

	return 0;
}

static int ftp_send_file(struct socket *ctrl_sock)
{
	char cmdbuf[FTPCMD_BUFSZ];
	char *filebuf;
	struct socket *data_sock;
	struct file *file;
	loff_t file_size, file_offset = 0;
	size_t bytes_read;
	long total_sent = 0;
	long next_report;
	unsigned int h1, h2, h3, h4, p1, p2;
	unsigned int data_port;
	int ret;

	char timestamp[20] = {0};

	/* get server's timestamp */
	ret = ftp_send_empty_file(ctrl_sock);
	if (ret)
		return ret;

	ret = ftp_get_timestamp(ctrl_sock, timestamp);
	if (ret)
		return ret;

	ret = ftp_dele_file(ctrl_sock);
	if (ret)
		return ret;

	/* TYPE I: set binary mode */
	ret = ftp_cmd(ctrl_sock, cmdbuf, "TYPE I\r\n", NULL, "200");
	if (ret < 0)
		return ret;

	/* MKD: make directory. deprecated. */
	//ftp_cmd(ctrl_sock, cmdbuf, "MKD %s\r\n", dst_path, "257");

	/* PASV: request data socket info */
	ret = ftp_cmd(ctrl_sock, cmdbuf, "PASV\r\n", NULL, "227");
	if (ret < 0)
		return ret;

	sscanf(cmdbuf, "227 Entering Passive Mode (%u,%u,%u,%u,%u,%u)",
		&h1, &h2, &h3, &h4, &p1, &p2);

	data_port = (p1 * 256) + p2;

	pr_info("kdump: parsed PASV ip: %u.%u.%u.%u, port: %u\n",
		h1, h2, h3, h4, data_port);

	/* create data socket */
	pr_info("kdump: try to connect with data socket\n");
	ret = ftp_connect(&data_sock,
			  htonl((h1 << 24) | (h2 << 16) | (h3 << 8) | h4),
			  data_port);
	if (ret < 0) {
		pr_err("kdump: failed to connect data socket: %d\n", ret);
		return ret;
	}

	/*
	 * STOR: store file to remote server
	 * filename format is vmcore-[mac]-[time].
	 */
	snprintf(cmdbuf, FTPCMD_BUFSZ, "STOR %svmcore-%s-%s\r\n",
		 FTP_PATH, mac_str, timestamp);
	ret = ftp_cmd(ctrl_sock, cmdbuf, cmdbuf, NULL, "150");
	if (ret < 0)
		return ret;

	file = filp_open(SRC_FILE, O_RDONLY, 0);
	if (IS_ERR(file)) {
		pr_err("kdump: failed to open file: %ld\n", PTR_ERR(file));
		return PTR_ERR(file);
	}

	filebuf = kmalloc(FILESND_BUFSZ, GFP_KERNEL);
	if (!filebuf) {
		filp_close(file, NULL);
		return -ENOMEM;
	}

	file_size = file->f_inode->i_size;

	pr_info("kdump: file(size:%ld) transfer starting...\n", (long int)file_size);

	/* send vmcore file */
	next_report = file_size / 10;

	while ((bytes_read = vfs_read(file, filebuf, FILESND_BUFSZ, &file_offset)) > 0) {
		ret = ftp_send(data_sock, filebuf, bytes_read);
		if (ret < 0)
			pr_err("kdump: failed to send file\n");

		total_sent += bytes_read;

		if (total_sent >= next_report) {
			pr_info("kdump: progress %d%%\n",
				(int)(total_sent * 100 / file_size));
			next_report += file_size / 10;
		}
	}

	release_data_sock(ctrl_sock, data_sock);

	/*
	 * QUIT: close ftp connection.
	 * Sometimes there is no response due to closing.
	 */
	ftp_cmd(ctrl_sock, cmdbuf, "QUIT\r\n", NULL, "221");

	kfree(filebuf);
	filp_close(file, NULL);

	return 0;
}

static int vmcore_to_ftp(void *data)
{
	/* The default port for ftp is 21. */
	unsigned short ftp_port = 21;
	struct socket *ctrl_sock = NULL;
	char cmdbuf[FTPCMD_BUFSZ];
	int ret;

	while (true) {
		if (check_network_ready()) {
			pr_info("kdump: network ready\n");
			break;
		}
		pr_info("kdump: waiting for network ready...\n");
		msleep(1000);
	}

	pr_info("kdump: try to connect with FTP server\n");
	pr_info("kdump: host=%s, path=%s, user=%s, password=%s\n",
		FTP_HOST, FTP_PATH, FTP_USER, FTP_PASS);

	if (FTP_HOST[0] == '\0') {
		pr_err("kdump: failed to get FTP server info\n");
		ret = -EINVAL;
		goto out_thread;
	}

	/* create control socket */
	ret = ftp_connect(&ctrl_sock, in_aton(FTP_HOST), ftp_port);
	if (ret < 0) {
		pr_err("kdump: failed to connect control socket: %d\n", ret);
		goto out_sock;
	}

	ret = ftp_recv(ctrl_sock, cmdbuf);
	if (ret < 0) {
		pr_err("kdump: failed to receive: %d\n", ret);
		goto out_sock;
	}

	if (strncmp(cmdbuf, "220", 3) != 0) {
		pr_err("kdump: failed to receive welcome message\n");
		ret = -EIO;
		goto out_sock;
	}

	pr_info("kdump: recv welcome msg: %s", cmdbuf);

	ret = ftp_login(ctrl_sock, FTP_USER, FTP_PASS);
	if (ret < 0) {
		pr_err("kdump: failed to login: %d\n", ret);
		goto out_sock;
	}

	ret = ftp_send_file(ctrl_sock);
	if (ret < 0) {
		pr_err("kdump: failed to send file: %d\n", ret);
		goto out_sock;
	}

out_sock:
	sock_release(ctrl_sock);
out_thread:
	complete(&kdump_done);
	if (ret)
		return ret;
	else
		return 0;
}

static int lg1k_crash_dump(void)
{
	int ret;
	const char *proc = "proc";
	struct path path;

	/* devfs mount */
	devtmpfs_mount();
	do_mount(".", "/", NULL, MS_MOVE, NULL);
	init_chroot(".");

	/* procfs mount */
	ret = init_mkdir(proc, 0755);
	if (ret < 0) {
		pr_err("kdump: faile to mkdir /%s: %d\n", proc, ret);
		return ret;
	}

	ret = do_mount(proc, proc, proc, MS_SILENT, NULL);
	if (ret) {
		pr_err("kdump: failed to mount %s: %d\n", proc, ret);
		return ret;
	}

	pr_info("kdump: procfs: mounted\n");

	/* check existing of vmcore file */
	if (kern_path(SRC_FILE, LOOKUP_FOLLOW, &path)) {
		pr_err("kdump: failed to get path for vmcore\n");
		return -ENOENT;
	}

	pr_info("kdump: %s file found\n", SRC_FILE);

	get_mac_address();

	/*
	 * Default is USB copy.
	 * However, if 'ftp=' is set, it'll do ftp transfer.
	 */
	if (is_ftp) {
		ftp_thread = kthread_run(vmcore_to_ftp, NULL, "kdump-ftp");
		if (IS_ERR(vmcore_to_ftp)) {
			pr_err("kdump: failed to create kthread: %ld\n",
				PTR_ERR(vmcore_to_ftp));
			return -1;
		}
	} else {
		usb_thread = kthread_run(vmcore_to_usb, NULL, "kdump-usb");
		if (IS_ERR(vmcore_to_usb)) {
			pr_err("kdump: failed to create kthread: %ld\n",
				PTR_ERR(vmcore_to_usb));
			return -1;
		}
	}

	wait_for_completion(&kdump_done);

	pr_info("kdump: operation complete\n");
	//kernel_restart(NULL);

	return 0;
}

static int lg1k_kmo_init(void)
{
	pr_info("kdump: registered to kmo\n");
	return register_kernel_mode_init(lg1k_crash_dump);
}
subsys_initcall(lg1k_kmo_init);
