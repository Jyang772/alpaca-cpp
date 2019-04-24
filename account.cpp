#include "account.h"


Account::Account(Json::Value resp) {

	account_blocked = resp["account_blocked"].asBool();
	buying_power = std::stod(resp["buying_power"].asString());
	cash = std::stod(resp["cash"].asString());
	cash_withdrawable = std::stod(resp["cash_withdrawable"].asString());
	created_at = resp["created_at"].asString();
	currency = resp["currency"].asString();
	id = resp["id"].asString();
	pattern_day_trader = resp["pattery_day_trader"].asBool();
	portfolio_value = std::stod(resp["portfolio_value"].asString());
	status = resp["status"].asString();
	trade_suspended_by_user = resp["trade_suspended_by_user"].asBool();
	trading_blocked = resp["trading_blocked"].asBool();
	transfers_blocked = resp["transfers_blocked"].asBool();
}
