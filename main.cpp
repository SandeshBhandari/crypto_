#include <iostream>
#include <string>
#include <json.hpp>
#include "httpsrequest.h"

using namespace std;
using json = nlohmann::json;

int main(){
	string url_;
	string paramname_;
	string paramvalue_;
	cout << "Enter domain url(without parameter)";
	cin >> url_;
	cout << "Enter parameter name:";
	cin >> paramname_;
	cout << "Enter parameter value:";
	cin >> paramvalue_;
	
	Httpsrequest request_ = Httpsrequest();
	request_.seturl(url_);
	request_.setparam(paramname_, paramvalue_);

	request_.makerequest();

	return 0;
}
