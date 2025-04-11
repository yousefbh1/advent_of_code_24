#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <set>
#include <array>

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
        {1, 0}, // N
        {1, 1}, // NE
        {0, 1}, // E
        {-1, 1}, // SE
        {-1, 0}, // S
        {-1, -1}, // SW
        {0, -1}, // W
        {1, -1} // NW
    }};
    
    int wordCount = 0;
    const int NUM_IN_WORD = 4;
    const char word[NUM_IN_WORD] = {'X', 'M', 'A', 'S'};

    for (int row = 0; row < grid.size(); row++) {
        for (int col = 0; col < grid[0].size(); col++) {
            if (grid[row][col] == word[0]) {
                for (int checkD = 0; checkD < NUM_DIRECTIONS; checkD++) { // for every direction
                    int charCounter = 0;
                    int dRow = row;
                    int dCol = col;
                    while (dRow >= 0 && dRow < grid.size() 
                        && dCol >= 0 && dCol < grid[0].size() && charCounter < 4) {
                            // check if next letter is valid
                            if (grid[dRow][dCol] != word[charCounter]) {
                                // failed, check next direction
                                break;
                            }
                            charCounter++;
                            dRow += dirs[checkD].first;
                            dCol += dirs[checkD].second;
                    }
                    // failed or reach end of word
                    if (charCounter == 4) {
                        wordCount++;
                    }
                }
            }
        }
    }


    std::cout << "num words found: " << wordCount << std::endl;
    return 0;
    
}