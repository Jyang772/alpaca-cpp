#include "tradeapi.h"

void Tradeapi::init(std::string EndPoint, std::string KeyID, std::string SecretKey) {
	this->EndPoint = EndPoint;
	this->KeyID = KeyID;
	this->SecretKey = SecretKey;	
	this->base_url = "https://" + EndPoint + "/v1";

	//this->curl = curl_easy_init();
}

Tradeapi::~Tradeapi() {
	//curl_easy_cleanup(curl);
}

std::string Tradeapi::build_params(std::vector<std::string> params) {

	std::string ret = "?";	
	for(int i=0; i<params.size(); i++) {
		if(i > 0)
			ret += "&";
		ret += params[i];
	}
	return ret;
}

Json::Value Tradeapi::GET(std::string req,std::string params,std::string endpoint) {

	std::string request;
	Json::Value jsonData;

	if(endpoint.size() > 0)
		request = "https://" + endpoint + req + params;
	else
		request = base_url + req + params;

	std::cout << "request: " + request << std::endl;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,20);
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
	curl_easy_cleanup(curl);

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

Json::Value Tradeapi::POST(std::string req,std::string params) {

	std::string request;
	Json::Value jsonData;

	request = base_url + req;

	std::cout << "request: " << request << std::endl;
	std::cout << "params: " << params << std::endl;

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,20);
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
	curl_easy_cleanup(curl);

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

Json::Value Tradeapi::DELETE(std::string req,std::string params) {

        std::string request;
        Json::Value jsonData;

        request = base_url + req + params;

        std::cout << "request: " + request << std::endl;

        curl = curl_easy_init();
        curl_easy_setopt(curl, CURLOPT_URL, request.c_str());
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT,20);
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
        curl_easy_cleanup(curl);

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

Order Tradeapi::submit_order(std::string symbol, int qty, std::string side, std::string type, std::string time_in_force, double limit_price,double stop_price, std::string client_order_id) {

	std::cout << "submit_order" << std::endl;
	Json::Value data;
	Json::Value resp;

	data["symbol"] = symbol;
	data["qty"] = std::to_string(qty);
	data["side"] = side;
	data["type"] = type;
	data["time_in_force"] = time_in_force;

	if(type == "limit")	
		data["limit_price"] = limit_price;
	if(type == "stop" || type == "stop_limit")
		data["stop_price"] = stop_price;

	Json::StreamWriterBuilder builder;
	builder["indentation"] = "";
	std::string params = Json::writeString(builder,data);

	resp = POST("/orders",params);
	return Order(resp);
}

std::vector<Order> Tradeapi::list_orders(std::string status="open", int limit, std::string after,
                                               std::string until, std::string direction) {
	//todo: Move out into function
	//std::string params = "?";
	//params += "status=open";
	std::vector<std::string> params;
	params.push_back("status="+status);

	Json::Value resp;
	resp = GET("/orders",build_params(params));
	std::vector<Order> noot(std::begin(resp), std::end(resp));
	return noot;
}

Order Tradeapi::get_order(std::string order_id) {
	Json::Value resp = GET("/orders/" + order_id);	
	//Json::Value resp;	
	return Order(resp);
}

Order Tradeapi::get_order_by_client_order_id(std::string client_order_id) {
	std::cout << "get_order_by_client_order\n";
	std::vector<std::string> params;
	params.push_back("client_order_id="+client_order_id);

	Json::Value resp = GET("/orders:by_client_order_id",build_params(params));
	return Order(resp);
}

void Tradeapi::cancel_order(std::string order_id) {
	Json::Value resp = DELETE("/orders/" + order_id);
	return;	
}

std::vector<Position> Tradeapi::list_positions() {
	Json::Value resp = GET("/positions");

	std::vector<Position> noot(std::begin(resp),std::end(resp)); 
	return noot;
}

Position Tradeapi::get_position(std::string symbol) {
	Json::Value resp = GET("/positions/" + symbol);
	return Position(resp);
}

std::vector<Asset> Tradeapi::list_assets(std::string status, std::string asset_class) {

	std::vector<std::string> params;
	params.push_back("status="+status);
	params.push_back("asset_class="+asset_class);
	Json::Value resp = GET("/assets",build_params(params));

	std::vector<Asset> noot(std::begin(resp),std::end(resp));
	return noot;
}

Asset Tradeapi::get_asset(std::string symbol) {
	Json::Value resp = GET("/assets/"+symbol);
	return Asset(resp);
}

std::vector<Bar> Tradeapi::get_barset(std::vector<std::string> symbols, std::string timeframe, std::string limit,
			              std::string start, std::string end, std::string after, std::string until) {

	std::string params = "?symbols=";
	for(int i=0; i<symbols.size(); i++) {
		params += symbols[i];
		if(i < symbols.size()-1)
			params += ",";
	}
		

	Json::Value resp = GET("/bars/"+timeframe,params,"data.alpaca.markets/v1/");
	std::cout << "BUNNY" << std::endl;
	Json::Value::ArrayIndex i = 0;
	std::vector<Bar> noot(std::begin(resp[symbols[0]]),std::end(resp[symbols[0]]));
	return noot;
}
