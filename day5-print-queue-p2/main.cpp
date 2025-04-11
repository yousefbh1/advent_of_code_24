#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

void construct_rules(std::unordered_map<int, std::vector<int>>& graph, std::ifstream& file) {
    std::string line;
    while (std::getline(file, line) && !line.empty()) {
        int from, to;
        char sep;
        std::stringstream ss(line);
        ss >> from >> sep >> to;
        graph[from].push_back(to);
    }
}

bool is_valid_order(const std::vector<int>& update, const std::unordered_map<int, std::vector<int>>& rules) {
    std::unordered_map<int, int> position;
    for (int i = 0; i < update.size(); ++i) {
        position[update[i]] = i;
    }

    for (const auto& [from, to_list] : rules) {
        if (position.count(from)) {
            for (int to : to_list) {
                if (position.count(to) && position[from] > position[to]) {
                    return false;
                }
            }
        }
    }

    return true;
}

// Topological sort only using the subset of nodes in `update`
std::vector<int> topological_sort_subset(const std::vector<int>& update, const std::unordered_map<int, std::vector<int>>& full_graph) {
    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_map<int, int> indegree;
    std::unordered_set<int> nodes(update.begin(), update.end());

    // Build subgraph from full graph based on nodes in this update
    for (int u : update) {
        if (full_graph.count(u)) {
            for (int v : full_graph.at(u)) {
                if (nodes.count(v)) {
                    graph[u].push_back(v);
                    indegree[v]++;
                }
            }
        }
        if (!indegree.count(u)) indegree[u] = 0;
    }

    std::queue<int> q;
    for (int u : update) {
        if (indegree[u] == 0) {
            q.push(u);
        }
    }

    std::vector<int> result;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        result.push_back(u);
        for (int v : graph[u]) {
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    // If cycle exists, result won't have all nodes
    if (result.size() != update.size()) return {};

    return result;
}

int main(int argc, char* argv[]) {

    std::ifstream file(argv[1]);

    std::unordered_map<int, std::vector<int>> rules;
    construct_rules(rules, file);

    std::string line;
    int total = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<int> update;

        while (std::getline(ss, token, ',')) {
            update.push_back(std::stoi(token));
        }

        if (update.empty()) continue;

        if (!is_valid_order(update, rules)) {
            std::vector<int> fixed = topological_sort_subset(update, rules);
            if (!fixed.empty()) {
                int mid = fixed[fixed.size() / 2];
                total += mid;
            } else {
                std::cerr << "Warning: Cycle detected, could not sort update: " << line << "\n";
            }
        }
    }

    std::cout << "Part 2 result: " << total << "\n";
    return 0;
}
