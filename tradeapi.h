#include <string>
#include <curl/curl.h>

class Tradeapi {
        public:
                void init(std::string, std::string, std::string);
		std::string getAccount();
                void listPositions();
                void sendRequest();
        private:

                //WebAPI
		CURL *curl = NULL;
                std::string Get(std::string);

		//Authentication
		std::string base_url;
                std::string Endpoint;
                std::string KeyID;
                std::string SecretKey;
};
