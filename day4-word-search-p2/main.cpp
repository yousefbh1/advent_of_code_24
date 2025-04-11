#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <array>
#include <unordered_map>

int main(int argc, char* argv[]) {
    if (argc > 0) {
        std::cout << "arg: " << argv[1] << std::endl;
    }

    std::vector<std::string> grid;

    std::ifstream file(argv[1]);
    std::string line;
    while(getline(file, line)) {
        grid.push_back(line);
    }

    file.close();

    for (int i = 0; i < grid.size(); ++i) {
        std::cout << grid[i] << '\n';
    }

    const int NUM_DIRECTIONS = 8;
    // search each node in each direction
    const std::array<std::pair<int, int>, NUM_DIRECTIONS> dirs = {{
        // (ROW_OFFSET, COLUMN OFFSET)
        {-1, -1}, // check one up, one left
        {-1, 1}, // check one up, one right
        {1, -1}, // check one down, one left
        {1, 1} // check one down, one right
    }};

    std::unordered_map<int, char> matchIt;
    matchIt[1] = 'M';
    matchIt[2] = 'S';
    matchIt[3] = 'M';
    matchIt[4] = 'S';
    
    int wordCount = 0;
    const char START_LETTER = 'A';

    for (int r = 1; r < grid.size() - 1; ++r) {
        for (int c = 1; c < grid[0].size() - 1; ++c) {
            if (grid[r][c] != 'A') continue;
    
            // Top-left to bottom-right diagonal
            char tl = grid[r - 1][c - 1];
            char br = grid[r + 1][c + 1];
            bool firstDiag = (tl == 'M' && br == 'S') || (tl == 'S' && br == 'M');
    
            // Top-right to bottom-left diagonal
            char tr = grid[r - 1][c + 1];
            char bl = grid[r + 1][c - 1];
            bool secondDiag = (tr == 'M' && bl == 'S') || (tr == 'S' && bl == 'M');
    
            if (firstDiag && secondDiag) {
                wordCount++;
            }
        }
    }


    std::cout << "num words found: " << wordCount << std::endl;
    return 0;
    
}