CC = clang
CXX = clang++
CXXFLAGS = --stdlib=libc++ --std=c++14 -I /usr/include/ -lncurses


main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean: 
	rm -rf *.o *.gch
