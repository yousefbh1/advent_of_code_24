#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int evaluateLeftToRight(const vector<int>& nums, const vector<char>& ops) {
    int result = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        if (ops[i - 1] == '+')
            result += nums[i];
        else
            result *= nums[i];
    }
    return result;
}

bool canReachTarget(int target, const vector<int>& nums) {
    size_t opsCount = nums.size() > 0 ? nums.size() - 1 : 0;

    if (opsCount == 0)
        return nums.size() == 1 && nums[0] == target;

    int combinations = 1 << opsCount;
    vector<char> ops(opsCount);

    for (int mask = 0; mask < combinations; ++mask) {
        for (size_t i = 0; i < opsCount; ++i) {
            ops[i] = (mask & (1 << i)) ? '+' : '*';
        }
        if (evaluateLeftToRight(nums, ops) == target)
            return true;
    }
    return false;
}

int main(int argc, char* argv[]) {

    ifstream infile(argv[1]);

    long long total = 0;
    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        int target;
        char colon;
        ss >> target >> colon;

        vector<int> nums;
        int x;
        while (ss >> x)
            nums.push_back(x);

        if (canReachTarget(target, nums))
            total += target;
    }

    cout << total << "\n";
    return 0;
}
