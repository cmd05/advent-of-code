// gpx puzzle_2.cpp 
// no. of loops=1770
// time: 3098ms

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <chrono>
#include <cassert>

inline constexpr char new_dir(const char dir) {
    if(dir == 'U')
        return 'R';
    if(dir == 'R')
        return 'D';
    if(dir == 'D')
        return 'L';
    if(dir == 'L')
        return 'U';
    
    return 'N'; // invalid argument
}

bool DEBUG_CODE = false;

int main() {
    std::chrono::steady_clock::time_point CODE_BEGIN = std::chrono::steady_clock::now();

    std::ifstream ifs {"input.txt"};

    std::vector<std::vector<char>> map;

    int nrows = 0;
    int ncols = 0;

    // empty - 0
    // blocked - 1
    // rows: 0, 1 ...
    // cols: 0, 1 ...
    std::pair<int, int> init_guard;

    int i = 0;
    for(std::string line; std::getline(ifs, line); i++) {
        // std::cout << line << '\n';
        std::vector<char> v;
        
        for(int j = 0; j < line.length(); j++) {
            char c = line[j];
            v.push_back(c);

            if(c == '^')
                init_guard = {i, j};
        }

        map.push_back(v);
    }

    nrows = map.size();
    ncols = map[0].size();

    // ------ mark the map first -------
    int r = init_guard.first, c = init_guard.second;
    int r1 = r, c1 = c;
    char dir = 'U';

    while(!(r < 0 || c < 0 || r >= nrows || c >= ncols)) {
        if(map[r][c] == '#') {
            dir = new_dir(dir);

            // reset to last position
            r = r1, c = c1;
        } else {
            // move successful
            map[r][c] = 'X';
        }

        // save last position
        r1 = r, c1 = c;
        
        // move
        if(dir == 'U') r -= 1;
        if(dir == 'R') c += 1;
        if(dir == 'D') r += 1;
        if(dir == 'L') c -= 1;
    }

    if(DEBUG_CODE) std::cout << "exit: " << r << ' ' << c << '\n';

    // std::ofstream ofs {"out.txt"};
    std::ofstream ofs {"out2.txt"};
    // for(int i = 0; i < nrows; i++) {
    //     std::string s {map[i].begin(), map[i].end()};
    //     ofs << s << '\n';
    // }

    // ---- test obstacles ----

    int count = 0;

    for(int i = 0; i < nrows; i++) {
        for(int j = 0; j < ncols; j++) {
            // put an 'O' at i,j
            // optimize by presimulating and only testing obstacles at 'X' positions
            
            if(map[i][j] != 'X' || (i == init_guard.first && j == init_guard.second)) {
                // std::cout << "skip\n";
                continue;
            } 
            //     std::cout << "placed " << i << " " << j << '\n';
            char new_obs = 'O';

            map[i][j] = new_obs;

            bool looping = false;
            char loop_dir;
            bool first_path_iteration = true;
            bool record_path = false;

            std::set<std::pair<int, int>> path;
            std::set<std::pair<int, int>> to_trace;
            std::set<std::pair<int,int>> path_blocks;

            int block_counter = 0;
            std::pair<int, int> prev4th_block = {-5,-5};

            // start movement of guard
            int r = init_guard.first, c = init_guard.second;
            int r1 = r, c1 = c;
            char dir = 'U';
            bool might_loop_new_dir = false;
            char new_loop_dir;

            // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

            while(!(r < 0 || c < 0 || r >= nrows || c >= ncols)) {
                if(map[r][c] == '#' || map[r][c] == new_obs) {
                    char tmp_dir = dir;
                    dir = new_dir(dir);

                    if(record_path && first_path_iteration) {
                        if(block_counter % 4 != 0) {
                            block_counter++;
                        } else {
                            if(prev4th_block == std::pair<int, int>{r,c}) {
                                if(DEBUG_CODE) std::cout << ("BLOCKFAIL");
                                // exit(0);
                                looping = true;
                                break;
                            }
                            // std::cout << prev4th_block.first << " " << prev4th_block.second << '\n';
                            prev4th_block = {r, c};
                            block_counter++;
                        }
                    }

                    if(map[r][c] == new_obs) {
                        if(DEBUG_CODE) std::cout << "hit " << tmp_dir << '\n';

                        if(!record_path) {
                            record_path = true;
                            loop_dir = tmp_dir;
                            first_path_iteration = true;
                            path.insert({r1, c1});
                        } else if(first_path_iteration && tmp_dir == loop_dir) {
                            path.insert({r1, c1}); // first trace has been complete
                            
                            // set path to trace
                            to_trace = path;
                            path.clear();

                            first_path_iteration = false;
                        } else if(tmp_dir == loop_dir) {
                            // not the first iteration
                            // path.insert({r1, c1}); // already recorded

                            // check if path matches trace
                            if(path == to_trace) {
                                looping = true;
                            } else {
                                if(DEBUG_CODE) std::cout << "FALSE";
                                looping = false;
                            }

                            break;
                        }

                        if(tmp_dir != loop_dir) {
                            // std::cout << ("DIRFAIL");
                            // exit(0);
                            if(!might_loop_new_dir) {
                                might_loop_new_dir = true;
                                new_loop_dir = tmp_dir;
                            } else if(tmp_dir == new_loop_dir) {
                                if(DEBUG_CODE) std::cout << "NEWLOOPCHECK\n";
                                looping = true;
                                break;
                            }
                        }
                    }

                    // reset to last position
                    r = r1;
                    c = c1;
                } else if(record_path) {
                    // move successful
                    path.insert({r, c});
                }


                // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                // auto time = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

                // // std::cout << time << '\n';
                // if(time > 100000) {
                //     std::cout << "TIMEDELAY\n";
                //     looping = true;
                //     break;
                //     // std::cout << ("TIME");
                // }

                // if(path.size() > 1000)
                //     std::cout << path.size() << '\n';

                // save last position
                r1 = r;
                c1 = c;

                // move
                if(dir == 'U') r -= 1;
                if(dir == 'R') c += 1;
                if(dir == 'D') r += 1;
                if(dir == 'L') c -= 1;
            }

            map[i][j] = 'X'; // remove our obstacle

            if(looping) {
                if(DEBUG_CODE) std::cout << "Put an obstacle at " << i << " " << j << "\n---------------\n";
                count++;
            } else {
                // std::cout << "exit: " << r << ' ' << c << '\n';
                if(DEBUG_CODE) std::cout << "fail" << "\n---------------\n";
            }
        }
    }

    std::chrono::steady_clock::time_point CODE_END = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(CODE_END - CODE_BEGIN).count();

    std::cout << "no. of loops=" << count << '\n';
    std::cout << "time: " << elapsed_time << "ms"; 
}