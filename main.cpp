#include "ncurses.h"
#include <string>
#include <regex>
#include <stdio.h>
#define GNUPLOT "gnuplot -persist"

int main()
{
  //ncurses
  initscr();
  keypad(stdscr, TRUE);
  noecho();

  //initialize gnuplot
  FILE * gp;
  gp = popen(GNUPLOT,"w");
  if(gp == nullptr)
    printf("error opening pipe to GNU plot\n");

  fprintf(gp, "set term x11 noraise persist\n");

  //load file

  //process loop
  unsigned long index = 0;
  auto ch = -1;
  while(ch != 'q')
    {
      fprintf(gp, "plot %lu \n", index);
      fflush(gp);
      ch = getch();
      switch(ch)
	{
	case KEY_LEFT:
	  if(index > 0)
	    --index;
	  break;
	case KEY_RIGHT:
	  ++index;
	  break;
	default:
	  break;
	}
    }    

  fprintf(gp, "exit \n");
  fflush(gp);

  fclose(gp);

  endwin();
}
