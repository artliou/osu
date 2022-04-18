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
** displaying data in the FLIP environment
**
** No program/assignement logic is contained within this file.
**
*********************************************************************/

int DebugConsole::debugLevel = 0;

void DebugConsole::SetDebugLevel(int level)
{
  DebugConsole::debugLevel = level;
}

int DebugConsole::GetDebugLevel()
{
  return DebugConsole::debugLevel;
}

int DebugConsole::getkey()
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

void DebugConsole::init_display(void)
{

}

void DebugConsole::shutdown_display(void)
{
  while (getkey() == -1);
}

void DebugConsole::debug_print (int level, bool bold, const char * color,const char * string, ...)
{
  if (level > DebugConsole::debugLevel)
  {
    return;
  }

  va_list list;
  va_start (list, string);

  printf (color, bold);
  vprintf (string, list);
  printf (COLOR_WHITE, false);

  va_end (list);
}

void DebugConsole::debug_test_result (bool passed)
{
  if (passed)
  {
    DebugConsole::debug_print (1, true, COLOR_GREEN, "\tPASSED\n");
  }
  else
  {
    DebugConsole::debug_print (1, true, COLOR_RED, "\tFAILED\n");
  }
}

void DebugConsole::cursor_move_to(int x, int y)
{
    printf (CURSOR_GOTO1, x ,y);
}
void DebugConsole::cursor_move_up(int x)
{
    printf (CURSOR_MOVE_UP, x);
}
void DebugConsole::cursor_move_dn(int x)
{
    printf (CURSOR_MOVE_DN, x);
}
void DebugConsole::cursor_move_lf(int x)
{
    printf (CURSOR_MOVE_LF, x);
}
void DebugConsole::cursor_move_rt(int x)
{
    printf (CURSOR_MOVE_RT, x);
}

void DebugConsole::screen_clear()
{
    printf (SCREEN_CLEAR);
}

void DebugConsole::erase_tail()
{
    printf (ERASE_TAIL);
}
