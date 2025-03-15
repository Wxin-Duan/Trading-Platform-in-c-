#pragma once
#include <string>
#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain
{
    public:
        int userResponse;
        MerkelMain();
        void init();
    private:
        void printMenu();
        int getuserResponse();
        void printHelp();
        void printExStat();
        void enterAsk();
        void bidFor();
        void printWallet();
        void userCon();
        void customerSelect();
        void printMarketStat();
        std::string gotoNextTimeFrame();
        OrderBook orderBook{"/Users/duanduan/Desktop/Merkel/Merkel/test.csv"};
        std::vector<OrderBookEntry> orders;
        std::string currentTime;
        Wallet wallet;
};
