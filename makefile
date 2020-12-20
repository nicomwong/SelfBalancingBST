CXX = g++
CXXFLAGS = -std=c++17
BINARIES = test project3.out

test: kAVLTree.o test.cpp
	${CXX} ${CXXFLAGS} -g $^ -o $@
	./$@

clean:
	/bin/rm -f ${BINARIES} *.o