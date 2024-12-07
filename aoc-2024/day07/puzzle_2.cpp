// o3 - ~430ms
// o0 - ~900ms

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdint.h>
#include <cassert>
#include <algorithm>
#include <chrono>
#include <string.h>

#include <random>

unsigned int max_num_ops = 11; // **according to input max 12 operations**

uint64_t concatenate(uint64_t x, uint64_t y) {
    uint64_t pow = 10;
    while(y >= pow)
        pow *= 10;
    return x * pow + y;        
}

char* dec_to_base3(unsigned int dec) {
    // std::string res_base3;
    // res_base3.resize(num_places);
    char* res_base3 = new char[max_num_ops + 1];

    int i = 0;
    while(dec != 0) {
        unsigned int dig = dec % 3;
        // res_base3 += std::to_string(dig);
        res_base3[i] = '0' + dig;
        dec /= 3;

        i++;
    }

    for(int j = i; j < max_num_ops; j++) {
        res_base3[j] = '0';
    }

    res_base3[max_num_ops] = '\0';
    strrev(res_base3);

    // std::reverse(res_base3.begin(), res_base3.end());

    return res_base3;
}

struct Line {
    uint64_t result;
    std::vector<uint64_t> nums;
};

int main() {
    std::ifstream ifs {"input.txt"};
    std::vector<Line> lines;

    for(std::string line; std::getline(ifs, line);) {
        if(line.empty())
            break;
        
        std::string s1;
        std::stringstream ss;

        unsigned int i = 0;
        for(; i < line.length(); i++) {
            if(line[i] == ':')
                break;

            s1 += line[i];
        }

        std::string s2 {line.begin() + i + 1, line.end()};
        ss << s2;

        Line line_data;
        
        // load result
        std::stringstream ss_res;
        ss_res << s1;
        ss_res >> line_data.result;

        // load nums
        for(uint64_t x; ss >> x;)
            line_data.nums.push_back(x);

        lines.push_back(line_data);
    }

    uint64_t final_sum = 0;

    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // pre-generate operand combinations upto 10 operands
    // "base-3 counting pattern"
    // + -> 0
    // * -> 1
    // || -> 2
    unsigned int max_num_seqs = pow(3, max_num_ops); // upper bound not included
    std::vector<char*> operations;
    operations.resize(max_num_seqs);

    for(unsigned int j = 0; j < max_num_seqs; j++)
        operations[j] = dec_to_base3(j);
        // operations.push_back(dec_to_base3(j, max_num_ops));

    {
        // auto rng = std::default_random_engine {};

        // one digit
        // std::shuffle(operations.begin(), operations.begin() + 3, rng);
        
        // // two digit
        // std::shuffle(operations.begin() + 3, operations.begin() + 9, rng);
        
        // // three digit
        // std::shuffle(operations.begin() + 9, operations.begin() + 27, rng);
        
        // // four digit
        // std::shuffle(operations.begin() + 27, operations.begin() + 81, rng);
        
        // five digit
        // std::shuffle(operations.begin() + 81, operations.begin() + 243, rng);
        
        // // six digit
        // std::shuffle(operations.begin() + 243, operations.begin() + 729, rng);
        
        // // seven digit
        // std::shuffle(operations.begin() + 729, operations.begin() + 2187, rng);
        
        // // 8 digit
        // std::shuffle(operations.begin() + 2187, operations.begin() + 6561, rng);
    }

    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    // std::cout << "time combs: " << elapsed_time << "ms\n";


    // check lines
    for(unsigned int i = 0; i < lines.size(); i++) {
        Line& line = lines[i];
        
        // "base-3 counting pattern"
        // + -> 0
        // * -> 1
        // || -> 2
        unsigned int num_ops = line.nums.size() - 1;
        unsigned int num_seqs = pow(3, num_ops); // upper bound not included

        // std::vector<std::string> operations;
        // for(unsigned int j = 0; j < num_seqs; j++)
        //     operations.push_back(dec_to_base3(j, num_ops));

        bool res_equal = false;
        unsigned int seq_index_eq = 0;

        for(unsigned int seq_index = 0; seq_index < num_seqs; seq_index++) {
            uint64_t calc_res = line.nums[0];
            char* sequence = operations[seq_index];

            // rightmost bit => leftmost operation and so on
            unsigned int nums_sz = line.nums.size();
            for(unsigned int j = 1; j < nums_sz; j++) {
                auto& num = line.nums[j];
                char op = sequence[max_num_ops-j];

                if(op == '0')
                    calc_res *= num;
                else if(op == '1')
                    calc_res += num;
                else if(op == '2')
                    calc_res = concatenate(calc_res, num);
                    // calc_res = std::stoull(std::to_string(calc_res) + std::to_string(line.nums[j]));

                // only break if last num i.e checked all numbers
                if(calc_res == line.result && j == (nums_sz - 1)) {
                    res_equal = true;
                    seq_index_eq = seq_index;
                    goto loop_exit;
                } else if(calc_res > line.result)
                    break;
            }
        }

        loop_exit:
        if(res_equal) {
            final_sum += line.result;
            // std::cout << "operation " << operations[seq_index_eq] << ". on line " << i << '\n';
        }
    }

    // memory is freed at the end of program anyway    
    // for(char* str : operations)
    //     delete[] str;

    std::cout << "finalsum=" << final_sum;
}