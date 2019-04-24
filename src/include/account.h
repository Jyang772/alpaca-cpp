#ifndef ACCOUNT
#define ACCOUNT

#include <json/json.h>

class Account {
	public:
		Account(Json::Value);
		bool account_blocked;
		bool pattern_day_trader;
		bool trade_suspended_by_user;
		bool trading_blocked;
		bool transfers_blocked;

		double buying_power;
		double cash;
		double cash_withdrawable;
		double portfolio_value;

		std::string status;
		std::string created_at;
		std::string currency;
		std::string id;
};

#endif
