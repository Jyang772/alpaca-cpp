#include <iostream>
#include <chrono>
#include <thread>
#include <sstream>
#include <cpprest/ws_client.h>
#include <json/json.h>

using namespace std;
using namespace web;
using namespace web::websockets::client;


void message_handler(websocket_incoming_message msg)
{
  std::string input = msg.extract_string().get();
  std::cout << "Input: " << input << std::endl;
}


int main() {
        Json::Value streams;
        streams.append("account_updates");
        streams.append("trade_updates");

        Json::Value data;
        //data["streams"] = streams;

        /* Authentication */
        data["key_id"] = "PKPUURFL462XO9XA1JW8";
        data["secret_key"] = "us4YPXtDQ4pEm10Qbwd7hWBK8ggslXScdAgBmRFp";

        /* Order Updates */
        //data["streams"] = streams;

        Json::Value root;
        root["action"] = "authenticate";
        root["data"]=data;

	Json::StreamWriterBuilder builder;
	builder["indentation"] = "";
	std::string params = Json::writeString(builder,root);
	std::cout << params << std::endl;

	Json::CharReaderBuilder readerBuilder;
  	Json::CharReader * reader = readerBuilder.newCharReader();
	Json::Value noot;
	std::string errs;
	reader->parse(params.c_str(),params.c_str()+params.size(), &noot,&errs);
	//reader.parse(params, noot);
	std::cout << "NOOT: " << std::endl;
	std::cout << noot.toStyledString() << std::endl;


	web::websockets::client::websocket_callback_client client;
  client.connect("wss://paper-api.alpaca.markets/stream").wait();

  websocket_outgoing_message out_msg;
  out_msg.set_utf8_message(params);
  client.send(out_msg).wait();

client.set_message_handler([](websocket_incoming_message msg)
{

	std::cout << msg.length() << std::endl;
    auto is = msg.body();
    concurrency::streams::container_buffer<std::vector<uint8_t>> ret_data;
    is.read_to_end(ret_data).wait();

    char bufStr[msg.length()+1];
    memset(bufStr, 0, sizeof(bufStr));
    memcpy(&bufStr[0], &(ret_data.collection())[0], msg.length());

    std::cout << bufStr << std::endl;

});


  std::this_thread::sleep_for(std::chrono::seconds(1));


  	streams.clear();
	data.clear();
	root.clear();
        //streams.append("account_updates");
        streams.append("trade_updates");

        data["streams"] = streams;

        /* Authentication */
        //data["key_id"] = "PKPUURFL462XO9XA1JW8";
        //data["secret_key"] = "us4YPXtDQ4pEm10Qbwd7hWBK8ggslXScdAgBmRFp";

        /* Order Updates */
        data["streams"] = streams;

        root["action"] = "listen";
        root["data"]=data;

	params = Json::writeString(builder,root);
	std::cout << params << std::endl;

	out_msg.set_utf8_message(params);
	client.send(out_msg).wait();

	std::this_thread::sleep_for(std::chrono::seconds(1));

	streams.append("account_updates");
	data["streams"] = streams;
	root["data"] = data;
	params = Json::writeString(builder,root);
		
	out_msg.set_utf8_message(params);
	client.send(out_msg).wait();


	
	while(1) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	}

  client.close().wait();

  return 0;
}
