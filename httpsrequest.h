#ifndef HTTPSREQUEST_h
#define HTTPSREQUEST_h

#include <string>
#include <map>
#include <curl/curl.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;


class Httpsrequest{
	public:
		Httpsrequest();
		void seturl(string url);
		void setparam(string param_name, string param_value); 
		void makerequest();
		json getResult() const;
		void terminate();

	private:
		CURL* c;
		string url_;
		map<string,string> param_;
		static void callback();
		
};

#endif
