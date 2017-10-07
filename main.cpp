#include <iostream>
#include <string>
#include <json.hpp>
#include "httpsrequest.h"
#include <vector>
#include <fstream>

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "At least an argument required." << endl;
	}else{
		Httpsrequest request_ = Httpsrequest();
		string option = argv[1];
		vector<string> values;
		string filename_ = "tracking.txt";
		fstream fs;
		for (int i = 2; i <= (argc - 1); ++i){
			values.push_back(argv[i]);
		}
		if (option == "a"){
			if (fs){
				fs.open(filename_, fstream::app);
			}else{
				fs.open(filename_, fstream::out);
			}	
			for (auto i: values){
				cout << i << "\n";
				fs << i << "\n";
			}
		}else if (option == "r"){
			string url = "https://www.bittrex.com/api/v1.1/public/getticker?market=USDT-" + values[0];
			request_.seturl(url);
			request_.makerequest();
		}else if(option == "l"){
		
		}
		fs.close();
	}
	return 0;
}
