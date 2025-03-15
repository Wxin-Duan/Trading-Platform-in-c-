//Specificaiton in the header file, implimentation in the cpp file
#pragma once
#include <string>

enum OrderType
{
    bid,
    ask,
    bidsale,
    asksale,
    unknown
};
class OrderBookEntry // this is the name of the class
{
    
public:            // parts of the class that can be seen from outside
    OrderBookEntry(double price, double amount, std::string timestamp, std::string product, OrderType type,std::string username="dataset");
    static OrderType stringToOrderBookType(std::string s);
    double getPrice();

    double _amount;
    std::string _product;
    std::string _timestamp;
    OrderType _type;
    double _price; // this is a data member (AKA a variable inside a class)
    std::string _username;
    static bool compareByTimeStamp(OrderBookEntry& o1,OrderBookEntry& o2){
        return o1._timestamp<o2._timestamp;
    }
    static bool compareByPriceAse(OrderBookEntry& o1,OrderBookEntry& o2){
        return o1._price<o2._price;
    }
    static bool compareByPriceDec(OrderBookEntry& o1,OrderBookEntry& o2){
        return o1._price>o2._price;
    }
}; // note the semi-colon
