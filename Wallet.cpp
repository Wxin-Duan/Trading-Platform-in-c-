#include "Wallet.h"
#include "CSVReader.h"
Wallet::Wallet(){
    
}
void Wallet::insertCurrency(std::string type, double amount){
    double balance;
    if(amount<0){
        throw std::exception{};
    }
    if(currencies.count(type)==0)//not there yet
    {
        balance=0;
    }
    else{
        balance=currencies[type];
    }
    balance+=amount;
    currencies[type]=balance;
}
bool Wallet::removeCurrency(std::string type, double amount){
    if(amount>=0&&containsCurrency(type, amount)){ //we have enough currency
        currencies[type]-=amount;
        return true;
    }
    return false;
}
bool Wallet::containsCurrency(std::string type, double amount){
    if(currencies[type]==0){
        return false;
    }
    return currencies[type]>=amount;
}
std::string Wallet::toString(){
    std::string s;
    for(std::pair<std::string,double> pair:currencies){
        std::string currency=pair.first;
        double amount=pair.second;
        s+=currency+" : "+std::to_string(amount)+"\n";
    }
    return s;
}
bool Wallet::canFulfillOrder(OrderBookEntry order){
    std::vector<std::string> currs=CSVReader::tokenize(order._product, '/');
    //ask
    if(order._type==OrderType::ask){
        double amount=order._amount;
        std::string currency=currs[0];
        std::cout<<"Wallet::canFulfillOrder ask "<<currency <<" : "<<amount<<std::endl;
        return containsCurrency(currency, amount);
    }
    //bid
    if(order._type==OrderType::bid){
        double amount=order._amount*order._price;
        std::string currency=currs[1];
        std::cout<<"Wallet::canFulfillOrder bid "<<currency <<" : "<<amount<<std::endl;
        return containsCurrency(currency, amount);
    }
    return false;
}
void Wallet::processSale(OrderBookEntry& sale){
    std::vector<std::string> currs=CSVReader::tokenize(sale._product, '/');
    //ask
    if(sale._type==OrderType::asksale){
        double outgoingAmount=sale._amount;
        std::string outgoingCurrency=currs[0];
        double incomingAmount=sale._amount*sale._price;
        std::string incomingCurrency=currs[1];
        std::cout<<"Wallet::canFulfillOrder ask "<<outgoingCurrency <<" : "<<outgoingAmount<<std::endl;
        currencies[incomingCurrency]+=incomingAmount;
        currencies[outgoingCurrency]-=outgoingAmount;
    }
    //bid
    if(sale._type==OrderType::bidsale){
        double incomingAmount=sale._amount;
        std::string incomingCurrency=currs[0];
        double outgoingAmount=sale._amount*sale._price;
        std::string outgoingCurrency=currs[1];
        std::cout<<"Wallet::canFulfillOrder ask "<<outgoingCurrency <<" : "<<outgoingAmount<<std::endl;
        currencies[incomingCurrency]+=incomingAmount;
        currencies[outgoingCurrency]-=outgoingAmount;
    }
}
