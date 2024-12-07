#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdint.h>
#include <cassert>

// finalsum=126830334 low
// finalsum=126830334 low
// finalsum=2850017430 low
// finalsum=261132851633 ("not the right answer")
// finalsum=261119341725 (not right answer)
// finalsum=1545167941823 (not the right answer)

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
        for(uint64_t x; ss >> x;) {
            // std::cout << x << " ";
            line_data.nums.push_back(x);
        }

        lines.push_back(line_data);
        // std::cout << '\n';
    }

    uint64_t final_sum = 0;

    // take care of `int` overflow

    // check lines
    for(unsigned int i = 0; i < lines.size(); i++) {
        Line& line = lines[i];

        // check how many operators needed
        unsigned int num_ops = line.nums.size() - 1;

        // "binary counting pattern"
        // + -> 0
        // * -> 1
        // unsigned int operations = 0;
        unsigned int max_bin = pow(2, num_ops); // upper bound not included

        // // rightmost bit => leftmost operation

        // for(unsigned int op_seq = 0; op_seq < max_bin; op_seq++) {
        //     for(int j = 0; j < num_ops; j++) {
        //         if((op_seq >> j) & 1)
        //     }
        // }
        std::vector<unsigned int> operations;

        for(unsigned int j = 0; j < max_bin; j++)
            operations.push_back(j);
        

        bool res_equal = false;
        unsigned int seq_index_eq = 0;

        for(unsigned int seq_index = 0; seq_index < operations.size(); seq_index++) {
            uint64_t calc_res = line.nums[0];
            unsigned int sequence = operations[seq_index];

            // if(i == 690 && sequence == 27) {
            //     std::cout << "here";
            // }

            // rightmost bit => leftmost operation and so on
            for(unsigned int j = 1; j < line.nums.size(); j++) {
                uint64_t calc_tmp = calc_res;

                if((sequence >> (j-1)) & 1)
                    calc_res *= line.nums[j];
                else
                    calc_res += line.nums[j];
                
                if(calc_res < calc_tmp) {
                    std::cout << ("OVERFLOW");
                    exit(0);
                }

                // only break if last num i.e checked all numbers
                if(calc_res == line.result && j == (line.nums.size() - 1)) {
                    res_equal = true;
                    seq_index_eq = seq_index;
                    goto loop_exit;
                } else if(calc_res > line.result) {
                    break;
                }
            }
        }

        loop_exit:
        if(res_equal) {
            uint64_t tmp_final_sum = final_sum;
            final_sum += line.result;

            if(final_sum <= tmp_final_sum) {
                std::cout << ("OVERFLOW");
                exit(0);
            }

            std::cout << "operation " << seq_index_eq << ". on line " << i << '\n';
        }
    }

    std::cout << "finalsum=" << final_sum;
}