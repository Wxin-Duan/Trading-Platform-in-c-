#include "OrderBookEntry.h"

OrderBookEntry::OrderBookEntry(double price, double amount, std::string timestamp, std::string product, OrderType type,std::string username)
: _price(price), _amount(amount),  _timestamp(timestamp),_product(product), _type(type),_username(username)
{
}
double OrderBookEntry::getPrice()
{
    return _price;
}
OrderType OrderBookEntry::stringToOrderBookType(std::string s){
    
    if(s=="ask"){
        return OrderType::ask;
    }
    if(s=="bid"){
        return OrderType::bid;
    }
    if(s=="bidsale"){
        return OrderType::bidsale;
    }
    if(s=="asksale"){
        return OrderType::asksale;
    }
    return OrderType::unknown;
}
