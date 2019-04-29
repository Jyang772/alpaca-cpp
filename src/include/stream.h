#ifndef STREAM
#define STREAM

#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include <cpprest/ws_client.h>
#include <json/json.h>
#include <list>

class Stream {
	public:
		Stream();
		Stream(Json::Value);


		void init();
		void connect(std::string EndPoint, std::string KeyID, std::string SecretKey);
		void subscribe(std::vector<std::string> streams);
		Json::Value account_updates();
		void trade_updates();		
		//Keep Json
		Json::Value json;

		std::list<Json::Value> logged;
	private:
		web::websockets::client::websocket_callback_client client;
		//concurrency::streams::container_buffer<std::vector<uint8_t>> ret_data;

};

#endif

