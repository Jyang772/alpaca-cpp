CXX      := -g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
CXXFLAGS := -Iinclude/
LDFLAGS  := -L/usr/lib -lcurl -ljsoncpp
TARGET   := main
BUILD    := ..

all: $(TARGET)

main: main.o tradeapi.o account.o order.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o tradeapi.o account.o order.o -o $(BUILD)/$(TARGET) 

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp

tradeapi.o: tradeapi.cpp 
	$(CXX) $(CXXFLAGS) -c tradeapi.cpp

account.o: account.cpp 
	$(CXX) $(CXXFLAGS) -c account.cpp

order.o: order.cpp 
	$(CXX) $(CXXFLAGS) -c order.cpp

clean:
	rm -f $(TARGET) *.o *~
