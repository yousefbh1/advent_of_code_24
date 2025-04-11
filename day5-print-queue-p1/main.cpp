#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

void construct_map(std::unordered_map<int, std::vector<int>>& map, std::ifstream &file) {
    // part 1, while line != " "
    // get each line, int 1 is key in  hashmap
    // discard |
    // int 2 is appeded to vector which key points to in hashmap
    std::string line;
    while(getline(file, line) && line != "") {
        int key;
        int val;
        char disc;
        std::stringstream ss(line);
        ss >> key >> disc >> val;
        map[key].push_back(val);
    }
}

int main(int argc, char* argv[]) {
    if(argc > 1) {
        std::cout << "arg: " << argv[1] << std::endl;
    }

    // want to print the middle page number totals for each correct ordering

    // hashmap, left list is the key, all the numbers that should before it 
    // appended to vector in the value 
    // 
    // for each ordering, if key not found, move on
    // hold a seen set which contains all the numbers we've seen in the ordering thus far
    // if any of the elements in the value vector in map appear in the seen array, the ordering
    // must be incorrect
    std::string line;
    std::ifstream file(argv[1]);
    std::unordered_map<int, std::vector<int>> map;

    construct_map(map, file);
    int res = 0;
    
    // part 2
    while(std::getline(file, line)) {
        // std::cout << "line: " << line << std::endl;
        std::stringstream ss(line);
        std::string keyString;
        std::unordered_set<int> seen;
        seen.clear();
        bool correct = true;
        std::vector<int> keys;
        while (std::getline(ss, keyString, ',')) {
            int key = std::stoi(keyString);
            keys.push_back(key);
        }

        // if key appears in any prev keys value vector, it is incorrect
        for (int i = 0; i < keys.size(); ++i) {
            int key = keys[i];
            if (map.count(key)) {
                for (int prereq : map[key]) {
                    if (seen.count(prereq)) {
                        correct = false;
                        break;
                    }
                }
            }

            seen.insert(key);
            if (!correct) break;
        }

        if (correct) {
            // add the middle number
            // which is the floor of len / 2
            int mid = keys.size() / 2;
            std::cout << "adding " << keys[mid] << " to res\n";
            res += keys[mid];
        }
    }


    file.close();

    std::cout << "res: " << res << std::endl;


    return 0;
}