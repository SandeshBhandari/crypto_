# crypto_

This is a simple C++ client to get the cryptocurrencies Ask, Bid and Last values from Bittrex Server.

There is a makefile provided to install it on a Mac. The program depends on nlohmann/json which is installed through the makefile.

Right now, it is just setup for a Mac as it is using brew to install the json library. This can be modified to package installer available in any linux system and the program should work once installed.


Common Examples of usage:
Once installed, to display the cryptocurrencies Ask, Bid and Last values:

crypto -r currencysymbol

so For Bitcoin, the currency symbol will be btc.

crypto -r btc

This should display the values for Bitcoin

There is also a feature to add certain cryptocurrencies so you dont have to try separate command each time to see the values you want to keep track of.

To add:

crypto -a btc,eth,ltc

The currency symbols should be comma separated like above. This creates a text folder with the values. So, the next time you want to see the values for these symbols just use the command:

crypto -l



