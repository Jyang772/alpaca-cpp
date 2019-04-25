CXX      := -g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
CXXFLAGS := -Iinclude/
LDFLAGS  := -L/usr/lib -lcurl -ljsoncpp
TARGET   := sma
BUILD	 := build

all:
	+$(MAKE) -C src

clean:
	rm -f $(TARGET) *.o *~ *.out
	+$(MAKE) -C src clean
