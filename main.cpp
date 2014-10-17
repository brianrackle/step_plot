#include <string>
#include <regex>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "ncurses.h"
#include "regex_replace_ext.hpp"

#define GNUPLOT "gnuplot -persist"

int main(int argc, char ** argv)
{
  //load file
  if(argc != 2)
    {
      printf("invalid arguements\n");
      return EXIT_FAILURE;
    }

  //initialize gnuplot
  FILE * gp;
  gp = popen(GNUPLOT,"w");
  if(gp == nullptr)
    {
      printf("error opening pipe to GNU plot\n");
      fflush(gp);
      return EXIT_FAILURE;
    }

  fprintf(gp, "set term x11 noraise persist\n");
  fflush(gp);
  
  //ncurses
  initscr();
  keypad(stdscr, TRUE);
  noecho();

  std::ifstream command_file(argv[1]);
  std::istreambuf_iterator<char> fbegin(command_file), fend;

  std::string command_contents(fbegin, fend);
  std::regex re_stride("\\{plots (\\d+)\\}");
  std::regex re_subindex("\\{(\\d+)\\}");
  
  std::smatch plots_match;
  std::regex_search(command_contents, plots_match, re_stride);
  
  unsigned long stride = stol(plots_match[1]);
  std::cout << stride << std::endl;
  
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

      /*
     auto command_string = bsb::regex_ext::regex_replace_ext(command_contents, re_subindex, 
					[index,stride](const std::string & string_match)
					{
					  long sub_index = stol(string_match) + 1;
					  return std::to_string((stride * index) + sub_index);
					});  
      */    
    }

  fprintf(gp, "exit \n");
  fflush(gp);

  fclose(gp);

  endwin();
  return EXIT_SUCCESS;
}
