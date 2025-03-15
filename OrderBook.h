#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
public:
    /**constructor, read a csv file*/
    OrderBook(std::string filename);
    /**return vector of all known products in the dataset*/
    std::vector<std::string> getKnownProducts();
    /**return vector of Orders according to the inputing filters*/
    std::vector<OrderBookEntry> getOrders(OrderType type, std::string prodcut,std::string timestamp);
    /**return the earliest time in the orderbook*/
    std::string getEarliestTime();
    /**return the next time after the sent time in the orderbook
     *if next time stamp is never found, wrap the timestamp to the very beginning*/
    std::string getNextTime(std::string timestamp);
    static double getHighPrice(std::vector<OrderBookEntry>& orders);
    static double getLowPrice(std::vector<OrderBookEntry>& orders);
    void insertOrder(OrderBookEntry& order);
    std::vector<OrderBookEntry> matchAskToBid(std::string prodcut, std::string timeStamp);
    
    
private:
    std::vector<OrderBookEntry> orders;
};
