#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <array>

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
      
        // Add your code here
        std::array<unsigned long long, 5> w{0, 0, 0, 0, 0};

        std::string lower_k;

        // For every character in the string, change the letters to lowercase
        for (char c : k) {
          if (std::isalnum(c)){
            lower_k += std::tolower(c);
          }
        }

        // Create variables for next loop
        int totalLength = lower_k.length();
        int groupCount = 0;

        // Using base 36 integers, 
        for(int i = totalLength; i > 0 && groupCount < 5; i -= 6, groupCount++) {
          int start = std::max(0, i - 6);
          std::string group = lower_k.substr(start, i - start);

          unsigned long long groupValue = 0;

          // all of the characters in the 6 pod group, turn the value into a 36 base number
          for (char ch : group) {
            groupValue = groupValue * 36 + letterDigitToNumber(ch);
          }

          w[4 - groupCount] = groupValue;
        }

        unsigned long long hash = 0;
        for(int i = 0; i < 5; i++) {
          hash += rValues[i] * w[i];
        }

        return hash;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        // Converts the 26 letters to a number
        if (std::isalpha(letter)) {
          return std::tolower(letter) - 'a';
        }

        // Focuses on the digits, adds 26 to the number
        else if (std::isdigit(letter)) {
          return 26 + (letter - '0');
        }

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
