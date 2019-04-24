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
		//Json::Value getAccount();
		Account getAccount();
		Order submit_order();
                void listPositions();
                void sendRequest();
        private:

                //WebAPI
		CURL *curl = NULL;
		Json::Value Get(std::string);

		    static std::size_t callback(
			    const char* in,
			    std::size_t size,
			    std::size_t num,
			    char* out)
		    {
			std::string data(in, (std::size_t) size * num);
			*((std::stringstream*) out) << data;
			return size * num;
		    }

		//Authentication
		std::string EndPoint;
		std::string base_url;
                std::string KeyID;
                std::string SecretKey;
};
