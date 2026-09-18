#!/bin/bash
#
#
#
#

function template()
{
	case $1 in
		suspend)
			# do something
			;;
		resume)
			# do something
			;;
		status)
			;;
	esac
}

#------------------------------------------------------------------------------
# 각 모듈별로 suspend, resume 을 구현합니다.
#------------------------------------------------------------------------------
function cpu()
{
	case $1 in
		suspend)
			echo 0 > /proc/lg/pm/governor
			echo 0 > /sys/devices/system/cpu/cpu3/online
			echo 0 > /sys/devices/system/cpu/cpu2/online
			echo 0 > /sys/devices/system/cpu/cpu1/online
			echo 1050 > /proc/lg/pm/frequency
			;;
		resume)
			echo 1400 > /proc/lg/pm/frequency
			echo 1 > /sys/devices/system/cpu/cpu3/online
			echo 1 > /sys/devices/system/cpu/cpu2/online
			echo 1 > /sys/devices/system/cpu/cpu1/online
			echo 1 > /proc/lg/pm/governor
			;;
		status)
			;;
	esac
}

function gfx()
{
	case $1 in
		suspend)
			echo 0 > /sys/module/lg1k/parameters/gfx_safe_runtime_pm
			echo runtime_suspend > /proc/lg/gfx/pm_test
			;;
		resume)
			echo runtime_resume > /proc/lg/gfx/pm_test
			;;
		status)
			;;
	esac
}

function fbdev()
{
	case $1 in
		suspend)
			echo 0 0 > /proc/lg/fbdev/viewctrl
			echo auto > /sys/devices/platform/lg1k-fb/power/control
			;;
		resume)
			echo on > /sys/devices/platform/lg1k-fb/power/control
			echo 0 1 > /proc/lg/fbdev/viewctrl
			;;
		status)
			;;
	esac
}

function v4l2_avd()
{
	case $1 in
		suspend)
			;;
		resume)
			;;
		status)
			;;
	esac
}

function v4l2_vbi()
{
	case $1 in
		suspend)
			;;
		resume)
			;;
		status)
			;;
	esac
}

function v4l2_dolby()
{
	case $1 in
		suspend)
			;;
		resume)
			;;
		status)
			;;
	esac
}

function hdmi20_v4l2()
{
	case $1 in
		suspend)
			echo 0 95 1 > /proc/lg/hdmi20/command
			echo 1 95 1 > /proc/lg/hdmi20/command
			echo 2 95 1 > /proc/lg/hdmi20/command
			echo 3 95 1 > /proc/lg/hdmi20/command
			;;
		resume)
			echo 0 95 0 > /proc/lg/hdmi20/command
			echo 1 95 0 > /proc/lg/hdmi20/command
			echo 2 95 0 > /proc/lg/hdmi20/command
			echo 3 95 0 > /proc/lg/hdmi20/command
			;;
		status)
			;;
	esac
}

function v4l2_gps()
{
	case $1 in
		suspend)
			echo gps_runtime_suspend > /proc/lg/de/pm_test
			;;
		resume)
			echo gps_runtime_resume > /proc/lg/de/pm_test
			;;
		status)
			;;
	esac
}

function v4l2_lgsr()
{
	case $1 in
		suspend)
			echo lgsr_runtime_suspend > /proc/lg/pe/pm_test
			;;
		resume)
			echo lgsr_runtime_resume > /proc/lg/pe/pm_test
			;;
		status)
			;;
	esac
}

function v4l2_vbe()
{
	case $1 in
		suspend)
			echo runtime_suspend > /proc/lg/be/pm_test
			;;
		resume)
			echo runtime_resume > /proc/lg/be/pm_test
			;;
		status)
			;;
	esac
}

function v4l2_vpq()
{
	case $1 in
		suspend)
			echo runtime_suspend > /proc/lg/pe/pm_test
			;;
		resume)
			echo runtime_resume > /proc/lg/pe/pm_test
			;;
		status)
			;;
	esac
}


function v4l2_vsc()
{
	case $1 in
		suspend)
			echo runtime_suspend > /proc/lg/de/pm_test
			;;
		resume)
			echo runtime_resume > /proc/lg/de/pm_test
			;;
		status)
			;;
	esac
}

function v4l2_vt()
{
	case $1 in
		suspend)
			echo vt_runtime_suspend > /proc/lg/de/pm_test
			;;
		resume)
			echo vt_runtime_resume > /proc/lg/de/pm_test
			;;
		status)
			;;
	esac
}

function lg1k_te()
{
	case $1 in
		suspend)
			echo 1 > /proc/te/clock_gate
			;;
		resume)
			echo 0 > /proc/te/clock_gate
			;;
		status)
			;;
	esac
}

function venc()
{
	case $1 in
		suspend)
			echo runtime_suspend > /proc/lxvenc/pm_test
			;;
		resume)
			echo runtime_resume > /proc/lxvenc/pm_test
			;;
		status)
			;;
	esac
}

function demod()
{
	case $1 in
		suspend)
			echo 1 > /proc/lg/demod/power_save
			;;
		resume)
			echo 0 > /proc/lg/demod/power_save
			;;
		status)
			;;
	esac
}

function display()
{
	case $1 in
		suspend)
			echo channelpower 0 > /proc/lg/ovi/dbg_func
			;;
		resume)
			echo channelpower 1 > /proc/lg/ovi/dbg_func
			;;
		status)
			;;
	esac
}

function sys()
{
	case $1 in
		suspend)
			echo auto > /sys/devices/platform/lg1k-sys/power/control
			;;
		resume)
			echo on > /sys/devices/platform/lg1k-sys/power/control
			;;
		status)
			;;
	esac
}

#------------------------------------------------------------------------------
function action()
{
	echo "<!> $1 $2 ..." > /dev/lg/logm0
	$2 $1
}

# https://askubuntu.com/questions/623933/how-to-create-a-rotation-animation-using-shell-script
spinner()
{
    local i sp n
    sp='/-\|'
    n=${#sp}
    printf ' '
    while sleep 0.1; do
        printf "%s\b" "${sp:i++%n:1}"
    done
}

case $1 in
	suspend)
		echo "++ suspend device ++"
		action suspend cpu
		action suspend gfx
		action suspend fbdev
		action suspend v4l2_avd
		action suspend v4l2_vbi
		action suspend v4l2_dolby
		action suspend hdmi20_v4l2
		action suspend v4l2_gps
		action suspend v4l2_lgsr
		action suspend v4l2_vbe
		action suspend v4l2_vpq
		action suspend v4l2_vsc
		action suspend v4l2_vt
		action suspend lg1k_te
		action suspend venc
		action suspend demod
		action suspend display
		action suspend sys
		;;

	resume)
		echo "++ resume device ++"
		action resume cpu
		action resume gfx
		action resume fbdev
		action resume v4l2_avd
		action resume v4l2_vbi
		action resume v4l2_dolby
		action resume hdmi20_v4l2
		action resume v4l2_gps
		action resume v4l2_lgsr
		action resume v4l2_vbe
		action resume v4l2_vpq
		action resume v4l2_vsc
		action resume v4l2_vt
		action resume lg1k_te
		action resume venc
		action resume demod
		action resume display
		action resume sys
		;;

	test)
		sh $0 suspend
		printf 'please wait.. '
		spinner &
		sleep 5
		kill "$!"
		printf '\n'
		sh $0 resume
		;;

	status)
		;;
	*)
		echo "usage: lowpower.sh {suspend|resume|status|test}"
		echo "   suspend  - enter always ready mode"
		echo "   resume   - exit always ready mode"
		echo "   status   - print status   "
		echo "   test     - calls suspend and resume sequentially"
		exit 1
		;;
esac
