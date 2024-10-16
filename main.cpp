#include <iostream>
#include <map>
#include <vector>

void printMenu()
{
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6 : Continue" << std::endl;
    std::cout << "7 : Continue" << std::endl;
    std::cout << "type in your response" << std::endl;
}

int getuserResponse()
{
    int userResponse;
    std::cin >> userResponse;
    std::cout << "... you typed " << userResponse << std::endl;
    return userResponse;
}

void printHelp()
{
    std::cout << "Help - choose options from the menu" << std::endl;
    std::cout << "and follow the on screen instructions." << std::endl;
}

void printExStat()
{
    std::cout << "exchange stats" << std::endl;
    std::cout << "Your exchange stats is as follows" << std::endl;
}

int enterAsk(){
    int ask;
    std::cout << "enter your ask" << std::endl;
    std::cin >> ask;
    std::cout << "your ask is " << ask << std::endl
              << "press 1 to continue" << std::endl;
    int yes;
    std::cin >> yes;
    if (yes == 1)
    {
        std::cout << "your ask is processed" << std::endl;
        return ask;
    }
    else
    {
        std::cout << "your ask is discarded " << std::endl;
        return ask = 0;
    }
}

int bidFor()
{
    int bid;
    std::cout << "Place bid by entering a number below: " << std::endl;
    std::cin >> bid;
    std::cout << "Your bid is " << bid << std::endl;
    return bid;
}

void printWallet()
{
    int wallet = 100;
    std::cout << "Status of your wallet is as below: " << std::endl;
    std::cout << wallet;
}

void userCon()
{
    std::cout << "Continue " << std::endl;
}

int invalidIn()
{
    int userResponse;
    std::cout << "Invalid! " << std::endl;
    std::cin >> userResponse;
    return userResponse;
}

int main()
{
    enum OrderType
    {
        bid,
        ask
    };
    
    std::vector<std::string> timeStamp;
    std::vector<std::string> products;
    std::vector<OrderType> types;
    std::vector<double> amount;
    std::vector<double> prices;

    bool userContinue = true;
    int userResponse;
    // map from ints to function pointers
    std::map<int, void (*)()> menu;
    // connect 1 to the printHelp function
    menu[1] = printHelp;
    // call option 1
    
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
            menu[1]();
            break;
        case 2:
            printExStat();
            break;
        case 3:
        {
            int ask;
            ask = enterAsk();
            break;
        }
        case 4:
        {
            int bid;
            bid = bidFor();
            break;
        }
        case 5:
            printWallet();
            break;
        case 6:
            userCon();
            break;
        case 0:
            userResponse=invalidIn();
            break;
        }
    }
    return 0;
}