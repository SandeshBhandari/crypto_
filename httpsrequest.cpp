#include <string>
#include <map>
#include <curl/curl.h>
#include "httpsrequest.h"
#include "json.hpp"
#include <iostream>
#include <cstdlib>

using json = nlohmann::json;

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
	curl_easy_cleanup(c);
	curl_global_cleanup();
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
	json j = json::parse(*userp);
	cout << j;	
	return totalsize;
}

json Httpsrequest::getResult() const{
	cout << "Nothing here right now";
	return "sj";
}
