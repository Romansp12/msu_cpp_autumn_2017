CC      	= g++
CFLAGS  	= -Wall -std=c++11 -O2

all: clean
	$(CC) $(CFLAGS) calculator.cpp main.cpp -o calc

clean:
	rm -rf *.o calc

tests: 
	./calc
