// compile command 
// g++ --std=c++11 main.cpp OrderBookEntry.cpp MerkelMain.cpp

#include <iostream>
#include <map>
#include <vector>
#include "OrderBookEntry.h"
#include "MerkelMain.h"
#include "CSVReader.h"
#include "Wallet.h"
int main()
{
    MerkelMain app{};
    app.init();
//    Wallet wallet;
//    wallet.insertCurrency("BTC", 10);
//    std::cout<<"wallet contains BTC: "<<wallet.containsCurrency("BTC", 10)<<std::endl;
//    std::cout<<wallet.toString()<<std::endl;
//    std::cout<<"wallet removes BTC: "<<wallet.removeCurrency("BTC", -1)<<std::endl;
//    std::cout<<wallet.toString()<<std::endl;
    return 0;
}
