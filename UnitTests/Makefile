INC= \
	-I ../inc \
	-I ../AbstractFactory \
	-I ../Singleton \
	-I ../SmallObjectAllocation \

# UT setup	
GTEST_LIB_DIR=/home/grzybek/workspace/googletest/googletest
INC +=-I $(GTEST_LIB_DIR)/include

SRC+=$(wildcard ./*.cpp)
SRC+=$(wildcard ../src/*.cpp)
SRC+=$(wildcard ../src/*.c)
SRC+=$(wildcard ../Singleton/*.cpp)
SRC+=$(wildcard ../SmallObjectAllocation/*.cpp)

OBJS=$(SRC:.cpp=.o)

TARGET=UT

CC=g++
CXXFLAGS=-ggdb -Wall -fmessage-length=0 $(INC) -std=gnu++11 -static-libgcc -static-libstdc++ \
			-fprofile-arcs -ftest-coverage 
LDFLAGS=-L $(GTEST_LIB_DIR)/lib -lgtest -lpthread -fprofile-arcs

all: $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS)

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

memory_check: all
	drmemory.exe $(TARGET) -show_reachable

code_coverage: run
	gcov ../SmallObjectAllocation/*
