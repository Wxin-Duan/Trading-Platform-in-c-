#include "CSVReader.h"
#include "OrderBookEntry.h"
#include <vector>
#include <iostream>
#include <fstream>
CSVReader::CSVReader(){
    
}
std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFileName){
    std::vector<OrderBookEntry> entries;
    std::ifstream csvFile{csvFileName};
    
    if(csvFile.is_open()){
        std::string line;
        while(std::getline(csvFile,line)){
            try{
                OrderBookEntry obe=stringsToOBE(tokenize(line, ','));
                entries.push_back(obe);
            }catch(const std::exception& e){
                std::cout<<"Bad Data "<<std::endl;
            }
            
        }//end of while
    }
    else{
        std::cout<<"file is not open  " <<std::endl;
    }
    std::cout<<"CSVReader::readCSV read "<<entries.size()<<" entries"<<std::endl;
    return entries;
}
std::vector<std::string> CSVReader::tokenize(std::string csvLine, char separator){
    std::vector<std::string> tokens;
    std::string token;
    signed int start,end;
    start=csvLine.find_first_not_of(separator,0);
    do {
        end=csvLine.find_first_of(separator,start);
        if(start==csvLine.length()||start==end) break;
        if(end>=0) token=csvLine.substr(start,end-start);
        else token =csvLine.substr(start,csvLine.length()-start);
        tokens.push_back(token);
        start=end+1;
        
        
    } while (end != std::string::npos);
    return tokens;

}
OrderBookEntry CSVReader::stringsToOBE(std::string priceStr,
                                   std::string amountStr,
                                   std::string timestamp,
                                   std::string product,
                                   OrderType orderType){
    double price;
    double amount;
    try {
        price = std::stod(priceStr);
        amount = std::stod(amountStr);
    }
    /*const means that we do not want to edit the exception, just put the exception as is.
      & means we do not want the program to make a copy of the exception
      the reason for doing these thing is to stop the program from unnessisary things, and be explicit about want you want to do.
    */
    catch (const std::exception& e) {
        std::cout << "CSVReader::stringsToOBE -> bad float at 'priceStr' "<<priceStr<<std::endl;
        std::cout << "CSVReader::stringsToOBE -> bad float at 'amountStr' "<<amountStr<<std::endl;
        throw;
    }
    OrderBookEntry obe{price, amount, timestamp, product, orderType};
    return obe;
}
OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens){
    double price, amount;
    if(tokens.size()!=5){
        std::cout << "bad line "<<std::endl;
        throw std::exception{};
    }
    try {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    /*const means that we do not want to edit the exception, just put the exception as is.
      & means we do not want the program to make a copy of the exception
      the reason for doing these thing is to stop the program from unnessisary things, and be explicit about want you want to do.
    */
    catch (const std::exception& e) {
        std::cout << "bad float"<<std::endl;
        throw;
    }
    OrderBookEntry obe{price, amount, tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2])};
    return obe;
}

