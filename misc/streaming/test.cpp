#include <iostream>
#include <json/json.h>



int main() {

	Json::Value streams;
	streams.append("account_updates");
	streams.append("trade_updates");

	Json::Value data;
	//data["streams"] = streams;

	/* Authentication */
	data["key_id"] = "API_KEY";
	data["secret_key"] = "API_SECRET";

	/* Order Updates */
	data["streams"] = streams;

	Json::Value root;
	root["action"] = "listen";  
	root["data"]=data;

	std::cout << root.toStyledString() << std::endl;

	std::cout << root["data"]["key_id"] << std::endl;
}
