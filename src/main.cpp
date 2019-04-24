#include <stdio.h>
#include <iostream>

#include "tradeapi.h"

int main() {

	std::cout << "hello" << std::endl;

	std::string EndPoint = "paper-api.alpaca.markets";
	std::string KeyID = "PKPUURFL462XO9XA1JW8";
	std::string SecretKey = "us4YPXtDQ4pEm10Qbwd7hWBK8ggslXScdAgBmRFp";

	Tradeapi api;
	api.init(EndPoint,KeyID,SecretKey);
	auto s = api.getAccount();

	std::cout << s.status << std::endl;
	std::cout << s.buying_power << std::endl;

	auto order = api.submit_order("TSLA",10,"buy","market","day");
	std::cout << order.symbol << std::endl;
		
	return 0;
}
