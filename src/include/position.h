#ifndef POSITON
#define POSITION

#include <json/json.h>

class Position {
	public:
		Position(std::string symbol);
		Position(Json::Value);

		std::string asset_id;
		std::string symbol;
		std::string exchange;
		std::string asset_class;
		double avg_entry_price;
		int qty;
		std::string side;
		double market_value;
		double cost_basis;
		std::string unrealized_pl;
		double unrealized_plpc;
		double unrealized_intraday_pl;
		double unrealized_intraday_plpc;

		double current_price;
		double lastday_price;
		double change_today;


		//Keep Json
		Json::Value json;

};

#endif



/*
 * {
  "asset_id": "904837e3-3b76-47ec-b432-046db621571b",
  "symbol": "AAPL",
  "exchange": "NASDAQ",
  "asset_class": "us_equity",
  "avg_entry_price": "100.0",
  "qty": "5",
  "side": "long",
  "market_value": "600.0",
  "cost_basis": "500.0",
  "unrealized_pl": "100.0",
  "unrealized_plpc": "0.20",
  "unrealized_intraday_pl": "10.0",
  "unrealized_intraday_plpc": "0.0084",
  "current_price": "120.0",
  "lastday_price": "119.0",
  "change_today": "0.0084"
}
*/
