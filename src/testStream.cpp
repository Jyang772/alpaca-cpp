#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include "tradeapi.h"
#include "date.h"


template <class Precision>
std::string getISOCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    return date::format("%FT%TZ", date::floor<Precision>(now));
}

void DatePlusDays(struct tm* date, int days);
void prices(std::vector<std::string> symbols);
void get_prices(std::vector<std::string> symbols, tm* end_dt);

double getDeltaMovingAverage(double delta, std::list<double> listDeltaMA)
{
    listDeltaMA.push_back(delta);
    if (listDeltaMA.size() > 10) listDeltaMA.pop_front();
    double sum = 0;
    for (std::list<double>::iterator p = listDeltaMA.begin(); p != listDeltaMA.end(); ++p)
        sum += (double)*p;
    return sum / listDeltaMA.size();
}



int main() {

	std::cout << "hello" << std::endl;

	std::string EndPoint = "paper-api.alpaca.markets";
	std::string KeyID = "PKPUURFL462XO9XA1JW8";
	std::string SecretKey = "us4YPXtDQ4pEm10Qbwd7hWBK8ggslXScdAgBmRFp";

	//Tradeapi api; //REST
	//api.init(EndPoint,KeyID,SecretKey);
	
	
	Stream s;
	s.init();
	s.connect("wss://paper-api.alpaca.markets/stream",KeyID,SecretKey);

	std::vector<std::string> streams;
	streams.push_back("trade_updates");
	streams.push_back("account_updates");

	s.subscribe(streams);

        while(1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        }
	


	return 0;
}


