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
		void makerequest();
		void getResult() const;
		void terminate();

	private:
		CURL* c;
		string url_;
		static json j;
		static size_t callback(void *buffer, size_t size, size_t nmemb, string *userp);
		
};

#endif
