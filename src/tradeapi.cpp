#include "tradeapi.h"

void Tradeapi::init(std::string EndPoint, std::string KeyID, std::string SecretKey) {
	this->EndPoint = EndPoint;
	this->KeyID = KeyID;
	this->SecretKey = SecretKey;	
	this->base_url = "https://" + EndPoint + "/v1";

	this->curl = curl_easy_init();
}

Tradeapi::~Tradeapi() {
	curl_easy_cleanup(curl);
}

Json::Value Tradeapi::GET(std::string req,std::string params) {

	std::string request;
	Json::Value jsonData;

	request = base_url + req + params;

	std::cout << "request: " + request << std::endl;

	curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,10);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	struct curl_slist *chunk = NULL;
	std::string keyid = "APCA-API-KEY-ID: " + KeyID;
	std::string secret = "APCA-API-SECRET-KEY: " + SecretKey;


	chunk = curl_slist_append(chunk, keyid.c_str());
	chunk = curl_slist_append(chunk, secret.c_str());

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

	//Response information
	long httpCode(0);
	std::stringstream httpData;
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);

	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	//curl_easy_cleanup(curl);

	//std::cout << "httpCode: " << httpCode << std::endl;

	if(httpCode==200) {
		//std::cout << "200" << std::endl;
		//Json::Value jsonData;
		Json::CharReaderBuilder jsonReader;
		std::string errs;

		if(Json::parseFromStream(jsonReader, httpData, &jsonData, &errs)) {
			std::cout << "\nJSON data received: " << std::endl;
			std::cout << jsonData.toStyledString() << std::endl;	
		}
	}
	return jsonData;
}

Json::Value Tradeapi::POST(std::string req,std::string params) {

	std::string request;
	Json::Value jsonData;

	request = base_url + req;

	std::cout << "request: " << request << std::endl;
	std::cout << "params: " << params << std::endl;

	curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,10);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	struct curl_slist *chunk = NULL;
	std::string keyid = "APCA-API-KEY-ID: " + KeyID;
	std::string secret = "APCA-API-SECRET-KEY: " + SecretKey;


	chunk = curl_slist_append(chunk, keyid.c_str());
	chunk = curl_slist_append(chunk, secret.c_str());

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);

	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());

	//Response information
	long httpCode(0);
	std::stringstream httpData;
	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);

	curl_easy_perform(curl);
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	//curl_easy_cleanup(curl);

	std::cout << "httpCode: " << httpCode << std::endl;

	if(httpCode==200) {
		//std::cout << "200" << std::endl;
		//Json::Value jsonData;
		Json::CharReaderBuilder jsonReader;
		std::string errs;

		if(Json::parseFromStream(jsonReader, httpData, &jsonData, &errs)) {
			std::cout << "\nJSON data received: " << std::endl;
			std::cout << jsonData.toStyledString() << std::endl;	
		}
	}
	return jsonData;
}

//Json::Value Tradeapi::getAccount() {
Account Tradeapi::getAccount() {

	Json::Value resp;
        resp = GET("/account");
        //return resp;
	return Account(resp);
}

Order Tradeapi::submit_order(std::string symbol, int qty, std::string side, std::string type, std::string time_in_force, double stop_price, std::string client_order_id) {

	std::cout << "submit_order" << std::endl;
	Json::Value data;
	Json::Value resp;

	data["symbol"] = symbol;
	data["qty"] = std::to_string(qty);
	data["side"] = side;
	data["type"] = type;
	data["time_in_force"] = time_in_force;

	Json::StreamWriterBuilder builder;
	builder["indentation"] = "";
	std::string params = Json::writeString(builder,data);

	resp = POST("/orders",params);
	return Order(resp);
}

std::vector<Order> Tradeapi::list_orders(std::string status="open", int limit, std::string after,
                                               std::string until, std::string direction) {
	//todo: Move out into function
	/*
	Json::Value data;
	data["status"] = status;
	data["limit"] = limit;
	data["after"] = after;
	data["until"] = until;
	data["direction"] = direction;

	Json::StreamWriterBuilder builder;
	builder["indentation"] = "";
	std::string params = Json::writeString(builder,data);
	*/
	std::string params = "?";
	params += "status=open";

	Json::Value resp;
	resp = GET("/orders",params);
	std::vector<Order> noot(std::begin(resp), std::end(resp));
	return noot;
}



