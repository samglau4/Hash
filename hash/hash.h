/*
 * hash.h
 *
 *  Created on: May 22, 2019
 *      Author: samla
 */
#ifndef HASH_H_
#define HASH_H_

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <bits/stdc++.h>


using namespace std;

    struct item {
        std::string BP;     //BYTE PAIR
        std::string ET;     //ENCODED TEXT
        item *next;
    };

    class hash {
        static const int tableSize = 10;
        item *HashTable [tableSize];     //STORE BP TO ET

    public:
        //PRIMARY FUNCTIONS
        hash();
        virtual ~hash();
        void AddItem(std::string BP, std::string ET);
        int Hash(std::string key);
        char randomChar();
        std::string Find_ENCODED_RETURN(std::string BP);
        std::string encoder(std::string text);

        bool FindBP(std::string BP);
        void addAll(std::string text);

        //AUXILARY PRINT FUNCTIONS
        std::string returnrandom();
        std::string randomWordGenerator();
        void printAllWord();
    };

#endif //INC_3_DEFENSE_HASH_H
