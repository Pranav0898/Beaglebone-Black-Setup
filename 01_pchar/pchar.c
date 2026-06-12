#include <linux/module.h>
#include <linux/fs.h>

// pseudo char device
#define MAX 32
static char mybuf[MAX];

// device number
static dev_t devno;
static int major = 250;

static int __init pchar_init(void) {
    int ret;
    printk(KERN_INFO "%s: pchar_init() called.\n", THIS_MODULE->name);
    // allocate device number
    devno = MKDEV(major, 0);
    ret = alloc_chrdev_region(&devno, 0, 1, "pchar");
    if(ret != 0) {
        printk(KERN_ERR "%s: alloc_chrdev_region() failed.\n", THIS_MODULE->name);
        return ret;
    }
    major = MAJOR(devno);
    printk(KERN_INFO "%s: alloc_chrdev_region() device num: %d.\n", THIS_MODULE->name, major);
    // create device class
    // create device file
    // initialize cdev object and add it in kernel
    return 0;
}

static void __exit pchar_exit(void) {
    printk(KERN_INFO "%s: pchar_exit() called.\n", THIS_MODULE->name);
    // remove cdev object from kernel
    // destroy device file
    // destroy device class
    // release device number
    unregister_chrdev_region(devno, 1);
    printk(KERN_INFO "%s: unregister_chrdev_region() released device num: %d.\n", THIS_MODULE->name, major);
}

module_init(pchar_init);
module_exit(pchar_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Pseudo Char Device Driver");
MODULE_AUTHOR("Pranav Sangar");

