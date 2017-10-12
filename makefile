build: main.cpp httpsrequest.cpp
	brew tap nlohmann/json ;\
	brew install nlohmann_json ;\
	mkdir "$$(HOME)/crypto_" ;\
	g++ -std=c++11 -o exec main.cpp httpsrequest.cpp -lcurl ;\
	cp "$$(pwd)/*" "$$(HOME)/crypto_/" ;\
	chmod u+x "$$(HOME)/crypto_/crypto" ;\
	ln -s "$$(HOME)/crypto_/crypto" /usr/local/bin/ ;\
	ln -s "$$(HOME)/crypto_/exec" /usr/local/bin/ ;\

