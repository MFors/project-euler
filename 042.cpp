/*
  Project Euler Problem 42
  Mikael Fors 2014

  "By converting each letter in a word to a number corresponding to its
   alphabetical position and adding these values we form a word value.
   For example, the word value for SKY is 19 + 11 + 25 = 55 = t_10.

   If the word value is a triangle number then we shall call the word a triangle
   word.

   Using words.txt, a 16K text file containing nearly two-thousand common
   English words, how many are triangle words?"
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class TriangleNumberChecker {
        int maxVal, n;
        map<int, bool> cache;

    public:
        TriangleNumberChecker();
        bool isTriangleNumber(int value);
};

TriangleNumberChecker::TriangleNumberChecker() {
    maxVal = n = 0;
}

bool TriangleNumberChecker::isTriangleNumber(int value) {
    // If no cache or if our max triangle number cached
    // is less than value, we calculate more triangles
    int shouldGenerate = cache.size() ? 0 : 1;
    shouldGenerate = !shouldGenerate ?
                        ((cache.rbegin()->first) >= value ?
                                  0 : 1)
                        : 1;

    if(shouldGenerate) {
        while(value >= maxVal) {
            ++n;
            maxVal = (n * (n + 1)) >> 1;
            cache[maxVal] = 1;
        }
    }

    return cache.find(value) != cache.end();
}

int main() {
    string data;
    ifstream file("042.data");
    uint i = 1, count = 0, current = 0;
    TriangleNumberChecker triangle;

    while(getline(file, data));
    file.close();

    while(i < data.size()) {
        if(data[i] == '\"') {
            i += 2; // "," <-- Skip 2 (3rd taken by default ++i)
            count += int(triangle.isTriangleNumber(current));
            current = 0;
        } else {
            current += data[i] - 'A' + 1;
        }
        ++i;
    }
    cout << "The answer is: " << count << endl;
    return 0;
}
