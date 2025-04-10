#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::cout << "arg: " << argv[1] << std::endl;
    } else {
        return 0;
    }
    vector<int> listLeft;
    vector<int> listRight;
    std::string filename = argv[1];
    std::ifstream f;
    f.open(filename);
    int intOut = 0;
    int counter = 0;
    std::string line;
    while (std::getline(f, line)) {
        std::stringstream ss(line);
        while(ss >> intOut) {
            if (counter % 2 == 0) {
                listLeft.push_back(intOut);
            } else {
                listRight.push_back(intOut);
            }
            counter++;
        }
    }

    f.close();

    std::sort(listLeft.begin(), listLeft.end());
    std::sort(listRight.begin(), listRight.end());
    std::unordered_map<int, int> seenRight;

    int simTotal = 0;
    for (size_t i = 0; i < listRight.size(); ++i) {
        seenRight[listRight[i]]++;
    }

    for (size_t i = 0; i < listLeft.size(); ++i) {
        if (seenRight.find(listLeft[i]) != seenRight.end()) {
            simTotal += (listLeft[i] * seenRight[listLeft[i]]);
        }
    }

    std::cout << "simTotal = " << simTotal << std::endl;

    return 0;
}