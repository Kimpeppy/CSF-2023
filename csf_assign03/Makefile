CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

csim: main.o csimfuncs.o
	$(CC) -o csim main.o csimfuncs.o

test: csimtest.o csimfuncs.o
	$(CC) -o test csimtest.o csimfuncs.o

main.o: main.cpp csimfuncs.h
	$(CC) $(CFLAGS) -c main.cpp

csimtest.o: csimtest.cpp csimfuncs.h
	$(CC) $(CFLAGS) -c csimtest.cpp

csimfuncs.o: csimfuncs.cpp csimfuncs.h
	$(CC) $(CFLAGS) -c csimfuncs.cpp

.PHONY: solution.zip
solution.zip:
	rm -f solution.zip
	zip -9r $@ Makefile README.txt *.cpp *.h
clean:
	rm -f *.o main