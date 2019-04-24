#include <stdio.h>
#include <iostream>

#include "tradeapi.h"

#include <unistd.h>

int main() {

	std::cout << "hello" << std::endl;

	std::string EndPoint = "paper-api.alpaca.markets";
	std::string KeyID = "PKPUURFL462XO9XA1JW8";
	std::string SecretKey = "us4YPXtDQ4pEm10Qbwd7hWBK8ggslXScdAgBmRFp";

	Tradeapi api; //REST
	api.init(EndPoint,KeyID,SecretKey);
	
	
	//Test getAccount
	/*
	auto s = api.getAccount();
	std::cout << s.status << std::endl;
	std::cout << s.buying_power << std::endl;
	std::cout << s.json.toStyledString() << std::endl;
	*/


	//Test submit_order
	auto order = api.submit_order("TSLA",10,"buy","market","day");
	std::cout << order.symbol << std::endl;

	//Test list_orders
	
	//auto orders = api.list_orders("open");
	//std::cout << orders[0].symbol << std::endl;
	//std::cout << orders[0].json.toStyledString() << std::endl;
	

	auto orders = api.list_orders("open");
	//Test get_order{order_id}
	auto order_ = api.get_order("2fd3f1c6-98ca-4f4c-a4d4-bda4d5765419");
	auto order_by_client_id = api.get_order_by_client_order_id("0664a1d8-7613-4b4c-b473-5bb5644e0014");

	return 0;
}
