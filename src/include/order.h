#ifndef ORDER
#define ORDER

#include <json/json.h>

class Order {
	public:
		Order(Json::Value);
		std::string id;
		std::string client_order_id;
		std::string created_at;
		std::string updated_at;
		std::string submitted_at;
		std::string filled_at;
		std::string expired_at;
		std::string canceled_at;
		std::string asset_id;
		std::string symbol;
		std::string exchange;
		std::string asset_class;
		double qty;
		std::string filled_qty;
		std::string type;
		std::string side;
		std::string time_in_force;
		double limit_price;
		double stop_price;
		std::string status;

		//Keep Json
		Json::Value json;

};

#endif
