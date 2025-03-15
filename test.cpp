//
//  test.cpp
//  Merkel
//
//

#include "test.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

std::vector<std::string> tokenize(std::string csvLine, char separator ){
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

int main(){
//    std::vector<std::string> tokens;
//    std::string s="thing1,thing2,thing3";
//    tokens=tokenize(s, ',');
//    for(std::string& t:tokens){
//        std::cout << t<<std::endl;
//    }
    std::ifstream csvFile{"/Users/haoyuanwan/Desktop/Merkel/Merkel/20200317.csv"};
    if(csvFile.is_open()){
        std::vector<std::string> tokens;
        std::cout << "is open "<<std::endl;
        std::string line;
        while(std::getline(csvFile,line)){
            std::cout << "line read is : "<<line <<std::endl;
            tokens=tokenize(line, ',');
            if(tokens.size()!=5){
                std::cout << "bad line "<<std::endl;
                continue;;
            }
            try {
                double price = std::stod(tokens[3]);
                double amount = std::stod(tokens[4]);
                std::cout << price<<" : "<<amount<<std::endl;
            }
            /*const means that we do not want to edit the exception, just put the exception as is.
              & means we do not want the program to make a copy of the exception
              the reason for doing these thing is to stop the program from unnessisary things, and be explicit about want you want to do.
            */
            catch (const std::exception& e) {
                std::cout << "bad float"<<std::endl;
                continue;
            }
            
        }
        
        csvFile.close();
    }
    else{
        std::cout << "ERRO "<<std::endl;
    }
    return 0;
}
