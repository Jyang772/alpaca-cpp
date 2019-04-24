#include <stdio.h>
#include <iostream>

#include "tradeapi.h"

int main() {

	std::cout << "hello" << std::endl;
	Tradeapi api;
	api.init("paper-api.alpaca.markets","PKPUURFL462XO9XA1JW8","us4YPXtDQ4pEm10Qbwd7hWBK8ggslXScdAgBmRFp");
	auto s = api.getAccount();

	std::cout << s.status << std::endl;
	std::cout << s.buying_power << std::endl;

	api.submit_order("TSLA",10,"buy","market","day");
		
	return 0;
}
