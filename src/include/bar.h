#ifndef BAR
#define BAR

#include <json/json.h>

class Bar {
	public:
		Bar(Json::Value);
		
		std::string symbol;
		int t;
		double o;
		double h;
		double l;
		double c;
		double v;

		//Keep Json
		Json::Value json;

};

#endif

/*
{
  "AAPL": [
    {
      "t": 1544129220,
      "o": 172.26,
      "h": 172.3,
      "l": 172.16,
      "c": 172.18,
      "v": 3892,
    }
  ]
} 
*/
