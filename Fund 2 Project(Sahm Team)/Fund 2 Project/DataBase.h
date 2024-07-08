#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class DataBase {
protected:
    ifstream Diamond_in;
    ifstream Gold_in;
    ifstream Silver_in;
    ofstream Diamond_out;
    ofstream Gold_out;
    ofstream Silver_out;

public:
    ~DataBase();
    void LinkDataBase(string DIAMOND, string GOLD, string SILVER);
};

#endif