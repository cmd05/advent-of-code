#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <set>

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

int main() {
    std::ifstream ifs {"input.txt"};

    // empty - 0
    // blocked - 1
    // rows: 0, 1 ...
    // cols: 0, 1 ...
    std::vector<std::vector<int>> map;
    std::set<std::pair<int, int>> visited;
    std::pair<int, int> init_guard;

    int i = 0;
    for(std::string line; std::getline(ifs, line); i++) {
        // std::cout << line << '\n';
        std::vector<int> v;
        
        for(int j = 0; j < line.length(); j++) {
            char c = line[j];

            if(c == '.')
                v.push_back(0);
            else if(c == '^') {
                v.push_back(0);
                init_guard = {i, j};
            } else if(c == '#')
                v.push_back(1);
        }

        map.push_back(v);
    }

    int nrows = map.size();
    int ncols = map[0].size();
    
    // start movement of guard
    int r = init_guard.first, c = init_guard.second;
    int r1 = r, c1 = c;
    char dir = 'U';

    while(!(r < 0 || c < 0 || r >= nrows || c >= ncols)) {
        if(map[r][c] == 1) {
            dir = new_dir(dir);

            // reset to last position
            r = r1, c = c1;
        } else {
            // move successful
            visited.insert({r, c});
        }

        // save last position
        r1 = r, c1 = c;
        
        // move
        if(dir == 'U') r -= 1;
        if(dir == 'R') c += 1;
        if(dir == 'D') r += 1;
        if(dir == 'L') c -= 1;
    }

    std::cout << visited.size() << '\n';
    std::cout << r << ' ' << c << '\n';
}