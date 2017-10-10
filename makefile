build: main.cpp httpsrequest.cpp
	brew tap nlohmann/json ;\
	brew install nlohmann_json ;\
	g++ -std=c++11 -o exec main.cpp httpsrequest.cpp -lcurl ;\
	chmod u+x crypto ;\
	ln -s $(pwd)/crypto /usr/local/bin/ ;\

