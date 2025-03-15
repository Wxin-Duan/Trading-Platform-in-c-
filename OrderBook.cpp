#include "OrderBook.h"
#include "CSVReader.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>

OrderBook::OrderBook(std::string filename){
    orders=CSVReader::readCSV(filename);
}

std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string,bool> prodMap;
    for(OrderBookEntry& e:orders){
        prodMap[e._product]=true;
    }
    /**auto means the type of e is auto converted, even though here the type is string, but I will still let the compiler to deal with it*/
    for(auto const& e:prodMap){
        products.push_back(e.first);
    }
    return products;
}

std::vector<OrderBookEntry> OrderBook::getOrders(OrderType type,
                                                 std::string product,
                                                 std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for(OrderBookEntry& e:orders){
        if(e._type==type &&
           e._product==product &&
           e._timestamp==timestamp){
            orders_sub.push_back(e);
        }
    }
    return orders_sub;
}
std::string OrderBook::getEarliestTime(){
    //assume the order is sorted according to timestamp
    return orders[0]._timestamp;
}
std::string OrderBook::getNextTime(std::string timestamp){
    std::string next_timestamp="";
    for(OrderBookEntry& e : orders){
        if(e._timestamp>timestamp){
            next_timestamp=e._timestamp;
            
            return next_timestamp;
        }
    }
    if(next_timestamp==""){
        next_timestamp=orders[0]._timestamp;
    }
    return next_timestamp;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders){
    double max=orders[0]._price;
    for (OrderBookEntry& e: orders){
        if(e._price>max) max=e._price;
        
    }
    return max;
}
double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders){
    double min=orders[0]._price;
    for (OrderBookEntry& e: orders){
        if(e._price<min) min=e._price;
        
    }
    return min;
}
void OrderBook::insertOrder(OrderBookEntry& order){
    orders.push_back(order);
    std::sort(orders.begin(),orders.end(),OrderBookEntry::compareByTimeStamp);
}
std::vector<OrderBookEntry> OrderBook::matchAskToBid(std::string product, std::string timestamp){
    std::vector<OrderBookEntry> asks=getOrders(OrderType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids=getOrders(OrderType::bid, product, timestamp);
    std::vector<OrderBookEntry> sales;
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAse);
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDec);
    
    for(OrderBookEntry& ask:asks){
        for(OrderBookEntry& bid:bids){
            if(bid._price>=ask._price){
                OrderBookEntry sale{
                    ask._price, 0, timestamp, product, OrderType::asksale
                };
                if(bid._username=="simuser"){
                    sale._username=bid._username;
                    sale._type=OrderType::bidsale;
                }
                if(ask._username=="simuser"){
                    sale._username=ask._username;
                    sale._type=OrderType::asksale;
                }
                
                if(bid._amount==ask._amount){
                    sale._amount=bid._amount;
                    sales.push_back(sale);
                    bid._amount=0;
                    break;
                }
                if(bid._amount>ask._amount){
                    sale._amount=ask._amount;
                    sales.push_back(sale);
                    bid._amount=bid._amount-ask._amount;
                    break;
                }
                if(bid._amount<ask._amount&&bid._amount>0){
                    sale._amount=bid._amount;
                    sales.push_back(sale);
                    bid._amount=0;
                    continue;
                }
            }
            
        }
    }
    return sales;
}
