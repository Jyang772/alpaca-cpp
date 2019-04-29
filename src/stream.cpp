#include "stream.h"

Stream::Stream() {}
/*
Stream::Stream(Json::Value data) {
	
	json = data;
}


Json::Value Stream::account_updates() {


}
*/


void Stream::trade_updates() {

	Json::Value stream;
	Json::Value data;
	Json::Value root;

	stream.append("trade_updates");
	data["streams"] = stream;
	root["action"] = "listen";
	root["data"] = data;
}

void Stream::init() {

	client.set_message_handler([&](web::websockets::client::websocket_incoming_message msg)
	{

		//Parse server response, whether it is trade_update or account_update
		//std::cout << msg.length() << std::endl;
		auto is = msg.body();
		concurrency::streams::container_buffer<std::vector<uint8_t>> ret_data;
		is.read_to_end(ret_data).wait();

		char bufStr[msg.length()+1];
		memset(bufStr, 0, sizeof(bufStr));
		memcpy(&bufStr[0], &(ret_data.collection())[0], msg.length());

		Json::CharReaderBuilder readerBuilder;
		Json::CharReader * reader = readerBuilder.newCharReader();
		Json::Value noot;
		std::string errs;
		reader->parse(bufStr,bufStr+sizeof(bufStr), &noot,&errs);
		//std::cout << bufStr << std::endl;
		//std::cout << noot.toStyledString() << std::endl;

		logged.push_back(noot);
	});
}

void Stream::connect(std::string EndPoint, std::string KeyID, std::string SecretKey) {

	client.connect(EndPoint).wait();

        Json::Value data;
        /* Authentication */
        data["key_id"] = KeyID;
        data["secret_key"] = SecretKey;

        Json::Value root;
        root["action"] = "authenticate";
        root["data"]=data;

        Json::StreamWriterBuilder builder;
        builder["indentation"] = "";
        std::string params = Json::writeString(builder,root);

	web::websockets::client::websocket_outgoing_message out_msg;
	out_msg.set_utf8_message(params);
  	client.send(out_msg).wait();
}


void Stream::subscribe(std::vector<std::string> selected_streams) {

	Json::Value streams;
	Json::Value data;
	Json::Value root;
	
	for(int i=0; i<selected_streams.size(); i++)
		streams.append(selected_streams[i]);

	data["streams"] = streams;
	root["action"] = "listen";
	root["data"] = data;

	Json::StreamWriterBuilder builder;
        builder["indentation"] = "";
        std::string params = Json::writeString(builder,root);

	web::websockets::client::websocket_outgoing_message out_msg;
	out_msg.set_utf8_message(params);
  	client.send(out_msg).wait();
}	

