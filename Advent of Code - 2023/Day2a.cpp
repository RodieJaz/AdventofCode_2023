#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

using namespace std;

const unordered_map<string, int> INITIAL_CUBE_COUNTS = {{"red", 12}, {"green", 13}, {"blue", 14}};

const string RED = "red";
const string GREEN = "green";
const string BLUE = "blue";

unordered_map<string, int> parseCubes(const string& setStr) {
    
    unordered_map<string, int> counts = {{RED, 0}, {GREEN, 0}, {BLUE, 0}};
    stringstream ss(setStr);
    string part;
    while (getline(ss, part, ',')) {
        int count;
        string color;
        stringstream partSS(part);
        if (!(partSS >> count >> color)) {
            cerr << "Error parsing part: " << part << endl;
            continue;
        }
        if (counts.find(color) == counts.end()) {
            cerr << "Unexpected color: " << color << endl;
            continue;
        }
        counts[color] += count;
    }
    return counts;
}

int main() {
    string file_path = "Day2.txt";
    ifstream file(file_path);

    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return 1;
    }

    unordered_map<string, int> available_cubes = INITIAL_CUBE_COUNTS;
    int sum_of_ids = 0;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        int game_id;
        if (!(ss >> token >> game_id)) {
            cerr << "Error parsing line: " << line << endl;
            continue;
        }
        getline(ss, token, ':');

        bool is_game_possible = true;
        while (getline(ss, token, ';')) {
            if (token.empty()) continue;
            auto counts = parseCubes(token.substr(1));
            for (const auto& [color, count] : counts) {
                if (count > available_cubes[color]) {
                    is_game_possible = false;
                    break;
                }
            }
            if (!is_game_possible) break;
        }

        if (is_game_possible) {
            sum_of_ids += game_id;
        }
    }
    cout << "Sum of IDs for possible games: " << sum_of_ids << endl;
    file.close();
    return 0;
}
