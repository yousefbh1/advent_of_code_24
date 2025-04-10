#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <unordered_set>
#include <stack>



int main(int argc, char* argv[]) {

    if (argc > 0) {
        std::cout << "arg: " << argv[1] << std::endl;
    } else {
        exit(1);
    }

    int result = 0;

    std::ifstream f(argv[1]);
    std::string input((std::istreambuf_iterator<char>(f)),
                        std::istreambuf_iterator<char>());

    f.close();
    
    std::regex pattern(R"((do\(\))|(don't\(\))|(mul\((\d{1,3}),(\d{1,3})\)))");
    std::sregex_iterator it(input.begin(), input.end(), pattern);
    std::sregex_iterator end;
    bool enabled = true;

    for (; it != end; ++it) {
        std::smatch match = *it;
        // std::cout << "new line\n";
        // std::cout << match[0] << std::endl; // full line
        // std::cout << match[1] << std::endl; // do()
        // std::cout << match[2] << std::endl; // dont()
        // std::cout << match[3] << std::endl; // mul line
        // std::cout << match[4] << std::endl; // num 1
        // std::cout << match[5] << std::endl; // num 2

        if (match[1].str() == "do()") {
            // std::cout << "do() enabled\n";
            enabled = true;
        }

        if (match[2].str() == "don't()") {
            // std::cout << "don't() enabled\n";
            enabled = false;
        }

        if (enabled) {
            if (match[4].str() != "" && match[5].str() != "") {
                // std::cout << "num 1: " << match[4].str() << "\n";
                int num1 = stoi(match[4].str());
                int num2 = stoi(match[5].str());
                result += num1 * num2;
            }
        }
    }

    std::cout << "result: " << result << std::endl;
    

    return 0;
}