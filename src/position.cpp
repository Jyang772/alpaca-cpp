#include "position.h"

Position::Position(Json::Value data) {
	asset_id = data["asset_id"].asString();
	symbol = data["symbol"].asString();
	exchange = data["exchange"].asString();
	asset_class = data["asset_class"].asString();
	avg_entry_price = std::stod(data["avg_entry_price"].asString());
	qty = std::stod(data["qty"].asString());
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
	
	json = data;
}
