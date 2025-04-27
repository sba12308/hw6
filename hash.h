#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        //initialize w array with zeros
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        
        //process the string in groups of 6 characters, starting from the end
        int length = k.length();
        int wIndex = 4; //start from w[4] for the last group
        
        for (int i = length - 1; i >= 0; i -= 6) {
            unsigned long long value = 0;
            
            //process up to 6 characters in reverse order
            int start = std::max(0, i - 5);
            for (int j = i; j >= start; --j)
            {
                HASH_INDEX_T digit = letterDigitToNumber(k[j]);
                value = value * 36 + digit;
            }
            
            w[wIndex] = value;
            wIndex--;
        }
        
        //compute the final hash value
        unsigned long long hash = 0;
        for (int i = 0; i < 5; ++i)
        {
            hash += rValues[i] * w[i];
        }
        
        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        //convert to lowercase if it's an uppercase letter
        if (letter >= 'A' && letter <= 'Z')
        {
            letter = letter - 'A' + 'a';
        }
        
        //convert letters a-z to 0-25
        if (letter >= 'a' && letter <= 'z')
        {
            return letter - 'a';
        }
        //convert digits 0-9 to 26-35
        else if (letter >= '0' && letter <= '9')
        {
            return letter - '0' + 26;
        }
        //invalid character (shouldn't happen per problem statement)
        return 0;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
