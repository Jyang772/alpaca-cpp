#ifndef TRADEAPI
#define TRADEAPI

#include <string>
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <json/json.h>

#include "account.h"
#include "order.h"

class Tradeapi {
        public:
                void init(std::string, std::string, std::string);
		~Tradeapi();
		//Json::Value getAccount();
		Account getAccount();
		Order submit_order(std::string, int qty, std::string, std::string, 
				   std::string, double stop_price=0, std::string client_order_id = "");
		std::vector<Order> list_orders(std::string status, int limit=50, std::string after="",
					       std::string until="", std::string direction="");	
                void listPositions();
                void sendRequest();

        private:

                //WebAPI
		CURL *curl = NULL;
		Json::Value GET(std::string,std::string params="");
		Json::Value POST(std::string, std::string);
		
		static std::size_t callback(
			    const char* in,
			    std::size_t size,
			    std::size_t num,
			    char* out);
			/*
		    {
			std::string data(in, (std::size_t) size * num);
			*((std::stringstream*) out) << data;
			return size * num;
		    }
		    */

		//Authentication
		std::string EndPoint;
		std::string base_url;
                std::string KeyID;
                std::string SecretKey;
};

inline size_t Tradeapi::callback(
	const char* in,
	std::size_t size,
	std::size_t num,
	char* out)
{
	std::string data(in, (std::size_t) size * num);
	*((std::stringstream*) out) << data;
	return size * num;
}

#endif
