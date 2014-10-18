#include <string>
#include <regex>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <functional>
#include "ncurses.h"
#include "regex_replace_ext.hpp"

#define GNUPLOT "gnuplot -persist"

FILE * start_gnuplot()
{
  //initialize gnuplot
  FILE * gp;
  gp = popen(GNUPLOT,"w");
  if(gp == nullptr)
    {
      printf("error opening pipe to GNU plot\n");
      fflush(gp);
      throw;
    }

  fprintf(gp, "set term x11 noraise persist\n");
  fflush(gp);
  return gp;
}

void stop_gnuplot(FILE * gp)
{
  fprintf(gp, "exit \n");
  fflush(gp);
  fclose(gp);
}

void start_ncurses()
{
  initscr();
  keypad(stdscr, TRUE);
  noecho();
}

void stop_ncurses()
{
  endwin();
}

std::string file_to_string(char * file_path)
{
  std::ifstream file(file_path);
  std::istreambuf_iterator<char> fbegin(file), fend;
  return {fbegin, fend};
}

void step(int & ch)
{
  ch = getch();
}

//find max sub-indexed plot and return it as the stride
long stride_count(std::string file_contents)
{
  std::regex re("\\{(\\d+)\\}");
  long max = 0;
  std::smatch results;
  std::regex_search(file_contents, results, re);
  //iterate results
}

//insert the dat filename into file_contents
std::string insert_dat_file(std::string file_contents, std::string dat_name)
{
  std::regex re("\\{DAT\\}");
  return std::regex_replace(file_contents, re, dat_name);
}

//finx the max occurance of #/d+
long plot_count(std::string file_contents)
{
  std::regex re("#(\\d+)");
}

int main(int argc, char ** argv)
{
  //load file
  if(argc != 3)
    {
      printf("invalid arguements\n");
      return EXIT_FAILURE;
    }

  std::string command_file_name{argv[1]);
  std::string data_file_name{argv[2]);

  auto data = file_to_string(data_file_name);
  auto command = file_to_string(plot_file_name);
  command = insert_dat_file(command, data_file_name);

  //replace {DAT} in argv[1] with argv[2]
  //stride = count number of {/d+} in argv[1]
  //plot_count = find #\d+ in 
  
  std::regex re_subindex("\\{(\\d+)\\}");

  //find max index
  std::regex re_count("#(\\d+)");
  
  //process loop
  unsigned long index = 0;
  unsigned long stride = 3;
  unsigned long max_index = 0;

  auto fmt = [&index, stride](const std::string & match)->std::string
    { 
      std::cout << match << " " << stol(match) + 1 << std::endl;
      return std::to_string((stride * index) + stol(match) + 1);
    };

  start_ncurses();
  auto gp = start_gnuplot();
  for(int ch = -1; ch != 'q'; step(ch))
    {
      //"load FILE
      fprintf(gp, "plot %lu \n", index);
      fflush(gp);

      switch(getch())
	{
	case KEY_LEFT:
	  if(index > 0) --index;
	  break;
	case KEY_RIGHT:
	  ++index;
	  break;
	default:
	  break;
	}
      using namespace bsb::regex_ext;
      auto command = regex_replace_ext(command, 
				       re_subindex,
				       fmt);
    }
  stop_gnuplot(gp);
  stop_ncurses();

  return EXIT_SUCCESS;
}
