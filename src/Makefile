CXX      := -g++
CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
CXXFLAGS := -Iinclude/
LDFLAGS  := -L/usr/lib -lcurl -ljsoncpp
TARGET   := sma
BUILD    := ..

all: $(TARGET)

sma: sma.o tradeapi.o account.o order.o position.o asset.o bar.o clock.o calendar.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) sma.o tradeapi.o account.o order.o \
		position.o asset.o bar.o clock.o calendar.o \
		-o $(BUILD)/$(TARGET) 

sma.o: sma.cpp 
	$(CXX) $(CXXFLAGS) -c sma.cpp

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

clock.o: clock.cpp
	$(CXX) $(CXXFLAGS) -c clock.cpp

calendar.o: calendar.cpp
	$(CXX) $(CXXFLAGS) -c calendar.cpp

clean:
	rm -f $(TARGET) *.o *~
