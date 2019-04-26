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

	Tradeapi api; //REST
	api.init(EndPoint,KeyID,SecretKey);
	
	
	//Test getAccount
	/*
	auto s = api.get_account();
	std::cout << s.status << std::endl;
	std::cout << s.buying_power << std::endl;
	std::cout << s.json.toStyledString() << std::endl;
	*/


	//Test submit_order
	//auto order = api.submit_order("TSLA",5,"buy","market","day");
	//std::cout << order.symbol << std::endl;

	//Test list_orders
	
	//auto orders = api.list_orders("open");
	//std::cout << orders[0].symbol << std::endl;
	//std::cout << orders[0].json.toStyledString() << std::endl;
	
	auto orders = api.list_orders("open");
	//Test get_order{order_id}
	auto order_ = api.get_order("2fd3f1c6-98ca-4f4c-a4d4-bda4d5765419");
	auto order_by_client_id = api.get_order_by_client_order_id("0664a1d8-7613-4b4c-b473-5bb5644e0014");
	//api.cancel_order("25b61d81-fffd-49b1-aefb-09a7d94be86f");
	
	auto positions = api.list_positions();
	//std::cout << positions[0].qty << std::endl;

	auto position = api.get_position("TSLA");

	//auto assets = api.list_assets();
	//std::cout << assets.size() << std::endl;
	//auto asset = api.get_asset("TSLA");
	//
	std::vector<std::string> symbols;
	symbols.push_back("TSLA");
	symbols.push_back("AAPL");
	auto bars = api.get_barset(symbols,"1Min",1000);

	std::vector<Bar> tsla_bars(std::begin(bars["TSLA"]),std::end(bars["TSLA"]));
	printf("TSLA day's change: %.3f%\n",(tsla_bars.back().c - tsla_bars[0].c)/tsla_bars[0].c * 100);

	printf("TSLA BARS: \n");
	for(int i=tsla_bars.size()-1; i>=990; i--)
		printf("%.2f\n",tsla_bars[i].c);


	
	auto clock = api.get_clock();
	auto now = clock.timestamp;
	std::cout << "Now: "  << now << std::endl;
	
	
	//prices(symbols);
	

	std::vector<std::string> assetsToTrade;
	assetsToTrade.push_back("SPY");
	assetsToTrade.push_back("MSFT");
	assetsToTrade.push_back("AAPL");
	assetsToTrade.push_back("NFLX");
	assetsToTrade.push_back("TSLA");
	double positionSizing = 0.25;

	auto barset = api.get_barset(assetsToTrade,"15Min",100);

	for(int i=0; i<assetsToTrade.size(); i++) {
		std::vector<Bar> bars(std::begin(barset[assetsToTrade[i]]),std::end(barset[assetsToTrade[i]]));

		std::list<std::string> timeList;
		std::list<double> openList;
		std::list<double> highList;
		std::list<double> lowList;
		std::list<double> closeList;
		std::list<double> volumeList;

		for(int j=0; j<bars.size(); j++) {
			/*
			std::string dateStr = bars[j].t;
			int y,M,d,h,m;
			float s;
			sscanf(dateStr.c_str(), "%d-%d-%dT%d:%d:%fZ", &y, &M, &d, &h, &m, &s);
			struct tm timestamp;
			timestamp.tm_year = y - 1900; // Year since 1900
			timestamp.tm_mon = M - 1;     // 0-11
			timestamp.tm_mday = d;        // 1-31
			timestamp.tm_hour = h;        // 0-23
			timestamp.tm_min = m;         // 0-59
			timestamp.tm_sec = (int)s;    // 0-61 (0-60 in C++11)

			tm *ltm = localtime(&timestamp);
			std::stringstream stream;
			*/
			timeList.push_back(bars[j].t);
			openList.push_back(bars[j].o);
			highList.push_back(bars[j].h);
			lowList.push_back(bars[j].l);
			closeList.push_back(bars[j].c);
			volumeList.push_back(bars[j].v);
		}



		double SMA20 = getDeltaMovingAverage(20,closeList);
		double SMA50 = getDeltaMovingAverage(50,closeList);

		std::cout << "SMA20: " << SMA20 << std::endl;
		std::cout << "SMA50: " << SMA50 << std::endl;
		if(SMA20 > SMA50) {
			auto openPosition = api.get_position(assetsToTrade[i]);

			if(openPosition.qty == 0) {
				double cashBalance = api.get_account().cash;
				double targetPositionSize = cashBalance / (closeList.back() / positionSizing);
				auto order = api.submit_order(assetsToTrade[i],targetPositionSize,"buy","market","gtc");
				std::cout << order.qty << " shares of " << assetsToTrade[i] << " bought." << std::endl;
			}
		}
		else {
			auto openPosition = api.get_position(assetsToTrade[i]);
			if(openPosition.qty > 0) {
				auto order = api.submit_order(assetsToTrade[i],openPosition.qty,"sell","market","gtc");
				std::cout << order.qty << " shares sold." << std::endl;
			}
			else {
				std::cout << "No open positions for: " << assetsToTrade[i] << std::endl;
			}
		}
	}
	


	return 0;
}

/*
// Adjust date by a number of days +/-
void DatePlusDays( struct tm* date, int days )
{
    const time_t ONE_DAY = 24 * 60 * 60 ;

    // Seconds since start of epoch
    time_t date_seconds = mktime( date ) + (days * ONE_DAY) ;

    // Update caller's date
    // Use localtime because mktime converts to UTC so may change date
    *date = *localtime( &date_seconds ) ; ;
}

void prices(std::vector<std::string> symbols) {


	//time now
        time_t now = time(0);
        tm *ltm = localtime(&now);

	//time in NY
	struct tm NY;
	NY.tm_year = ltm->tm_year;
	NY.tm_mon = ltm->tm_mon;
	NY.tm_mday = ltm->tm_mday;
	NY.tm_hour = 9;
	NY.tm_min = 30;

	std::string end_dt;
	if(difftime(mktime(ltm),mktime(&NY)) > 0) {
		DatePlusDays(ltm, -1);
		std::stringstream stream;
		stream << std::put_time(ltm,"%Y-%m-%d");
		end_dt = stream.str();
	}

	return get_prices(symbols,ltm);
}

void get_prices(std::vector<std::string> symbols, tm* end_dt) {
	
	tm start_dt = *end_dt;
	DatePlusDays(&start_dt,-50);

	std::stringstream stream;
	//start date
	stream << std::put_time(&start_dt, "%Y-%m-%d");
	std::string start = stream.str();

	//end date
	stream << std::put_time(end_dt, "%Y-%m-%d");
	std::string end = stream.str();

	auto barset = api.get_barset(symbols,"day",50,start,end);
}

*/

