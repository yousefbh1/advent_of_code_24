#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

struct Pos {
    int x;
    int y;
    char dir;
};

Pos createMap(std::vector<std::vector<char>> &grid, const std::string &filename) {
    std::ifstream file(filename);
    
    Pos start{-1, -1, '?'};
    std::string line;
    while (std::getline(file, line)) {
        std::vector<char> row(line.begin(), line.end());
        int rowIndex = grid.size();
        // look for the guard marked by '^'
        for (int col = 0; col < static_cast<int>(row.size()); ++col) {
            if (row[col] == '^') {
                start = Pos{rowIndex, col, '^'};
            }
        }
        grid.push_back(std::move(row));
    }
    return start;
}

char turnRight(char currDir, const char pos_arrows[4]) {
    int idx = 0;
    for (int i = 0; i < 4; i++) {
        if (pos_arrows[i] == currDir) {
            idx = i;
            break;
        }
    }
    return pos_arrows[(idx + 1) % 4];
}

int simulateGuard(std::vector<std::vector<char>> &grid, Pos start, 
                  const std::unordered_map<char, Pos> &arrow_map, 
                  const char pos_arrows[4],
                  char OBSTACLE, char EMPTY) {
    int uniqueCount = 0;
    
    if (start.x >= 0 && start.x < static_cast<int>(grid.size()) &&
        start.y >= 0 && start.y < static_cast<int>(grid[0].size())) {
        grid[start.x][start.y] = 'X';
        uniqueCount++;
    }
    
    Pos current = start;
    char currentDir = start.dir;
    
    while (true) {
        Pos delta = arrow_map.at(currentDir);
        int nx = current.x + delta.x;
        int ny = current.y + delta.y;
        
        if (nx < 0 || nx >= static_cast<int>(grid.size()) ||
            ny < 0 || ny >= static_cast<int>(grid[0].size())) {
            break;
        }
        
        if (grid[nx][ny] == OBSTACLE) {
            currentDir = turnRight(currentDir, pos_arrows);
            continue;  // try new direction next iteration.
        }
        
        current.x = nx;
        current.y = ny;
        if (grid[current.x][current.y] == EMPTY) {
            grid[current.x][current.y] = 'X';
            uniqueCount++;
        }
        // continue in current direction.
    }
    
    return uniqueCount;
}

int main(int argc, char* argv[]) {
    
    std::vector<std::vector<char>> grid;
    Pos start = createMap(grid, argv[1]);
    if (start.x == -1) {
        return 1;
    }
    
    const char OBSTACLE = '#';
    const char EMPTY = '.';
    
    const char pos_arrows[4] = {'^', '>', 'v', '<'};
    std::unordered_map<char, Pos> arrow_map = {
        {'^', {-1,  0, '^'}}, 
        {'>', { 0,  1, '>'}}, 
        {'v', { 1,  0, 'v'}}, 
        {'<', { 0, -1, '<'}} 
    };
    
     // while guard next position is in bounds
        // if next position is # turn 90 degrees right (want char array, with corresponding direction map)
            // need to check next pos again, i.e continue
        // if it's not marked X, mark X, unique_pos++
    // else, next position is out of bounds
        // if it's not marked X, mark X, unique_pos++
    int uniqueVisited = simulateGuard(grid, start, arrow_map, pos_arrows, OBSTACLE, EMPTY);
    
    // check grid
    for (const auto &row : grid) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << "\n";
    }
    std::cout << "unique positions visited: " << uniqueVisited << "\n";
    
    return 0;
}
