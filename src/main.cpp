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

Tradeapi api;

int main() {

	std::cout << "hello" << std::endl;

	std::string EndPoint = "paper-api.alpaca.markets";
	std::string KeyID = "PKPUURFL462XO9XA1JW8";
	std::string SecretKey = "us4YPXtDQ4pEm10Qbwd7hWBK8ggslXScdAgBmRFp";

	//Tradeapi api; //REST
	api.init(EndPoint,KeyID,SecretKey);
	
/*	
	//Test getAccount
	
	auto s = api.getAccount();
	std::cout << s.status << std::endl;
	std::cout << s.buying_power << std::endl;
	std::cout << s.json.toStyledString() << std::endl;



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
	//std::cout << positions[0].symbol << std::endl;

	auto position = api.get_position("TSLA");

	//auto assets = api.list_assets();
	//std::cout << assets.size() << std::endl;
	//auto asset = api.get_asset("TSLA");
	//
*/
	std::vector<std::string> symbols;
	symbols.push_back("TSLA");
	auto bars = api.get_barset(symbols,"1Min",1000);

	std::vector<Bar> tsla_bars(std::begin(bars["TSLA"]),std::end(bars["TSLA"]));
	printf("TSLA day's change: %.3f%\n",(tsla_bars.back().c - tsla_bars[0].c)/tsla_bars[0].c * 100);

	printf("TSLA BARS: \n");
	for(int i=tsla_bars.size()-1; i>=990; i--)
		printf("%.2f\n",tsla_bars[i].c);

	
	auto clock = api.get_clock();
	auto now = clock.timestamp;
	std::cout << "Now: "  << now << std::endl;
	
	
	struct tm done;
	done.tm_year = 1900;
	done.tm_mon = 1;
	done.tm_mday = 0;	

	std::string dateStr = now;
	int y,M,d,h,m;
	float s;
	sscanf(dateStr.c_str(), "%d-%d-%dT%d:%d:%fZ", &y, &M, &d, &h, &m, &s);
	struct tm now_tm;
	now_tm.tm_year = y - 1900; // Year since 1900
	now_tm.tm_mon = M - 1;     // 0-11
	now_tm.tm_mday = d;        // 1-31

	if(clock.is_open && difftime(mktime(&done),mktime(&now_tm))) {
	
		//api.get_bar		
		done = now_tm;
	}

	time_t now_ = time(0);
	tm *ltm = localtime(&now_);
	DatePlusDays(ltm,-1);

	std::stringstream stream;
	stream << std::put_time(ltm, "%Y-%m-%d %H:%M:%S");
	std::cout << "Now -1 day: " << stream.str() << std::endl;

	//prices(symbols);

	return 0;
}


// Adjust date by a number of days +/-
void DatePlusDays( struct tm* date, int days )
{
    const time_t ONE_DAY = 24 * 60 * 60 ;

    // Seconds since start of epoch
    time_t date_seconds = mktime( date ) + (days * ONE_DAY) ;

    if(days < 0) {
	date->tm_hour = 23;
        date->tm_min = 59;
        date->tm_sec = 0;
    }
    // Update caller's date
    // Use localtime because mktime converts to UTC so may change date
    *date = *localtime( &date_seconds ) ; ;

	if(days < 0) {
		date->tm_hour = 23;
		date->tm_min = 59;
		date->tm_sec = 0;
	}

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

	/* Subtract time now from 0930EST 
	 * If the time now is greater 
	 * */
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




