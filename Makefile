

INC=./inc
SRC=$(wildcard src/*.cpp)
SRC+=$(wildcard src/*.c)
SRC+=main.cpp

OBJS=$(SRC:.cpp=.o)

TARGET=demo.exe

CC=g++
CXXFLAGS=-O2 -g -Wall -fmessage-length=0 -I $(INC) -std=gnu++11
LDFLAGS=

all: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)
	
run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	
	