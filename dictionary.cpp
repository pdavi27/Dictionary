#include "dictionary.h"

Dictionary::Dictionary() {} // Constructor
Dictionary::~Dictionary() {} // Deconstructor

// Clears the dictionary
void Dictionary::clear() {
    nPairs = 0;
}

// Determines if the dictionary is empty
bool Dictionary::isEmpty() {
    if (nPairs == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Determines the size of the dictionary
int Dictionary::size() {
    return nPairs;
}

// Inserts pairs into dictionary
void Dictionary::insert(string k, Fraction v) {
    int i = 0;
   while (i<nPairs and keyList[i] != k)
   {
       i++;
   }
   if (i<nPairs)
   {
       throw domain_error(k);
   }
   if (nPairs >= 100)
   {
       throw overflow_error(k);
   }
   else
   {
       keyList[i] = k;
       valueList[i] = v;
       nPairs = nPairs + 1;
   }

}

// Removes pairs from dictionary
void Dictionary::remove(string k) {
    int i = 0;
    while (i<nPairs and keyList[i] != k)
    {
        i++;
    }
    if (i<nPairs)
    {
        nPairs--;
        keyList[i]=keyList[nPairs];
        valueList[i]=valueList[nPairs];
    }
    else
    {
        throw domain_error(k);
    }
}

// Searches for key in dictionary
Fraction Dictionary::search(string k) {
    int i = 0;
    while (i<nPairs and keyList[i] != k)
    {
        i++;
    }
    if (i<nPairs)
    {
        return valueList[i];
    }
    else
    {
        throw domain_error(k);
    }
}

// Force update in dictionary
void Dictionary::update(string k, Fraction v) {
    int i = 0;
    while (i<nPairs and keyList[i] != k)
    {
        i++;
    }
    if (i<nPairs)
    {
        valueList[i] = v;
    }
    else
    {
        throw domain_error(k);
    }
}
