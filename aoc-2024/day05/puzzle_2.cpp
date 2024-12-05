#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>
#include <algorithm>

// https://stackoverflow.com/a/919661
inline constexpr std::size_t hash(unsigned int v1, unsigned int v2) {
    unsigned int x1 = 0; // lower
    unsigned int x2 = 0; // higher

    if(v2 < v1) {
        x1 = v2;
        x2 = v1;
    } else {
        x1 = v1;
        x2 = v2;
    }
    
    // std::string s = std::to_string(x1) + std::to_string(x2);
    // return std::hash<std::string>{}(s);

    return ((((x1 + x2) * (x1 + x2 + 1)) / 2) + x2);
}

int main() {
    std::unordered_map<std::size_t, unsigned int> rules;
    std::ifstream ifs{"day5_input.txt"};

    unsigned int a, b;
    char sep;

    // read rules
    for(std::string line; std::getline(ifs, line);) {
        if(line.empty())
            break;

        std::stringstream ss {line};
        ss >> a >> sep >> b;

        // assert(rules.find(hash(a, b)) == rules.end() && "Collision of hash");

        rules[hash(a, b)] = a; // put first number as value
    }

    // read updates
    unsigned int sum = 0;

    for(std::string line; ifs >> line;) {
        std::stringstream ss {line};
        std::vector<unsigned int> vec;

        unsigned int n;
        char sep;

        for(; ss >> n >> sep;) vec.push_back(n); // read numbers
        ss >> n; vec.push_back(n); // last number

        std::size_t sz = vec.size();
        bool correct = true;

        for(std::size_t i = 0; i < sz; i++) {
            for(std::size_t j = i+1; j < sz; j++) {
                auto it = rules.find(hash(vec[j], vec[i]));

                if(it != rules.end() && it->second != vec[i]) {
                    correct = false;
                    goto loop_exit;
                }
            }
        }

    loop_exit:
        if(!correct) {
            // reorder update correctly
            std::sort(vec.begin(), vec.end(), [&rules](auto a, auto b) {
                auto it = rules.begin();
                if((it = rules.find(hash(a, b))) != rules.end())
                    return a == it->second;
                return a < b;
            });

            std::size_t mid = vec.size() / 2; // assuming only odd no. of elements
            sum += vec[mid];
        }
    }

    std::cout << "Sum = " << sum;
}