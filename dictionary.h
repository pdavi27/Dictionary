#ifndef DICTIONARY_DICTIONARY_H
#define DICTIONARY_DICTIONARY_H

#include <cstring>
#include "fraction.h"

using namespace std;

class Dictionary {

    int nPairs = 0;
    string keyList[100];
    Fraction valueList[100];

public:

    Dictionary();
    ~Dictionary();

    void clear();
    bool isEmpty();
    int size();

    void insert(string k, Fraction v);
    void remove(string k);
    Fraction search(string k);
    void update(string k, Fraction v);

};

#endif //DICTIONARY_DICTIONARY_H
