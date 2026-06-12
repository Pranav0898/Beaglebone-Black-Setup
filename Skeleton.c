#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>

// pseudo char device
#define MAX 32
static char mybuf[MAX];

// device number
static dev_t devno;
static int major = 250;
// device class
static struct class *pclass;
// device struct - cdev
static struct cdev pchar_cdev;
// device operations
static int pchar_open(struct inode *pinode, struct file *pfile) {
    printk(KERN_INFO "%s: pchar_open() called.\n", THIS_MODULE->name);
    return 0;
}

static int pchar_close(struct inode *pinode, struct file *pfile) {
    printk(KERN_INFO "%s: pchar_close() called.\n", THIS_MODULE->name);
    return 0;
}

static ssize_t pchar_write(struct file *pfile, const char __user *ubuf, size_t bufsize, loff_t *pf_pos) {
    printk(KERN_INFO "%s: pchar_write() called.\n", THIS_MODULE->name);
    return bufsize;
}

static ssize_t pchar_read(struct file *pfile, char __user *ubuf, size_t bufsize, loff_t *pf_pos) {
    printk(KERN_INFO "%s: pchar_read() called.\n", THIS_MODULE->name);
    return 0;
}

static struct file_operations pchar_fops = {
    .owner = THIS_MODULE,
    .open = pchar_open,
    .release = pchar_close,
    .write = pchar_write,
    .read = pchar_read
};

static int __init pchar_init(void) {
    int ret;
    struct device *pdevice;

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
    pclass = class_create(THIS_MODULE, "pchar_class");
    if(IS_ERR(pclass)) {
        printk(KERN_ERR "%s: class_create() failed.\n", THIS_MODULE->name);
        unregister_chrdev_region(devno, 1);
        return -1;
    }
    printk(KERN_INFO "%s: class_create() created pchar_class.\n", THIS_MODULE->name);
    // create device file
    pdevice = device_create(pclass, NULL, devno, NULL, "pchar");
    if(IS_ERR(pdevice)) {
        printk(KERN_ERR "%s: device_create() failed.\n", THIS_MODULE->name);
        class_destroy(pclass);
        unregister_chrdev_region(devno, 1);
        return -1;
    }
    printk(KERN_INFO "%s: device_create() created pchar device.\n", THIS_MODULE->name);
    // initialize cdev object and add it in kernel
    pchar_cdev.owner = THIS_MODULE;
    cdev_init(&pchar_cdev, &pchar_fops);
    ret = cdev_add(&pchar_cdev, devno, 1);
    if(ret != 0) {
        printk(KERN_ERR "%s: cdev_add() failed.\n", THIS_MODULE->name);
        device_destroy(pclass, devno);
        class_destroy(pclass);
        unregister_chrdev_region(devno, 1);
        return -1;
    }
    printk(KERN_INFO "%s: cdev_add() added device in kernel.\n", THIS_MODULE->name);
    return 0;
}

static void __exit pchar_exit(void) {
    printk(KERN_INFO "%s: pchar_exit() called.\n", THIS_MODULE->name);
    // remove cdev object from kernel
    cdev_del(&pchar_cdev);
    printk(KERN_INFO "%s: cdev_del() removed device from kernel.\n", THIS_MODULE->name);
    // destroy device file
    device_destroy(pclass, devno);
    printk(KERN_INFO "%s: device_destroy() destroyed pchar device.\n", THIS_MODULE->name);
    // destroy device class
    class_destroy(pclass);
    printk(KERN_INFO "%s: class_destroy() destroyed pchar_class.\n", THIS_MODULE->name);
    // release device number
    unregister_chrdev_region(devno, 1);
    printk(KERN_INFO "%s: unregister_chrdev_region() released device num: %d.\n", THIS_MODULE->name, major);
}

module_init(pchar_init);
module_exit(pchar_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Pseudo Char Device Driver");
MODULE_AUTHOR("Nilesh Ghule <nilesh@sunbeaminfo.com>");

