#include "position.h"

Position::Position(Json::Value data) {
	asset_id = data["asset_id"].toString();
	symbol = data["symbol"].toString();
	exchange = data["exchange"].toString();
	asset_class = data["asset_class"].toString();
	avg_entry_price = std::stod(data["avg_entry_price"].toString());
	qty = std::stod(data["qty"].toString());
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



}
