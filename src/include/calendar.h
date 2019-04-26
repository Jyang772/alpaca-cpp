#ifndef CALENDAR
#define CALENDAR

#include <json/json.h>

class Calendar {
	public:
		Calendar(Json::Value);
		std::string date;
		std::string open;
		std::string close;

		//Keep Json
		Json::Value json;
};

#endif
