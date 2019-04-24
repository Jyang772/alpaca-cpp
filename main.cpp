#include <stdio.h>
#include <iostream>

#include "tradeapi.h"

int main() {

	std::cout << "hello" << std::endl;
	Tradeapi api;
	api.init("paper-api.alpaca.markets","PK899PYO6YVTYMU4TBYS","soDqkLmkGEmjk2PWKx4LX3Gejg3qqRLP4lwLVpv4");
	auto s = api.getAccount();
	std::cout << s.status << std::endl;
	std::cout << s.buying_power << std::endl;
	//std::cout << std::stod(s["buying_power"].asString()) << std::endl;
		
	return 0;
}
