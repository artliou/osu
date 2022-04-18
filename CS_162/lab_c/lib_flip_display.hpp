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

#define CURSOR_GOTO1 "\033[%d;%dH"
#define CURSOR_GOTO2 "\033[%d;%df"
// puts the cursor at line L and column C.

#define CURSOR_MOVE_UP "\033[%dA"
#define CURSOR_MOVE_DN "\033[%dB"
#define CURSOR_MOVE_RT "\033[%dC"
#define CURSOR_MOVE_LF "\033[%dD"
#define SCREEN_CLEAR "\033[2J"
#define ERASE_TAIL "\033[K"

int getkey();
void init_display(void);
void shutdown_display(void);
void debug_print (bool bold, const char * color,const char * string, ...);
void debug_test_result (bool passed);

void cursor_move_to(int x, int y);
void cursor_move_up(int x);
void cursor_move_dn(int x);
void cursor_move_lf(int x);
void cursor_move_rt(int x);

void screen_clear();
void erase_tail();

#endif // LIB_FLIP_DISPLAY_H
