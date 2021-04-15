#include <iostream>
#include <random>
#include "fraction.h"

// change this to whatever you called your interface file for the dictionary
#include "dictionary.h"

using namespace std;

// this is a "macro"... it works like a function, but it's done by copy-and-paste
// to use it, output OPF(f) where f is some boolean value. if f is true, OPF()
// will be the string "pass" and if f is false, it will be "fail"
#define OPF(var) ((var)?"pass":"fail")

int main() {
    bool
        emptyOkay,
        sizeOkay,
        okay;

    int DICTIONARY_MAX_SIZE = 100;

    // these are for the new way C++ does random numbers
    // in the end, I use the uniform_int_distributions to generate a random
    // number in the given ranges
    auto
        rd = new random_device;
    auto
        mt = new mt19937((*rd)());
    uniform_int_distribution<>
        letters(0,25),
        numbers(1,100),
        positions(0,DICTIONARY_MAX_SIZE-1);

    Dictionary
        dict;                               // the dictionary

    // these three arrays are parallel arrays
    string
        keyList[DICTIONARY_MAX_SIZE];       // the keys I'm adding
    Fraction
        valueList[DICTIONARY_MAX_SIZE];     // the values I'm adding
    bool
        flags[DICTIONARY_MAX_SIZE];         // flags for tracking which keys
                                            // I am working with

    // step 0: populate keys and values

    // loop over all positions in the parallel arrays
    for (int32_t i=0;i<DICTIONARY_MAX_SIZE;i++) {
        // generate a random 8-letter string for the key
        for (int32_t j=0;j<8;j++)
            keyList[i] += "abcdefghijklmnopqrstuvwxyz"[letters(*mt)];
        // generate a random fraction for the value
        valueList[i] = Fraction(numbers(*mt),numbers(*mt));
    }

    // start by checking that the dictionary reports that it's empty
    emptyOkay = dict.isEmpty();
    sizeOkay = dict.size() == 0;

    // step 1: add first 50 keys to the dictionary

    okay = true;
    for (int32_t i=0;i<50;i++) {
        // try to add a key, process any exceptions that are thrown back
        try {
            dict.insert(keyList[i], valueList[i]);
        } catch (domain_error &e) {
            cout << "Error: " << e.what() << endl;
            cout << "i=" << i << '\t' << keyList[i] << '\t' << valueList[i] << endl;
            okay = false;
        } catch (overflow_error &e) {
            cout << "Error: " << e.what() << endl;
            cout << "i=" << i << '\t' << keyList[i] << '\t' << valueList[i] << endl;
            okay = false;
        } catch (...) {
            cout << "Unknown error" << endl;
            okay = false;
        }

        // make sure the dictionary reports that it's not empty and has the
        // correct size
        if (dict.size() != i + 1)
            sizeOkay = false;
        emptyOkay = emptyOkay && !dict.isEmpty();
    }

    // output results so far
    cout << "            insert: " << OPF(okay) << endl;
    cout << "           isEmpty: " << OPF(emptyOkay) << endl;
    cout << "              size: " << OPF(sizeOkay) << endl;

    // step 2a: search for the 50 keys, verify values

    okay = true;
    // search for the keys in reverse order
    for (int32_t i=49;i>=0;i--) {
        // try to search, process exceptions
        try {
            Fraction f = dict.search(keyList[i]);

            // make sure the returned value is correct
            if (f != valueList[i]) {
                cout << "Value mismatch" << endl;
                cout << "i=" << i << '\t' << keyList[i] << '\t' << f << endl;
                okay = false;
            }
        } catch (domain_error &e) {
            cout << "Error: " << e.what() << endl;
            cout << "i=" << i << '\t' << keyList[i] << '\t' << valueList[i] << endl;
            okay = false;
        } catch (...) {
            cout << "Unknown error" << endl;
            okay = false;
        }
    }

    // step 2b: search for the keys not in table

    for (int32_t i=50;i<DICTIONARY_MAX_SIZE;i++) {
        // these keys should not be in the dictionary, so they should throw
        // exceptions. that's okay.
        try {
            dict.search(keyList[i]);

            // if the search didn't throw an exception, we'll run this line.
            // it should throw a domain_error, so we shouldn't get here.
            okay = false;
        } catch (domain_error &e) {
            // this is expected, so nothing done here
        } catch (...) {
            cout << "Unknown error" << endl;
            okay = false;
        }
    }

    cout << "            search: " << OPF(okay) << endl;

    /*

    // step 2c: verify key list

    // set all flags to false
    for (bool & flag : flags)
        flag = false;

    string
        key;

    // get the first key in the dictionary and make sure that worked
    if (!dict.getFirstKey(key))
        okay = false;

    do {
        // look for that key in our list
        for (int32_t i=0;i<DICTIONARY_MAX_SIZE;i++)
            if (keyList[i] == key) {    // if key is found,
                flags[i] = true;        // set its flag and stop searching
                break;
            }
    } while (dict.getNextKey(key)); // move on to the next key

    // now, the first 50 flags should be set and the rest should be cleared.
    // verify this.
    for (int32_t i=0;i<50;i++)
        if (!flags[i])
            okay = false;

    for (int32_t i=50;i<DICTIONARY_MAX_SIZE;i++)
        if (flags[i])
            okay = false;

    cout << "  getFirst/getNext: " << OPF(okay) << endl;

     */

    // step 3a: add remaining keys to dictionary

    // this is the same as step 1, except we're adding all of the remaining keys
    okay = true;
    for (int32_t i=50;i<DICTIONARY_MAX_SIZE;i++) {
        try {
            dict.insert(keyList[i], valueList[i]);
        } catch (domain_error &e) {
            cout << "Error: " << e.what() << endl;
            cout << "i=" << i << '\t' << keyList[i] << '\t' << valueList[i] << endl;
            okay = false;
        } catch (overflow_error &e) {
            cout << "Error: " << e.what() << endl;
            cout << "i=" << i << '\t' << keyList[i] << '\t' << valueList[i] << endl;
            okay = false;
        } catch (...) {
            cout << "Unknown error" << endl;
            okay = false;
        }
    }

    cout << "        insert all: " << OPF(okay) << endl;

    // the dictionary should now be full. this tests adding one more key
    okay = true;
    try {
        dict.insert("hello",Fraction(0,1));

        cout << "Error: overflow not caught" << endl;

        okay = false;
    } catch (overflow_error &e) {
        // expected behavior here
    } catch (...) {
        cout << "Unknown error" << endl;
        okay = false;
    }

    cout << "          overflow: " << OPF(okay) << endl;

    // step 3b: search for all keys, verify values

    // same as step 2a, except now we're looking at all of the pairs
    okay = true;

    for (int32_t i=DICTIONARY_MAX_SIZE-1;i>=0;i--) {
        try {
            Fraction f = dict.search(keyList[i]);

            if (f != valueList[i]) {
                cout << "Value mismatch" << endl;
                cout << "i=" << i << '\t' << keyList[i] << '\t' << f << endl;
                okay = false;
            }
        } catch (domain_error &e) {
            cout << "Error: " << e.what() << endl;
            cout << "i=" << i << '\t' << keyList[i] << '\t' << valueList[i] << endl;
            okay = false;
        } catch (...) {
            cout << "Unknown error" << endl;
            okay = false;
        }
    }

    cout << "        search all: " << OPF(okay) << endl;

    /*

    // step 3c: verify key list

    // verify that all keys are now in the dictionary, like step 2c
    for (bool & flag : flags)
        flag = false;

    if (!dict.getFirstKey(key))
        okay = false;

    do {
        for (int32_t i=0;i<DICTIONARY_MAX_SIZE;i++)
            if (keyList[i] == key) {
                flags[i] = true;
                break;
            }
    } while (dict.getNextKey(key));

    for (bool flag : flags)
        if (!flag)
            okay = false;

    cout << "getFirst/getNext 2: " << (okay ? "pass" : "fail") << endl;

    */

    // step 4a: update 50 random keys

    // pick 50 keys at random (repeats are okay) and give them a new random value.
    okay = true;
    for (int32_t i=0;i<50;i++) {
        int32_t
            pos = positions(*mt);

        // give the chosen key a new random value, remember it in our list
        valueList[pos] = Fraction(numbers(*mt),numbers(*mt));

        // now update the dictionary
        try {
            dict.update(keyList[pos],valueList[pos]);
        } catch (domain_error &e) {
            cout << "Error: " << e.what() << endl;
            cout << "i=" << i << '\t' << keyList[i] << '\t' << valueList[i] << endl;
            okay = false;
        } catch (...) {
            cout << "Unknown error" << endl;
            okay = false;
        }
    }

    cout << "            update: " << OPF(okay) << endl;

    // step 4b: verify updates

    // now search for every key and verify that the dictionary values match our
    // list
    okay = true;

    for (int32_t i=DICTIONARY_MAX_SIZE-1;i>=0;i--) {
        try {
            Fraction f = dict.search(keyList[i]);

            if (f != valueList[i]) {
                cout << "Value mismatch" << endl;
                cout << "i=" << i << '\t' << keyList[i] << '\t' << f << endl;
                okay = false;
            }
        } catch (domain_error &e) {
            cout << "Error: " << e.what() << endl;
            cout << "i=" << i << '\t' << keyList[i] << '\t' << valueList[i] << endl;
            okay = false;
        } catch (...) {
            cout << "Unknown error" << endl;
            okay = false;
        }
    }

    cout << "     verify update: " << OPF(okay) << endl;

    // step 5a: remove 50 random keys

    // clear all flags, prepare to remember which keys are gone
    for (auto &flag : flags)
        flag = false;

    int32_t
        pos;

    okay = true;
    for (int32_t i=0;i<50;i++) {
        // pick a key at random... one that hasn't already been removed
        do {
            pos = positions(*mt);
        } while (flags[pos]);
        flags[pos] = true;

        // remove the key from the dictionary
        try {
            dict.remove(keyList[pos]);
        } catch (domain_error &e) {
            cout << "Error: " << e.what() << endl;
            cout << "i=" << i << '\t' << keyList[i] << '\t' << valueList[i] << endl;
            okay = false;
        } catch (...) {
            cout << "Unknown error" << endl;
            okay = false;
        }
    }

    // now, remove the keys again, just to verify that each throws an exception
    for (int32_t i=0;i<DICTIONARY_MAX_SIZE;i++) {
        if (flags[i])
            // remove the key from the dictionary
            try {
                dict.remove(keyList[i]);

                cout << "Removed a deleted key" << endl;
                okay = false;   // should not get here
            } catch (domain_error &e) {
                // this is the expected behavior
            } catch (...) {
                cout << "Unknown error" << endl;
                okay = false;
            }
    }

    // confirm the size of the dictionary
    if (dict.size() != DICTIONARY_MAX_SIZE - 50) {
        cout << "Error: size is wrong" << endl;
        okay = false;
    }

    cout << "            remove: " << OPF(okay) << endl;

    // step 5b: search for removed keys

    okay = true;

    // each of these should throw an exception since they should not be there
    for (int32_t i=DICTIONARY_MAX_SIZE-1;i>=0;i--) {
        if (flags[i])
            try {
                dict.search(keyList[i]);

                okay = false;
            } catch (domain_error &e) {
                // expected behavior
            } catch (...) {
                cout << "Unknown error" << endl;
                okay = false;
            }
    }

    cout << "     verify update: " << OPF(okay) << endl;

    // step 5c: search for remaining keys, verify values

    // this is like the other search verifications
    okay = true;

    for (int32_t i=DICTIONARY_MAX_SIZE-1;i>=0;i--) {
        if (!flags[i])      // only check keys that are still in the dictionary
            try {
                Fraction f = dict.search(keyList[i]);

                if (f != valueList[i]) {
                    cout << "Value mismatch" << endl;
                    cout << "i=" << i << '\t' << keyList[i] << '\t' << f << endl;
                    okay = false;
                }
            } catch (domain_error &e) {
                cout << "Error: " << e.what() << endl;
                cout << "i=" << i << '\t' << keyList[i] << '\t' << valueList[i] << endl;
                okay = false;
            } catch (...) {
                cout << "Unknown error" << endl;
                okay = false;
            }
    }

    cout << "     verify remove: " << OPF(okay) << endl;

    // step 7a: remove remaining keys (clear)

    dict.clear();

    // step 7b: verify

    okay = true;
    if (!dict.isEmpty()) {
        cout << "Dictionary not empty after clear()" << endl;
        okay = false;
    }

    if (dict.size() != 0) {
        cout << "Dictionary size not zero after clear()" << endl;
        okay = false;
    }

    // check all of the keys, they should all fail
    for (int32_t i=DICTIONARY_MAX_SIZE-1;i>=0;i--) {
        try {
            dict.search(keyList[i]);

            okay = false;
        } catch (domain_error &e) {
            // expected behavior
        } catch (...) {
            cout << "Unknown error" << endl;
            okay = false;
        }
    }

    cout << "      verify clear: " << OPF(okay) << endl;

    // all done
    return 0;
}
