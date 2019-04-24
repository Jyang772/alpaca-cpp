#include <stdio.h>
#include <iostream>

#include "tradeapi.h"

int main() {

	std::cout << "hello" << std::endl;

	std::string EndPoint = "paper-api.alpaca.markets";
	std::string KeyID = "PKPUURFL462XO9XA1JW8";
	std::string SecretKey = "us4YPXtDQ4pEm10Qbwd7hWBK8ggslXScdAgBmRFp";

	Tradeapi api; //REST
	api.init(EndPoint,KeyID,SecretKey);
	
/*	
	//Test getAccount
	auto s = api.getAccount();
	std::cout << s.status << std::endl;
	std::cout << s.buying_power << std::endl;
	std::cout << s.json.toStyledString() << std::endl;
*/

	//Test submit_order
	auto order = api.submit_order("TSLA",10,"buy","market","day");
	std::cout << order.symbol << std::endl;

	//Test list_orders
	auto orders = api.list_orders("open");
	std::cout << orders[0].symbol << std::endl;
	std::cout << orders[0].json.toStyledString() << std::endl;
	return 0;
}
