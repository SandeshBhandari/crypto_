#include <iostream>
#include <string>
#include <json.hpp>
#include "httpsrequest.h"
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

void header(){
	cout << setw(10) << left << "" << setw(10) << left << "Ask" << setw(10) << left << "Bid" << setw(10) << left << "Last" << "\n";
}

int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "At least an argument required." << endl;
	}else{
		string option = argv[1];
		vector<string> values;
		string filename_ = "tracking.txt";
		fstream fs;
		for (int i = 2; i <= (argc - 1); ++i){
			values.push_back(argv[i]);
		}
		if (option == "a"){
			if (fs){
				fs.open(filename_, fstream::app | fstream::out);
			}
			for (auto i: values){
				cout << i << "\n";
				fs << i << "\n";
			}
		}else if (option == "r"){
			header();
			string url = "https://www.bittrex.com/api/v1.1/public/getticker?market=USDT-" + values[0];
			Httpsrequest request_ = Httpsrequest();
			request_.seturl(url);
			request_.makerequest();
			request_.getResult();
			request_.terminate();
		}else if(option == "l"){
			fs.open(filename_, fstream::in);
			vector<string> list;
			string str;
			while (getline(fs, str)){
				list.push_back(str);
			}
			header();
			for (auto i: list){
				string url = "https://www.bittrex.com/api/v1.1/public/getticker?market=USDT-" + i;
				Httpsrequest request_ = Httpsrequest();
				request_.seturl(url);
				request_.makerequest();
				request_.getResult();
				request_.terminate();
			}
		}
		fs.close();
	}
	return 0;
}
