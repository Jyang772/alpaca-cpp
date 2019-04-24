CXX      := -g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
LDFLAGS  := -L/usr/lib -lcurl -ljsoncpp
TARGET   := main

all: $(TARGET)

main: main.o tradeapi.o account.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o tradeapi.o account.o -o $(TARGET)

main.o:
	$(CXX) $(CXXFLAGS) -c main.cpp

tradeapi.o: tradeapi.cpp tradeapi.h
	$(CXX) $(CXXFLAGS) -c tradeapi.cpp

account.o: account.cpp account.h
	$(CXX) $(CXXFLAGS) -c account.cpp

clean:
	rm main *.o *~
