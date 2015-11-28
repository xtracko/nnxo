all: nnxo

nnxo: network.hpp math.hpp serialization.hpp main.cpp
	${CXX} -std=c++11 -msse2 ${CXXFLAFS} $^ -o $@
clean:
	rm -f nnxo
