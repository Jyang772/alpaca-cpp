#define CURL_STATICLIB
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#include <curl/curl.h>
#include <json/json.h>
namespace
{
    std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            char* out)
    {
        std::string data(in, (std::size_t) size * num);
        *((std::stringstream*) out) << data;
        return size * num;        
    }
}

int main()
{
    const std::string url("https://paper-api.alpaca.markets/v1/account");

    CURL* curl = curl_easy_init();

    // Set remote URL.
    curl_easy_setopt(curl, CURLOPT_URL,"https://paper-api.alpaca.markets/v1/account" );

    // Don't bother trying IPv6, which would increase DNS resolution time.
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);

    // Don't wait forever, time out after 10 seconds.
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);

    // Follow HTTP redirects if necessary.
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

	struct curl_slist *chunk = NULL;
	chunk = curl_slist_append(chunk, "APCA-API-KEY-ID: PK899PYO6YVTYMU4TBYS");
	chunk = curl_slist_append(chunk, "APCA-API-SECRET-KEY: soDqkLmkGEmjk2PWKx4LX3Gejg3qqRLP4lwLVpv4");

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER,chunk);

    // Response information.
    long httpCode(0);
    // std::unique_ptr<std::string> httpData(new std::string());

    std::stringstream httpData;

    // Hook up data handling function.
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);

    // Hook up data container (will be passed as the last parameter to the
    // callback handling function).  Can be any pointer type, since it will
    // internally be passed as a void pointer.
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &httpData);

    // Run our HTTP GET command, capture the HTTP response code, and clean up.
    curl_easy_perform(curl);
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    curl_easy_cleanup(curl);

    if (httpCode == 200)
    {
        std::cout << "\nGot successful response from " << url << std::endl;

        // Response looks good - done using Curl now.  Try to parse the results
        // and print them out.
        Json::Value jsonData;
        Json::CharReaderBuilder jsonReader;
        std::string errs;

        if (Json::parseFromStream(jsonReader, httpData, &jsonData, &errs))
            // jsonReader.parse(httpData, jsonData))
        {
            std::cout << "Successfully parsed JSON data" << std::endl;
            std::cout << "\nJSON data received:" << std::endl;
            std::cout << jsonData.toStyledString() << std::endl;

	    std::cout << noot << std::endl;
            const std::string dateString(jsonData["date"].asString());
            const std::size_t unixTimeMs(
                    jsonData["milliseconds_since_epoch"].asUInt64());
            const std::string timeString(jsonData["time"].asString());

            std::cout << "Natively parsed:" << std::endl;
            std::cout << "\tDate string: " << dateString << std::endl;
            std::cout << "\tUnix timeMs: " << unixTimeMs << std::endl;
            std::cout << "\tTime string: " << timeString << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "Could not parse HTTP data as JSON" << std::endl;
            std::cout << "HTTP data was:\n" << httpData.str() << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
        return 1;
    }

    return 0;
}
