#include <iostream>
#include "MerkelMain.h"
#include "OrderBookEntry.h"
#include <vector>
#include "CSVReader.h"
#include "OrderBook.h"
#include "Wallet.h"

MerkelMain::MerkelMain()
{

}
void MerkelMain::init()
{
    currentTime=orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10);
    customerSelect();
    
}

void MerkelMain::printMenu()
{
    std::cout << "current time is : " <<currentTime<< std::endl;
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6 : Go to next time frame" << std::endl;
    std::cout << "7 : Continue" << std::endl;
    std::cout << "type in your response" << std::endl;
}

int MerkelMain::getuserResponse()
{
    int userResponse=0;
    std::string input;
    std::getline(std::cin,input);
    try{
        userResponse= std::stoi(input);
        std::cout << "... you typed " << userResponse << std::endl;
        
    }catch(const std::exception& e){
        std::cout<<"MerkelMain::getuserResponse() bad input: "<<input<<std::endl;
    }
    return userResponse;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void MerkelMain::printExStat()
{
    for (std::string const& p:orderBook.getKnownProducts() ){
        std::cout<<"Prodcut : "<<p<<std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderType::ask, p, currentTime);
        std::cout<<"ask seen: "<<entries.size()<<std::endl;
        std::cout<<"max ask: "<<OrderBook::getHighPrice(entries)<<std::endl;
        std::cout<<"min ask: "<<OrderBook::getLowPrice(entries)<<std::endl;
    }
}

void MerkelMain::enterAsk()
{
    std::cout << "enter your ask" << std::endl;
   // std::cin >> ask;
    std::string input;
    //getline() doesn't work with previous std::cin when we prompt for user option. So need some code to ask the complier to ignor the previous std::cin
   // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::getline(std::cin,input);
    std::vector<std::string> tokens=CSVReader::tokenize(input,',');
    if(tokens.size()!=3){
        std::cout<<"MerkelMain::enterAsk bad input, token size<3: "<<input;
    }
    else{
        try{
            OrderBookEntry obe=CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderType::ask);
            obe._username="simuser";
            if(wallet.canFulfillOrder(obe)){
                std::cout<<"Wallet looks good. "<<std::endl;
                orderBook.insertOrder(obe);
            }
            else{
                std::cout<<"Wallet funds insufficient. "<<std::endl;
            }
        }catch(const std::exception& e){
            std::cout<<"MerkelMain::enterAsk bad input "<<input<<std::endl;
        }
        
    }
    
}

void MerkelMain::bidFor()
{
    std::cout << "enter your bid" << std::endl;
   // std::cin >> ask;
    std::string input;
    //getline() doesn't work with previous std::cin when we prompt for user option. So need some code to ask the complier to ignor the previous std::cin
   // std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::getline(std::cin,input);
    std::vector<std::string> tokens=CSVReader::tokenize(input,',');
    if(tokens.size()!=3){
        std::cout<<"MerkelMain::enterBid bad input, token size<3: "<<input;
    }
    else{
        try{
            OrderBookEntry obe=CSVReader::stringsToOBE(tokens[1], tokens[2], currentTime, tokens[0], OrderType::bid);
            obe._username="simuser"; 
            if(wallet.canFulfillOrder(obe)){
                std::cout<<"Wallet looks good. "<<std::endl;
                orderBook.insertOrder(obe);
            }
            else{
                std::cout<<"Wallet funds insufficient. "<<std::endl;
            }
        }catch(const std::exception& e){
            std::cout<<"MerkelMain::enterBid bad input "<<input<<std::endl;
        }
        
    }
}

void MerkelMain::printWallet()
{
    std::cout << "Status of your wallet is as below: " << std::endl;
    std::cout << wallet.toString();
}
std::string MerkelMain::gotoNextTimeFrame(){
    std::cout << "Going to the next time frame"<<std::endl;
    std::vector<OrderBookEntry> sales=orderBook.matchAskToBid("ETH/BTC", currentTime);
    std::cout<<"Sales size = "<<sales.size()<<std::endl;
    for(OrderBookEntry& sale:sales){
        std::cout<<"sale price: "<< sale._price<<" . amount: "<<sale._amount<<std::endl;
        if(sale._username=="simuser"){
            //update the wallet
        }
    }
    currentTime=orderBook.getNextTime(currentTime);
    return currentTime;
}
void MerkelMain::userCon()
{
    std::cout << "Continue " << std::endl;
}

//int MerkelMain::invalidIn()
//{
//    int userResponse;
//    std::cout << "Invalid! " << std::endl;
//    std::cin >> userResponse;
//    return userResponse;
//}
void MerkelMain::customerSelect()
{
    bool userContinue = true;
    int userResponse;
    while (userContinue)
    {
        printMenu();
        userResponse = getuserResponse();

        switch (userResponse)
        {
        case 7:
        {
            userContinue = false;
            break;
        }
        case 1:
            printHelp();
            break;
        case 2:
            printExStat();
            break;
        case 3:
        {
            enterAsk();
            break;
        }
        case 4:
        {
            bidFor();
            break;
        }
        case 5:
            printWallet();
            break;
        case 6:
            currentTime=gotoNextTimeFrame();
            break;
        }
    }
}
void MerkelMain::printMarketStat()
{
    std::cout << "Order book contains: " << orders.size() << " entries. " << std::endl;
}
