CXX      := -g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
LDFLAGS  := -L/usr/lib -lcurl -ljsoncpp
TARGET   := main

all: $(TARGET)

main: main.o tradeapi.o account.o order.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o tradeapi.o account.o order.o -o $(TARGET)

main.o:
	$(CXX) $(CXXFLAGS) -c main.cpp

tradeapi.o: tradeapi.cpp tradeapi.h
	$(CXX) $(CXXFLAGS) -c tradeapi.cpp

account.o: account.cpp account.h
	$(CXX) $(CXXFLAGS) -c account.cpp

order.o: order.cpp order.h
	$(CXX) $(CXXFLAGS) -c order.cpp

clean:
	rm -f $(TARGET) *.o *~
