CC = clang
CXX = clang++
CXXFLAGS = --stdlib=libc++ --std=c++14 -I /usr/include/ -I ~/repos/brainstem_breakfast/source/ -lncurses


main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean: 
	rm -rf *.o *.gch
