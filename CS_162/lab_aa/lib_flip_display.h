/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 21, 2016
** Description:  General purpose library for using NCURSES in flip
*********************************************************************/

#ifndef LIB_FLIP_DISPLAY_H
#define LIB_FLIP_DISPLAY_H

/*********************************************************************
**
** This file has poor comments because it is for testing and
** displaying data in the FLIP environment using NCURSES
**
** No program logic is contained within this file.
**
*********************************************************************/

#include "ncurses.h"

void init_display(void);
void shutdown_display(void);
void debug_print (bool bold, int color,const char * string, ...);
void debug_test_result (bool passed);

#endif // LIB_FLIP_DISPLAY_H
