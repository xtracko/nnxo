all: nn-music

nn-music: net.hpp main.cpp
	${CXX} -std=c++11 -msse2 $< -o $@
clean:
	rm -f nn-music
