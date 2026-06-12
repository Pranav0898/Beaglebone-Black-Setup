#include <linux/module.h>

// * kernel module entry point fn
//      called by kernel (only once) when module is loaded into kernel (insmod).
// * function should perform module intialization and
//      return 0 if initialization is successful; otherwise return error code
// * __init --> is a gcc compiler attribute __section(".init.text")
//      to put fn code into a special section ".init.text".
//      this section is auto released/deleted after module loading.
int __init init_module(void) {
    printk("hello: init_module() called...\n");
    return 0;
}

// * kernel module entry point fn
//      called by kernel (only once) when module is unloaded from kernel (rmmod).
// * function should perform module de-intialization and
//      returns nothing (void)
// * __exit --> is a gcc compiler attribute __section(".exit.text")
//      to put fn code into a special section ".exit.text".
//      this section is auto released/deleted after module unloading.
void __exit cleanup_module(void) {
    printk("hello: cleanup_module() called...\n");
}

// assign module license. available licenses are GPL, GPL v2, Dual BSD/GPL, Dual MIT/GPL, Proprietary
//  If module GPL licensed then it can access exported fns from other GPL licensed components
MODULE_LICENSE("GPL");
// add information about the module into module metadata
MODULE_DESCRIPTION("Hello kernel module for DESD-Aug-24 @ Sunbeam");
// add developer info about module into module metadata
MODULE_AUTHOR("Nilesh Ghule <nilesh@sunbeaminfo.com>");

// all above MODULE_ macros internally calls MODULE_INFO() macro that adds module info
//  into modules metadata section ".modinfo".
// > modinfo hello.ko
//  utility to display the module info/metadata (from .modinfo section of the module).

// Module Compilation and Execution
//  1. Create a Makefile
//      obj-m = hello.o
//  2. > make -C /lib/modules/`uname -r`/build M=`pwd` modules
//      compiles modules mentioned in Makefile in `pwd` (cur dir) using the settings
//      from kernels main Makefile in build dir (ksrc dir).
//  3. > sudo insmod hello.ko
//      loads the module into the kernel and runs init_module() entry pt.
//  4. > lsmod
//      lists the modules loaded in the kernel
//  5. > sudo rmmod hello.ko
//      runs clean_module() entry pt and unloads the module from the kernel.


