#include "bar.h"


Bar::Bar(Json::Value data) {
	
	t = std::stod(data["t"].asString());
	o = std::stod(data["o"].asString());
	h = std::stod(data["h"].asString());
	l = std::stod(data["l"].asString());
	c = std::stod(data["c"].asString());
	v = std::stod(data["v"].asString());

	json = data;
}
