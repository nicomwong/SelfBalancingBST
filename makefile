CXX = g++
CXXFLAGS = -std=c++17
BINARIES = test project3.out

project3.out: kAVLTree.o project3.cpp
	${CXX} ${CXXFLAGS} -g $^ -o $@

test: kAVLTree.o test.cpp
	${CXX} ${CXXFLAGS} -g $^ -o $@
	./$@

clean:
	/bin/rm -f ${BINARIES} *.o