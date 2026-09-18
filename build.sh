#!/bin/bash -ex

CPUS=$(grep '^processor' /proc/cpuinfo | tail -n1 | awk '{print $3 + 1}')
if test -z "$CPUS"; then
	CPUS=15;
fi

# default values
CHIP_NAME=o26
JOBS=$CPUS
CROSS_COMPILE=aarch64-linux-gnu-

function usage() {
	echo ""
	echo " build.sh [options ...]"
	echo "   options:"
	echo "     -c <chip-name>              : default $CHIP_NAME"
	echo "     -j <jobs>                   : default $JOBS"
	echo "     -t <cross-compiler-prefix>  : default $CROSS_COMPILE"
	echo ""
}

while getopts c:j:t: name; do
	case $name in
	c)
		CHIP_NAME="$OPTARG"
		;;
	j)
		JOBS="$OPTARG"
		;;
	t)
		CROSS_COMPILE="$OPTARG"
		;;
	*)
		usage
		exit 1
		;;
	esac
done

rm -f linux-rockhopper/drivers/lg_kdriver
ln -sf ../../kdriver linux-rockhopper/drivers/lg_kdriver

# since o26
KDRV_PLATFORM_CFG=${CHIP_NAME}_webos
if ! test -f kdriver/platform/${KDRV_PLATFORM_CFG}/platform_dev.mk; then
	# before o26
	KDRV_PLATFORM_CFG=${CHIP_NAME}_webos_udtv
fi
test -f kdriver/platform/${KDRV_PLATFORM_CFG}/platform_dev.mk

ARGS=(-C linux-rockhopper)
ARGS+=(ARCH=arm64)
ARGS+=(CROSS_COMPILE=$CROSS_COMPILE)
ARGS+=(CONFIG_LG_BUILTIN_KDRIVER=y)
ARGS+=(KDRV_MODULE_BUILD=NO)
ARGS+=(KDRV_PLATFORM_CFG=${KDRV_PLATFORM_CFG})
ARGS+=(PLATFORM_CHIP_NAME=$CHIP_NAME)
if test -n "$JOBS"; then
	ARGS+=(-j $JOBS)
fi

make "${ARGS[@]}" lg1k_defconfig
make "${ARGS[@]}"
make "${ARGS[@]}" modules
make "${ARGS[@]}" modules_install INSTALL_MOD_PATH=$(pwd)/target


if test -d npu-drv; then
	ARGS=(-C npu-drv)
	ARGS+=(ARCH=arm64)
	ARGS+=(CROSS_COMPILE=$CROSS_COMPILE)
	ARGS+=(KERNEL_SRC=$(pwd)/linux-rockhopper)
	make "${ARGS[@]}"
	make "${ARGS[@]}" modules_install INSTALL_MOD_PATH=$(pwd)/target
else
	echo skip npu-drv...
fi

echo Done.

