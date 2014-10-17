//need to include /usr/include/ and /usr/lib/ to compile
//http://www.gnu.org/software/ncurses/
//#include "ncurses.h"
#include <string>
#include <regex>
#include <stdio.h>
#define GNUPLOT "gnuplot -persist"

//http://kunak.phsx.ku.edu/~sergei/Gnuplot/line_point_types.html
int main()
{
  FILE * gp;
  gp = popen(GNUPLOT,"w");

  if(gp == nullptr)
    printf("error opening pipe to GNU plot\n");

  fprintf(gp, "set term x11 noraise persist\n");
  
  while(true)
    {
      for(int i = 0; i < 100; i++)
	{
	  fprintf(gp, ("plot " + std::to_string(i) + " \n").c_str());
	}
    }
  fclose(gp);

  //create "steps/" directory
  
  //load data.txt
  //parse into individual steps.dat files

  //copy appropriate steps_#.dat file to local directory as current.dat
  //set datafile commentschars "#"
}
