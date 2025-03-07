#ifndef MAIN_H
#define	MAIN_H

#include<xc.h>
#include "clcd.h"
#include "adc.h"
#include "mkp.h"
#include "uart.h"
#include "ds1307.h"
#include "i2c.h"
#include "e_eprom.h"


typedef enum
{
    e_Dashboard,
    e_menu,
    e_viewlog,
    e_downloadlog,
    e_clearlog,
    e_settime
}State;


void Dashboard(char key, State *current_state);
void downloadlog(State *current_state);
void store_eeprom(char *time, char speed, char ev[][3], char row);
void menu(char key,State *current_state);
void viewlog(char key,State *current_state);
void clearlog(State *current_state);
void settime(char key,State *current_state);
static void get_time(void);
#endif	/* MAIN_H */

