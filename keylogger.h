#include <linux/keyboard.h>
#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include "keys.h"
static char *msg_Ptr;
void update_key(struct keyboard_notifier_param p)
{
    if (p.shift){
        /*hundle as shift*/
        msg_Ptr = keycode[p.value][1];
    }
    else
    {
        msg_Ptr= keycode[p.value][0];
    }
    
}
/*
static int device_open(struct indoe *indoe, struct file *file)
{
    static int counter =0;
    if (Device_open) return -EBUSY;
    device_open++;
}
*/
static ssize_t device_read(struct file *filp, char __user * buffer, size_t length, loff_t *offset)
{
    int bytes_read=0;
    if (*msg_Ptr ==0) return 0;
    while (length && *msg_Ptr){
        put_user(*(msg_Ptr++), buffer++);
        length--;
        bytes_read++;
    }
}