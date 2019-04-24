CXX      := -g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
CXXFLAGS := -Iinclude/
LDFLAGS  := -L/usr/lib -lcurl -ljsoncpp
TARGET   := main
BUILD    := ..

all: $(TARGET)

main: main.o tradeapi.o account.o order.o position.o asset.o bar.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o tradeapi.o account.o order.o position.o asset.o bar.o \
		-o $(BUILD)/$(TARGET) 

main.o: main.cpp 
	$(CXX) $(CXXFLAGS) -c main.cpp

tradeapi.o: tradeapi.cpp 
	$(CXX) $(CXXFLAGS) -c tradeapi.cpp

account.o: account.cpp 
	$(CXX) $(CXXFLAGS) -c account.cpp

order.o: order.cpp 
	$(CXX) $(CXXFLAGS) -c order.cpp

position.o: position.cpp
	$(CXX) $(CXXFLAGS) -c position.cpp

asset.o: asset.cpp
	$(CXX) $(CXXFLAGS) -c asset.cpp

bar.o: bar.cpp
	$(CXX) $(CXXFLAGS) -c bar.cpp
clean:
	rm -f $(TARGET) *.o *~
