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
	std::cout << positions[0].symbol << std::endl;

	auto position = api.get_position("TSLA");

	//auto assets = api.list_assets();
	//std::cout << assets.size() << std::endl;
	//auto asset = api.get_asset("TSLA");

	return 0;
}
