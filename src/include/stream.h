#ifndef STREAM
#define STREAM

#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include <cpprest/ws_client.h>
#include <json/json.h>

class Stream {
	public:
		Stream();
		Stream(Json::Value);


		void init();
		void connect(std::string EndPoint, std::string KeyID, std::string SecretKey);
		Json::Value subscribe(std::vector<std::string> streams);
		Json::Value account_updates();
		Json::Value trade_updates();		
		//Keep Json
		Json::Value json;

	private:
		web::websockets::client::websocket_callback_client client;

};

#endif

