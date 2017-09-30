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
	
void Httpsrequest::setparam(string param_name, string param_value){
	param_[param_name] = param_value;
}

void Httpsrequest::makerequest(){
	string finalurl_ = url_ + "?";
	string paramcombo_ = "";
	map<string,string>::iterator it = param_.begin();
	paramcombo_ = it->first + "=" + it->second;
	it++;
	while (it != param_.end()){
		paramcombo_ += "&";
		paramcombo_ = paramcombo_ + it->first + "=" + it->second;	
		it++;
	}
	finalurl_ += paramcombo_;
	cout << finalurl_ << endl;
	string s = "";
	curl_easy_setopt(c, CURLOPT_URL, finalurl_.c_str());
	curl_easy_setopt(c, CURLOPT_WRITEFUNCTION , &Httpsrequest::callback);
	curl_easy_setopt(c, CURLOPT_WRITEDATA, &s);
	curl_easy_perform(c);
	curl_easy_cleanup(c);
	curl_global_cleanup();
}
size_t Httpsrequest::callback(void *buffer, size_t size, size_t nmemb, string *userp){
	//printf("%s", (char*)userp);
	//if (!userp){
	//	cout << "userp is null!!" << endl;
	//}
	size_t totalsize = size * nmemb;
	size_t oldsize = userp->size();
	try{
		userp->resize(oldsize + totalsize);
		//userp = (string *)realloc((char*)userp, oldsize + totalsize);

	}catch(bad_alloc &e){
		printf("Error while resizing");
	}
	char* buffstr_ = new char[userp->size() + 1]; 
	std::copy((char *)buffer, (char *)buffer+totalsize, buffstr_);
	buffstr_[userp->size()] = '\0';
	string str(buffstr_);
	delete[] buffstr_;
	userp = &str;
	cout << *userp << endl;	
	return totalsize;
}

json Httpsrequest::getResult() const{
	cout << "Nothing here right now";
	return "sj";
}
