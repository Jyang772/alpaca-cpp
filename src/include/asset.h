#ifndef ASSET
#define ASSET

#include <json/json.h>

class Asset {
	public:
		Asset(Json::Value);

		std::string id;
		std::string asset_class;
		std::string exchange;
		std::string symbol;
		std::string status;
		bool tradable;

		//Keep Json
		Json::Value json;

};

#endif

/*
{
  "id": "904837e3-3b76-47ec-b432-046db621571b",
  "asset_class": "us_equity",
  "exchange": "NASDAQ",
  "symbol": "AAPL",
  "status": "active",
  "tradable": true
}
*/
