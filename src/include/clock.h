#ifndef CLOCK
#define CLOCK

#include <json/json.h>

class Clock {
	public:
		Clock(Json::Value);
		std::string timestamp;
		bool is_open;
		std::string next_open;
		std::string next_close;

		//Keep Json
		Json::Value json;
};

#endif
