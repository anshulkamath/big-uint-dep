CXX = cc
CXXFLAGS = -g -Wall -Wextra -pedantic -std=c17

all: test-sha256

test-sha256: test-sha256.o sha256.o
	${CXX} ${CXXFLAGS} -o $@ $^

test-sha256.o: test-sha256.c sha256.c sha256.h
	${CXX} ${CXXFLAGS} -o $@ -c $<

sha256.o: sha256.c sha256.h
	${CXX} -c ${CXXFLAGS} -o $@ $<

clean:
	rm -rf *.o *.dSYM main