#include "order.h"

Order::Order(Json::Value data) {
	id = data["id"].asString();
	client_order_id = data["client_order_id"].asString();
	created_at = data["created_at"].asString();
	updated_at = data["updated_at"].asString();
	submitted_at = data["submitted_at"].asString();
	filled_at = data["filled_at"].asString();
	expired_at = data["expired_at"].asString();
	canceled_at = data["canceled_at"].asString();
	asset_id = data["asset_id"].asString();
	symbol = data["symbol"].asString();
	exchange = data["exchange"].asString();
	asset_class = data["asset_class"].asString();
	qty = std::stod(data["qty"].asString());
	filled_qty = std::stod(data["filled_qty"].asString());
	type = data["type"].asString();
	side = data["side"].asString();
	time_in_force = data["time_in_force"].asString();
	limit_price = limit_price ? 0 : std::stod(data["limit_price"].asString());
	stop_price = stop_price ? 0 : std::stod(data["stop_price"].asString());
	status = data["status"].asString();
}
