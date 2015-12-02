all: nnxo

nnxo: functions.hpp network.hpp math.hpp main.cpp loaders.hpp utils.hpp
	${CXX} -std=c++11 -msse2 ${CXXFLAFS} *.cpp -o $@
clean:
	rm -f nnxo
