#include <string>
#include <map>
#include <curl/curl.h>
#include "httpsrequest.h"
#include "json.hpp"
#include <iostream>

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
	curl_easy_setopt(c, CURLOPT_URL, finalurl_.c_str());
	//curl_easy_setopt(c, CURLOPT_WRITEFUNCTION ,Httpsrequest::callback);
	cout << curl_easy_perform(c);
}

void Httpsrequest::callback(){

}

json Httpsrequest::getResult() const{
	cout << "Nothing here right now";
	return "sj";
}
