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

#define TEXT_RESET  "\x1B[0m"
#define COLOR_RED   "\x1B[%d;31m"
#define COLOR_GREEN   "\x1B[%d;32m"
#define COLOR_YELLOW  "\x1B[%d;33m"
#define COLOR_BLUE   "\x1B[%d;34m"
#define COLOR_MAGENTA   "\x1B[%d;35m"
#define COLOR_CYAN   "\x1B[%d;36m"
#define COLOR_WHITE   "\x1B[%d;37m"

void init_display(void);
void shutdown_display(void);
void debug_print (bool bold, const char * color,const char * string, ...);
void debug_test_result (bool passed);

#endif // LIB_FLIP_DISPLAY_H
