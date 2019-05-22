/*
 * hash.cpp
 *
 *  Created on: May 22, 2019
 *      Author: samla
 */
#include <iostream>
#include "hash.h"
#include <ctime>
#include <time.h>
#include <cstdlib>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;
std::string arr[100][2];

//DESTRUCTOR FUNCTION
hash::~hash() {
    item* temp;
    item* temp_next;
    for (int i = 0; i < tableSize; i++) {
        temp = HashTable[i];
        while (NULL != temp) {
            temp_next = temp->next;
            delete temp;
            temp = temp_next;
        }
        HashTable[i] = NULL;
    }
}

//CONSTRUCTOR
/*SETS UP THE EMPTY HASHTABLE WITH "empty"*/
hash::hash() {
    for (int i = 0; i < tableSize; i++) {
        HashTable[i] = new item;
        HashTable[i]->BP = "empty";
        HashTable[i]->ET = "empty";
        HashTable[i]->next = NULL;
    }
}


//CREATE RANDOM CHARACTER
//UPDATED 050119
char hash::randomChar() {
    int min = 33;
    int max = 126;
    int random = min + rand() % (( max + 1 ) - min);
    int random2 = min + rand() % (( max + 1 ) - min);
    char *randomString = new char[3];
    randomString[0] = random;
    randomString[1] = random2;
    randomString[2] = '\0';
    return *randomString;
}

//ADD ALL ITEMS OF THE STRING TO HASH TABLE.
//PARAMETER text IS THE STRING THAT NEEDS TO BE STORED TO THE HASH TABLE
void hash::addAll(std::string text) {
    std::string strPair = "";
    std::string rr = "";
    int x = 0;
    for (unsigned i = 0; i < text.length(); i = i + 2) {
        strPair = text.substr(i, 2);
        char r;
        bool FindBPT = FindBP(strPair);
        if (!FindBPT) {
            x = randomChar();
            r = (char) x;
            std::string rr(&r, 2);
            string zacc = returnrandom();
            AddItem(strPair, zacc);
        }
    }
}

//ADDS ITEM TO FIRST HASHTABLE
//PARAMETER BP & ET ARE BYTE PAIR AND ENCODED TEXT THAT IS ADDED TO THE TABLE
//BYTE PAIR(BP) IS THE STRING THAT IS HASHED.
void hash::AddItem(std::string BP, std::string ET) {
    int index = Hash(BP);
    if (HashTable[index]->BP == "empty") {
        HashTable[index]->BP = BP;
        HashTable[index]->ET = ET;
    }

    else {
        item* Ptr = HashTable[index];
        item* newItem = new item;           //INITIALIZE A NEW ITEM
        newItem->BP = BP;
        newItem->ET = ET;
        newItem->next = NULL;
        while (Ptr->next != NULL) {       //HAPPEN AT END OF LIST
            Ptr = Ptr->next;
        }
        Ptr->next = newItem; //LINKS the last item in the list to the newly created item that n is pointing to
    }
}

//CREATES HASH FOR THE KEY
//PARAMETER key IS THE PAIR TO BE HASHED.
int hash::Hash(std::string key) {
    //Lets say key has hash value. If value is 453 and size is 100
    //we do 453 % 100 = 53 remainder. This is index value that we are going to
    //return to tell us where in the table to place the information associated with this key
    int hash = 0;
    int index;

    for (unsigned i = 0; i < key.length(); i++) {
        hash = hash + (int) key[i]; //WITHOUT THIS LINE, all are stored in index 0.
    }
    index = hash % tableSize;       //TO FIT INSIDE THE HASH TABLE
    return index;
}


//USED FOR SENDING BYTE PAIR and RETURNING ENCODED TEXT
//PARAMETER BP is the byte pair used to find the decoded value
//RETURNS the encoded text ET corresponding to BP.
std::string hash::Find_ENCODED_RETURN(std::string BP) {
    int index = Hash(BP);
    bool foundBP = false;
    std::string ET = "";

    item *Ptr = HashTable[index];
    while (Ptr != NULL) {       //POINTING TO SOME ITEM
        if (Ptr->BP == BP) {
            foundBP = true;
            ET = Ptr->ET;
        }
        Ptr = Ptr->next;
    }
    if (foundBP) {
        return ET;
    }
    return 0;
}


//MAIN ENCODING
//PARAMETER text IS THE STRING TO BE ENCODED.
//RETURNS ENCODED TEXT returnENCSTR.
std::string hash::encoder(std::string text) {
    std::string returnENCSTR = "";
    std::string strPair2 = "";

    for (unsigned i = 0; i < text.length(); i = i + 2) {
        strPair2 = text.substr(i, 2);
        returnENCSTR = returnENCSTR + Find_ENCODED_RETURN(strPair2);
    }

    return returnENCSTR;
}

bool hash::FindBP(std::string BP) {
    int index = Hash(BP);
    bool foundBP = false;
    std::string ET = "";

    item *Ptr = HashTable[index];
    while (Ptr != NULL) {       //POINTING TO SOME ITEM
        if (Ptr->BP == BP) {
            foundBP = true;
            ET = Ptr->ET;
        }
        Ptr = Ptr->next;
    }
    if (foundBP) {
        return true;
    } else {
        return false;
    }
}

std::string hash::returnrandom(){
            int x1 = randomChar();
            int x2 = randomChar();
            char r1 = (char) x1;
            char r2 = (char) x2;
            std::string rr1(&r1, 1);
            std::string rr2(&r2, 1);
            std::string rr = rr1 + rr2;
        return rr;
}

int main() {
    hash Hashy;

    string line_;
    ifstream file_("mytext.txt");
    string PASSWORD;
    int count = 0;
    if (file_.is_open()) {              //check if the file is open.
        while ((file_ >> PASSWORD)) {   //reads file line by line, storing each variable values.
            arr[count][0] = PASSWORD;
            count++;
        }
        file_.close();
    }
    else    cout << "File is not open. " << endl;

    std::cout << "PASSWORD" << "\t" << "ENCODED-PASSWORD" << endl;
    for (int i = 0; i < 5; i++){
        Hashy.addAll(arr[i][0]);
        //Hashy.addAll(arr[i][0]);
        arr[i][1] = Hashy.encoder(arr[i][0]);
        cout << arr[i][0] << "\t" << arr[i][1] <<endl;
    }
    cout << "--------------------------------------------" << endl;

    std::string retreivePassword;
    int countreturn = 0;
    cout << "Enter a password to restore: ";
    cin >> retreivePassword;
    for (int i = 0; i < 5; i++){
        if (retreivePassword == arr[i][1])  {   cout << arr[i][0] << endl;  }
        else countreturn++;
    }
    if (countreturn == 0)   cout << "Password Not Found" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Enter a password to restore: ";
    cin >> retreivePassword;
    countreturn = 0;
    for (int i = 0; i < 5; i++){
        if (retreivePassword == arr[i][1])  {   cout << arr[i][0] << endl;  }
        else countreturn++;
    }
    if (countreturn == 5)   cout << "Password Not Found" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Enter a password to restore: ";
    cin >> retreivePassword;
    countreturn = 0;
    for (int i = 0; i < 5; i++){
        if (retreivePassword == arr[i][1])  {   cout << arr[i][0] << endl;  }
        else countreturn++;
    }
    if (countreturn == 5)   cout << "Password Not Found" << endl;
    cout << "--------------------------------------------" << endl;
    return 0;
}



