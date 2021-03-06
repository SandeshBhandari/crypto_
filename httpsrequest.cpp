#include <string>
#include <map>
#include <curl/curl.h>
#include "httpsrequest.h"
#include "json.hpp"
#include <iostream>
#include <cstdlib>
#include <iomanip>

using json = nlohmann::json;

json Httpsrequest::j;

Httpsrequest::Httpsrequest(){
	curl_global_init(CURL_GLOBAL_ALL);
	c = curl_easy_init();
}

void Httpsrequest::seturl(string url){
	url_ = url;
}
	
void Httpsrequest::makerequest(){
	string s = "";
	curl_easy_setopt(c, CURLOPT_URL, url_.c_str());
	curl_easy_setopt(c, CURLOPT_WRITEFUNCTION , &Httpsrequest::callback);
	curl_easy_setopt(c, CURLOPT_WRITEDATA, &s);
	curl_easy_perform(c);
}

size_t Httpsrequest::callback(void *buffer, size_t size, size_t nmemb, string *userp){
	size_t totalsize = size * nmemb;
	size_t oldsize = userp->size();
	try{
		userp->resize(oldsize + totalsize);
	}catch(bad_alloc &e){
		printf("Error while resizing");
	}
	char* buffstr_ = new char[userp->size() + 1]; 
	std::copy((char *)buffer, (char *)buffer+totalsize, buffstr_);
	buffstr_[userp->size()] = '\0';
	string str(buffstr_);
	delete[] buffstr_;
	userp = &str;
	j = json::parse(*userp);
	return totalsize;
}

void Httpsrequest::terminate() const{
	curl_easy_cleanup(c);
	curl_global_cleanup();
}

void  Httpsrequest::getResult() const{
	int pos = url_.find("USDT-");
	string currency = url_.substr(pos + 5, url_.length());
	if (j["success"].get<bool>() == true){
		cout << setw(10) << left << currency << setw(10) << left << j["result"]["Ask"].get<double>() << setw(10) << left << j["result"]["Bid"].get<double>() << setw(10) << left << j["result"]["Last"].get<double>() << "\n";
	}else{
		cout << "Error while getting the values. Check currency entered!\n";
	}

}
