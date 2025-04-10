#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <vector>

bool is_safe(const std::vector<int>& report) {
    if (report.size() < 2) return false;

    int diff = report[1] - report[0];
    if (std::abs(diff) < 1 || std::abs(diff) > 3) return false;

    bool increasing = diff > 0;

    for (size_t i = 1; i < report.size(); ++i) {
        int d = report[i] - report[i - 1];
        if (std::abs(d) < 1 || std::abs(d) > 3) return false;
        if (increasing && d <= 0) return false;
        if (!increasing && d >= 0) return false;
    }

    return true;
}

bool is_safe_with_one_removed(const std::vector<int>& report) {
    for (size_t i = 0; i < report.size(); ++i) {
        std::vector<int> copy = report;
        copy.erase(copy.begin() + i);
        if (is_safe(copy)) return true;
    }
    return false;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " input_file.txt" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    std::string line;
    int safeReports = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::vector<int> report;
        int num;
        while (ss >> num) {
            report.push_back(num);
        }

        if (is_safe(report) || is_safe_with_one_removed(report)) {
            ++safeReports;
        }
    }

    file.close();
    std::cout << "Total safe reports (with dampener): " << safeReports << std::endl;
    return 0;
}
