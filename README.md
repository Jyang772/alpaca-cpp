**Note: This is a work in progress. I just wanted to use Alpaca with C++.**

A simple SMA example based off of this [post](https://blog.alpaca.markets/blog/2018/7/24/building-a-simple-stock-trading-bot-by-using-brokerapi) is included.

To build:
```
$cd alpaca-cpp
$make
$./sma
```

# alpaca-cpp
C++ library for Alpaca trade API

`alpaca-cpp` is a C++ library for the Alpaca trade API. It allows rapid trading algo development easily, with support for the
both REST and ~~streaming interfaces~~. For details of each API behavior,
please see the online API document.

### REST example
```c++
#include "tradeapi.h"

Tradeapi api;
api.init(EndPoint,KeyID,SecretKey);
auto account = api.get_account();
auto positions = api.list_positions();
std::cout << positions[0].symbol << std::endl;
```

### Stream example
```c++
Stream s;
s.init(); //Hook up callback handler
s.connect("wss://paper-api.alpaca.markets/stream",KeyID,SecretKey);

std::vector<std::string> streams;
streams.push_back("trade_updates");
streams.push_back("account_updates");

s.subscribe(streams);

//Do whatever with streamed data using callback handler defined in stream.cpp or ... be bad:
Json::Value ret;
while(1) {
  std::this_thread::sleep_for(std::chrono::seconds(1));

  while(s.logged.size() > 0) {
    ret = s.logged.front();
    std::cout << "Stream: " << ret["stream"] << std::endl;
    if(ret["stream"] == "trade_updates") {
            std::cout << "Event: " << ret["data"]["event"] << std::endl;
            std::cout << "Qty: " << ret["data"]["order"]["qty"] << std::endl;
    }
    s.logged.pop_front();
  }
}
```

## API Document

The HTTP API document is located in https://docs.alpaca.markets/

## Authentication

The Alpaca API requires API key ID and secret key, which you can obtain from the
web console after you sign in.  You can pass `key_id` and `secret_key` to the initializers of
`REST` or `StreamConn` as arguments, or set up environment variables as
follows.

- APCA_API_KEY_ID: key ID
- APCA_API_SECRET_KEY: secret key

## Base URL

The base URL for API calls defaults to `https://api.alpaca.markets/`. This endpoint
is for live trading, and for paper trading and other purposes, you can to change
the base URL. You can pass `base_url` kwarg to `REST()`, or using the environment
variable, `APCA_API_BASE_URL`.

The environment variable `APCA_API_DATA_URL` can also be changed to configure the
endpoint for returning data from the `/bars` endpoint. By default, it will use
`https://data.alpaca.markets`.

## REST

The `REST` class is the entry point for the API request.  The instance of this
class provides all REST API calls such as account, orders, positions,
and bars.

