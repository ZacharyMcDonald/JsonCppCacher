CC = g++
CFLAGS = -g -std=c++11 -Wall
GFLAGS = -lgtest -lgtest_main -lpthread -ljsoncpp
TEST_PROG = test.exe
SRC = src/
OF = ${SRC}obj_files/
OBJs = ${OF}jcache.o

build: ${OF}jcache.o
	rm -f ${TEST_PROG}
	${CC} ${CFLAGS} ${SRC}jcache_tests.cpp ${OBJs} ${GFLAGS} -o ${TEST_PROG} 
	./${TEST_PROG}

${OF}jcache.o: ${SRC}jcache.cpp ${SRC}jcache.h
	${CC} ${CFLAGS} -c ${SRC}jcache.cpp -ljsoncpp -o ${OF}jcache.o

clean:
	rm -f *.o *.gch ${TEST_PROG}
	rm ${OF}*