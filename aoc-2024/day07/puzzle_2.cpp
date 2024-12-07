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

std::string dec_to_base3(unsigned int dec, unsigned int num_places) {
    std::string res_base3;

    while(dec != 0) {
        unsigned int dig = dec % 3;
        res_base3 += std::to_string(dig);
        dec /= 3;
    }

    std::reverse(res_base3.begin(), res_base3.end());

    std::string padding(num_places - res_base3.length(), '0');
    res_base3 = padding + res_base3;

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
    unsigned int max_num_ops = 11; // **according to input max 12 operations**
    unsigned int max_num_seqs = pow(3, max_num_ops); // upper bound not included
    std::vector<std::string> operations;

    for(unsigned int j = 0; j < max_num_seqs; j++)
        operations.push_back(dec_to_base3(j, max_num_ops));

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
            std::string sequence = operations[seq_index];

            // rightmost bit => leftmost operation and so on
            for(unsigned int j = 1; j < line.nums.size(); j++) {
                if(sequence[max_num_ops-j] == '0')
                    calc_res += line.nums[j];
                else if(sequence[max_num_ops-j] == '1')
                    calc_res *= line.nums[j];
                else if(sequence[max_num_ops-j] == '2')
                    calc_res = std::stoull(std::to_string(calc_res) + std::to_string(line.nums[j]));

                // only break if last num i.e checked all numbers
                if(calc_res == line.result && j == (line.nums.size() - 1)) {
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

    std::cout << "finalsum=" << final_sum;
}