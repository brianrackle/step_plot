CC = clang
CXX = clang++
CXXFLAGS = --std=c++1y

all: main.o gradient.hpp.gch gradient_test.hpp.gch markdown.hpp.gch markdown_test.hpp.ghc range_map.hpp.gch range_map_test.hpp.gch shelp.hpp.gch shelp_test.hpp.gch time_it.hpp.gch time_it_test.hpp.gch

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp


clean: 
	rm -rf *.o *.gch
