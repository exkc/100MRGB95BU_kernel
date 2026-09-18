**Secure DMA-BUF Allocator Userspace API**




.. c:type:: struct sheap_alloc_data

   metadata passed from userspace for allocations.

**Definition**

::

  struct sheap_alloc_data {
    __u64 len;
    __u32 fd;
    __u32 fd_flags;
    __u64 heap_flags;
  };

**Members**

``len``
  size of the allocation.

``fd``
  will be populated with a fd which provides the handle
  to the allocated dma-buf.

``fd_flags``
  file descriptor flags used when allocating.
  O_CLOEXEC flag should be set.
  O_RDONLY, O_WRONLY, O_RDWR flags are allowed to be set.

``heap_flags``
  flags passed to heap(currently not allowed)


**Description**

provided by userspace as an argument to the ioctl




.. c:type:: struct sheap_attach_data

   metadata passed from userspace for get phy addr of dma buf.

**Definition**

::

  struct sheap_attach_data {
    __u32 fd;
    __u64 paddr;
  };

**Members**

``fd``
  file descriptor handle to the allocated dma-buf.

``paddr``
  sg dma address(physical address) of dma-buf.



.. c:function:: SHEAP_IOCTL_ALLOC ()

   allocate secure dma-buf from protected pool.

**Parameters**

**Description**


This IOCTL command performs secure dma-buf memory allocation on sheap device.
uses the _IOWR macro to specify the read/write nature of the command.

Takes a sheap_alloc_data struct and returns it with the fd field
populated with the dmabuf handle of the allocation.


.. c:function:: SHEAP_IOCTL_ATTACH ()

   import secure dma-buf to get the phy address.

**Parameters**

**Description**


This IOCTL command performs secure dma-buf attachment to get phy address.
uses the _IOWR macro to specify the read/write nature of the command.

Takes a dma-buf fd in sheap_attach_data struct and
returns it with the phy addr from imported dma-buf handle.


