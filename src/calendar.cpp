#include "calendar.h"


Calendar::Calendar(Json::Value data) {
	
	date = data["date"].asString();
	open = data["open"].asString();
	close = data["close"].asString();

	json = data;
}
