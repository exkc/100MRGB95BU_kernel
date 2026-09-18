
apps += test_dma_buf_te_alloc

test-gpu-kernel-files :=
test-gpu-kernel-files += $(src)/dma_buf_te_alloc.sh
test-gpu-kernel-files += $(src)/gpu_check_proc_meminfo.sh
$(eval $(call install_files,gpu-kernel-tests,$(test-gpu-kernel-files),$(INSTALL_DIR_SHARE)/tests/20.gpu-kernel))



GPU_RELEASE = b46

apps += gpu-alloc.csf
objs_gpu-alloc.csf = gpu-alloc.o
CFLAGS_gpu-alloc.csf += -I$(src)/../$(GPU_RELEASE)/include/uapi/gpu/arm/midgard
CFLAGS_gpu-alloc.csf += -DMALI_USE_CSF
LDFLAGS_gpu-alloc.csf += -static

apps += gpu-alloc.jm
objs_gpu-alloc.jm = gpu-alloc.o
CFLAGS_gpu-alloc.jm += -I$(src)/../$(GPU_RELEASE)/include/uapi/gpu/arm/midgard
LDFLAGS_gpu-alloc.jm += -static
