#include <stdio.h>
#include <iostream>

#include "tradeapi.h"

int main() {

	std::cout << "hello" << std::endl;
	Tradeapi api;
	api.init("paper-api.alpaca.markets","PK899PYO6YVTYMU4TBYS","soDqkLmkGEmjk2PWKx4LX3Gejg3qqRLP4lwLVpv4");
	auto s = api.getAccount();
	//api.submit_order();

	std::cout << s.status << std::endl;
	std::cout << s.buying_power << std::endl;
		
	return 0;
}
