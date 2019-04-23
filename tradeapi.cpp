#include "tradeapi.h"

void Tradeapi::init(std::string EndPoint, std::string KeyID, std::string SecretKey) {

}

std::string Tradeapi::getAccount() {

        std::string resp;
        resp = Get("/account");
        return resp;
}

std::string Tradeapi::Get(std::string req) {

	std::string request;
	std::string resp;

	request = base_url + req;

	curl_easy_setopt(curl, CURLOPT_URL, request);
	curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT,10);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	struct curl_slist *chunk = NULL;
	const std::string keyid = "APCA-API-KEY-ID: " + KeyID;
	const std::string secret = "APCA-API-SECRET-KEY: " + SecretKey;
	chunk = curl_slist_append(chunk, keyid.c_str());
	chunk = curl_slist_append(chunk, secret.c_str());

	return resp;
}
