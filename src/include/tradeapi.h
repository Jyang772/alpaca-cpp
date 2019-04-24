#ifndef TRADEAPI
#define TRADEAPI

#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <curl/curl.h>
#include <json/json.h>

#include "account.h"
#include "order.h"
#include "position.h"

class Tradeapi {
        public:
                void init(std::string, std::string, std::string);
		~Tradeapi();
		/* Account */
		//Json::Value getAccount();
		Account getAccount();

		/* Orders */
		Order submit_order(std::string, int qty, std::string, std::string, 
				   std::string, double limit_price=0, double stop_price=0, std::string client_order_id = "");
		std::vector<Order> list_orders(std::string status, int limit=50, std::string after="",
					       std::string until="", std::string direction="");
		Order get_order(std::string order_id);
		Order get_order_by_client_order_id(std::string client_order_id);
		void cancel_order(std::string order_id);

		/* Positions */
		std::vector<Position> list_positions(); 
		

        private:

                //WebAPI
		CURL *curl = NULL;
		Json::Value GET(std::string,std::string params="");
		Json::Value POST(std::string, std::string="");
		Json::Value DELETE(std::string, std::string="");
		
		static std::size_t callback(
			    const char* in,
			    std::size_t size,
			    std::size_t num,
			    char* out);

		//Construct GET URL w/ parameters
		std::string build_params(std::vector<std::string> params);
		//Build JSON string
		std::string build_json(std::vector<std::string> params);

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
