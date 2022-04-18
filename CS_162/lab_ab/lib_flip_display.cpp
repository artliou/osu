/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 21, 2016
** Description:  General purpose library for using NCURSES in flip
*********************************************************************/

#include "lib_flip_display.hpp"
#include <stdio.h>
#include <stdarg.h>
#include <termios.h>
#include <string.h>

/*********************************************************************
**
** This file has poor comments because it is for testing and
** displaying data in the FLIP environment using NCURSES
**
** No program logic is contained within this file.
**
*********************************************************************/

int getkey()
{
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;

    /* set the terminal to raw mode */
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

    /* read a character from the stdin stream without blocking */
    /*   returns EOF (-1) if no character is available */
    character = fgetc(stdin);

    /* restore the original terminal attributes */
    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

void init_display(void)
{

}

void shutdown_display(void)
{
  while (getkey() == -1);
}

void debug_print (bool bold, const char * color,const char * string, ...)
{
  va_list list;
  va_start (list, string);

  printf (color, bold);
  vprintf (string, list);

  va_end (list);
}

void debug_test_result (bool passed)
{
  if (passed)
  {
    debug_print (true, COLOR_GREEN, "\tPASSED\n");
  }
  else
  {
    debug_print (true, COLOR_RED, "\tFAILED\n");
  }
}

void cursor_move_to(int x, int y)
{
    printf (CURSOR_GOTO1, x ,y);
}
void cursor_move_up(int x)
{
    printf (CURSOR_MOVE_UP, x);
}
void cursor_move_dn(int x)
{
    printf (CURSOR_MOVE_DN, x);
}
void cursor_move_lf(int x)
{
    printf (CURSOR_MOVE_LF, x);
}
void cursor_move_rt(int x)
{
    printf (CURSOR_MOVE_RT, x);
}

void screen_clear()
{
    printf (SCREEN_CLEAR);
}

void erase_tail()
{
    printf (ERASE_TAIL);
}
