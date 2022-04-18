/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 21, 2016
** Description:  General purpose library for using NCURSES in flip
*********************************************************************/

#include "lib_flip_display.h"

/*********************************************************************
**
** This file has poor comments because it is for testing and
** displaying data in the FLIP environment using NCURSES
**
** No program logic is contained within this file.
**
*********************************************************************/

void init_display(void)
{
  initscr();
  raw();
  keypad(stdscr, TRUE);
  echo();
  start_color();
  
  for (int color = 0; color < 8; color++)
  {
    init_pair (color, color, COLOR_BLACK);
  }
}

void shutdown_display(void)
{
  endwin();
}

void debug_print (bool bold, int color,const char * string, ...)
{
  va_list list;
  va_start (list, string);
  if (bold)
  {
    attron(A_BOLD);
  }
  attron (COLOR_PAIR(color));

  vwprintw (stdscr, string, list);

  attroff (COLOR_PAIR(color));
  if (bold)
  {
    attroff(A_BOLD);
  }
  refresh();
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
