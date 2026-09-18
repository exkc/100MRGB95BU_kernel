
#include <mali_kbase.h>
#include <device/mali_kbase_device.h>

#include <linux/proc_fs.h>
#include <linux/seq_file.h>

int get_gpu_total_memory (void);
int get_gpu_total_memory (void)
{
	struct list_head *entry;
	const struct list_head *kbdev_list;
	int gpu_memory = 0;

	kbdev_list = kbase_device_get_list();
	list_for_each(entry, kbdev_list) {
		struct kbase_device *kbdev = NULL;
		struct kbase_context *kctx_element;

		kbdev = list_entry(entry, struct kbase_device, entry);

		mutex_lock(&kbdev->kctx_list_lock);
		list_for_each_entry(kctx_element, &kbdev->kctx_list, kctx_list_link) {
			/* output the memory usage and cap for each kctx
			 * opened on this device */
			gpu_memory += atomic_read(&(kctx_element->used_pages));
		}
		mutex_unlock(&kbdev->kctx_list_lock);
	}
	kbase_device_put_list(kbdev_list);

	return gpu_memory;
}

int get_gpu_cached_memory (void);
int get_gpu_cached_memory (void)
{
	return 0;
}

int get_gpu_pool_memory (void);
int get_gpu_pool_memory (void)
{
	struct list_head *entry;
	const struct list_head *kbdev_list;
	int pool_memory = 0;

	kbdev_list = kbase_device_get_list();
	list_for_each(entry, kbdev_list) {
		struct kbase_device *kbdev = NULL;
		struct kbase_context *kctx_element;
		int gid=0;

		kbdev = list_entry(entry, struct kbase_device, entry);
		mutex_lock(&kbdev->kctx_list_lock);
		list_for_each_entry(kctx_element, &kbdev->kctx_list, kctx_list_link) {
			for (gid = 0; gid < MEMORY_GROUP_MANAGER_NR_GROUPS; ++gid) {
				pool_memory += kbase_mem_pool_size(&(kctx_element->mem_pools.small[gid]));
				pool_memory += kbase_mem_pool_size(&(kctx_element->mem_pools.large[gid]));
			}
		}
		mutex_unlock(&kbdev->kctx_list_lock);
	}
	kbase_device_put_list(kbdev_list);

	return (pool_memory);
}

static int get_gpu_memory (pid_t client_tgid)
{
	struct list_head *entry;
	const struct list_head *kbdev_list;
	unsigned int gpu_memory = 0 ;

	kbdev_list = kbase_device_get_list();
	list_for_each(entry, kbdev_list) {
		struct kbase_device *kbdev = NULL;
		struct kbase_context *kctx_element;

		kbdev = list_entry(entry, struct kbase_device, entry);

		mutex_lock(&kbdev->kctx_list_lock);
		list_for_each_entry(kctx_element, &kbdev->kctx_list, kctx_list_link) {
			if(kctx_element->tgid == client_tgid)
				gpu_memory += atomic_read(&(kctx_element->used_pages));
		}
		mutex_unlock(&kbdev->kctx_list_lock);
	}
	kbase_device_put_list(kbdev_list);

	return gpu_memory;
}

static int gpu_show(struct seq_file *sfile, void *data)
{
	pid_t tgid = (unsigned long)sfile->private;

	seq_printf(sfile, "%d\n", get_gpu_memory(tgid));
	return 0;
}

static int um_show(struct seq_file *sfile, void *data)
{
	extern int lgext_dma_buf_te_memory(pid_t tgid);
	pid_t tgid = (unsigned long)sfile->private;

	seq_printf(sfile, "%d\n", lgext_dma_buf_te_memory(tgid));
	return 0;
}

static unsigned int kbase_kctx_count(pid_t client_tgid)
{
	unsigned int count = 0;
	struct list_head *entry;
	const struct list_head *kbdev_list;

	kbdev_list = kbase_device_get_list();
	list_for_each(entry, kbdev_list) {
		struct kbase_device *kbdev = NULL;
		struct kbase_context *kctx_element;

		kbdev = list_entry(entry, struct kbase_device, entry);

		mutex_lock(&kbdev->kctx_list_lock);
		list_for_each_entry(kctx_element, &kbdev->kctx_list, kctx_list_link) {
			if(kctx_element->tgid == client_tgid)
				count ++;
		}
		mutex_unlock(&kbdev->kctx_list_lock);
	}
	kbase_device_put_list(kbdev_list);

	return count;
}

// thread safe...
//
// 두개 이상의 kctx 가 동시에 device 의 kctx_list 에 추가되는 경우,
// kbase_kctx_count() 함수가 2를 리턴할 수 있다. 이런경우 /proc/{gpu,um}/
// 디렉토리에 tgid 파일이 만들저지지 않을 수 있다.
//
// 같은 이유로, 두개 이상의 kctx 가 여러 thread 에서 한번에 삭제될 때,
// /proc/{gpu,um}/ 디렉토리의 tgid 파일이 삭제되지 않을 수 있다.
//
// 이 문제를 해결하려면 mali_kbase_core_linux.c 파일을 수정해야 하는데, 빈번한
// 문제도 아니며, 심각한 문제가 생기지도 않아, 그냥 현상태로 사용한다.
int kbase_lgsic_ext_profile_insert(struct kbase_context *kctx, struct kbase_device *kbdev);
int kbase_lgsic_ext_profile_insert(struct kbase_context *kctx, struct kbase_device *kbdev)
{
	unsigned int count = kbase_kctx_count(kctx->tgid);

	WARN_ON_ONCE(count == 0);
	if (count == 1)
	{
		char fname[64];

		snprintf(fname, sizeof(fname), "%d", kctx->tgid);

		if (kbdev->lgext_gpu_directory)
			proc_create_single_data(fname, 0444,
					kbdev->lgext_gpu_directory,
					gpu_show,
					(void*)(long)kctx->tgid);

		if (kbdev->lgext_um_directory)
			proc_create_single_data(fname, 0444,
					kbdev->lgext_um_directory,
					um_show,
					(void*)(long)kctx->tgid);
	}

	return 0;
}

void kbase_lgsic_profile_remove(struct kbase_context *kctx, struct kbase_device *kbdev);
void kbase_lgsic_profile_remove(struct kbase_context *kctx, struct kbase_device *kbdev)
{
	if (kbase_kctx_count(kctx->tgid) == 1)
	{
		char fname[64];

		snprintf(fname, sizeof(fname), "%d", kctx->tgid);
		if (kbdev->lgext_gpu_directory)
			remove_proc_entry(fname, kbdev->lgext_gpu_directory);
		if (kbdev->lgext_um_directory)
			remove_proc_entry(fname, kbdev->lgext_um_directory);
	}
}
