#pragma once
#include <iostream>
#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet{
    public:
        Wallet();
    /** insert currency to the wallet*/
        void insertCurrency(std::string type, double amount);
    /** remove currency from the wallet, return if the currency is successfully removed*/
        bool removeCurrency(std::string type, double amount);
    /** check if the wallet contains this amount of the currency or More**/
        bool containsCurrency(std::string type, double amount);
    /** check if the wallet can fulfill an order**/
        bool canFulfillOrder(OrderBookEntry order);
    /** stirng representation of the wallet*/
        std::string toString();
    /** update the contents of the wallet
      * assume the order was made by the owner of the wallet*/
        void processSale(OrderBookEntry& sale);
    private:
    std::map<std::string, double> currencies;
    
        
};
