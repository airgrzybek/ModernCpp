

INC= \
	-I ./inc \
	-I ./AbstractFactory \
	-I ./Singleton \
	-I ./SmallObjectAllocation \
	
	
SRC=$(wildcard src/*.cpp)
SRC+=$(wildcard src/*.c)
SRC+=$(wildcard Singleton/*.cpp)
SRC+=$(wildcard SmallObjectAllocation/*.cpp)
SRC+=main.cpp

OBJS=$(SRC:.cpp=.o)

TARGET=demo.exe

CC=g++
CXXFLAGS=-O3 -Wall -fmessage-length=0 $(INC) -std=gnu++11 -Werror -DWINDOWS
LDFLAGS=

all: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)
	
run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	
	