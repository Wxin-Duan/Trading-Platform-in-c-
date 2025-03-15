#ifndef CSVReader_h
#define CSVReader_h
#pragma once
#include "OrderBookEntry.h"
#include <vector>

class CSVReader{
    public:
    CSVReader();
    static std::vector<OrderBookEntry> readCSV(std::string csvFileName);
    static std::vector<std::string> tokenize(std::string csvLine, char separator);
    static OrderBookEntry stringsToOBE(std::string price,
                                       std::string amount,
                                       std::string timestamp,
                                       std::string product,
                                       OrderType orderType);
    
    private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> tokens);
    
};

#endif /* CSVReader_h */
