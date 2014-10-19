#include <string>
#include <regex>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <functional>
#include <algorithm>
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

std::string file_to_string(std::string file_path)
{
  std::ifstream file(file_path);
  std::istreambuf_iterator<char> fbegin(file), fend;
  return {fbegin, fend};
}

void step(int & ch)
{
  ch = getch();
}

template <class T>
T max_value(const std::string & file_contents, const std::regex & re)
{
    T max = 0;
    std::sregex_iterator begin(file_contents.begin(), file_contents.end(), re), end;
    for (auto it = begin; it != end; ++it)
        max = std::max<T>(stol((*it)[1]), max);
    return max;
}

//find max sub-indexed plot and return it as the stride
unsigned long stride_count(const std::string & file_contents)
{
    return max_value<unsigned long>(file_contents, std::regex("\\{(\\d+)\\}")) + 1;
}

//insert the dat filename into file_contents
std::string insert_dat_file(const std::string & file_contents, const std::string & dat_name)
{
  return std::regex_replace(file_contents, std::regex("\\{DAT\\}"), dat_name);
}

//finx the max occurance of #/d+
unsigned long plot_count(const std::string & file_contents)
{
    return max_value<unsigned long>(file_contents, std::regex("#(\\d+)"));
}

int main(int argc, char ** argv)
{
  //load file
  if(argc != 3)
    {
      printf("invalid arguements\n");
      return EXIT_FAILURE;
    }

  std::string command_file_name = argv[1];
  std::string data_file_name = argv[2];

  auto data = file_to_string(data_file_name);
  auto command = file_to_string(command_file_name);
  command = insert_dat_file(command, data_file_name);

  std::regex re_subindex("\\{(\\d+)\\}");
  
  //process loop
  unsigned long index = 0;
  unsigned long stride = stride_count(command);
  unsigned long max_index = plot_count(data)-1;

  auto fmt = [&index, stride](const unsigned m_index, const std::string & match)->std::string
    { return std::to_string((stride * index) + stol(match)); }; //index can only be 1

  start_ncurses();
  auto gp = start_gnuplot();

  for(int ch = -1; ch != 'q'; step(ch))
    {
      switch(ch)
	{
	case KEY_LEFT:
	  if(index > 0) --index;
	  break;
	case KEY_RIGHT:
	  if(index < max_index) ++index;
	  break;
	default:
	  break;
	}
      erase();
      move(0,0);
      using namespace bsb::regex_ext;
      std::string formated_command = regex_replace_ext(command,
						       re_subindex,
						       fmt);
      printw(formated_command.c_str());
      fprintf(gp, "%s \n", formated_command.c_str());
      fflush(gp);
    }
  stop_gnuplot(gp);
  stop_ncurses();

  return EXIT_SUCCESS;
}
