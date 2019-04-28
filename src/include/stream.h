#ifndef STREAM
#define STREAM

#include <json/json.h>

class Stream {
	public:
		Stream(Json::Value);

		Json::Value subscribe(std::vector<std::string> streams);
		Json::Value account_updates();
		Json::Value trade_updates();		
		//Keep Json
		Json::Value json;

};

#endif

