#include "tradeapi.h"

void Tradeapi::init(std::string EndPoint, std::string KeyID, std::string SecretKey) {
	this->EndPoint = EndPoint;
	this->KeyID = KeyID;
	this->SecretKey = SecretKey;	
	this->base_url = "https://" + EndPoint + "/v1";

	this->curl = curl_easy_init();
}

//Json::Value Tradeapi::getAccount() {
Account Tradeapi::getAccount() {

	Json::Value resp;
        resp = Get("/account");
        //return resp;
	return Account(resp);
}

Json::Value Tradeapi::Get(std::string req) {

	std::string request;
	Json::Value jsonData;

	request = base_url + req;

	//std::cout << "request: " + request << std::endl;

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
	curl_easy_cleanup(curl);

	//std::cout << "httpCode: " << httpCode << std::endl;

	if(httpCode==200) {
		//std::cout << "200" << std::endl;
		//Json::Value jsonData;
		Json::CharReaderBuilder jsonReader;
		std::string errs;

		if(Json::parseFromStream(jsonReader, httpData, &jsonData, &errs)) {
			//std::cout << "\nJSON data received: " << std::endl;
			//std::cout << jsonData.toStyledString() << std::endl;	
		}
	}
	return jsonData;
}
