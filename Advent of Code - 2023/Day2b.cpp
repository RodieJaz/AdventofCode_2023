#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map> 
#include <algorithm>
#include <cctype>

using namespace std;

struct CubeCounts {
    int red = 0;
    int green = 0;
    int blue = 0;
};

string rtrim(const string& str) {
    size_t end = str.find_last_not_of(", ");
    return (end == string::npos) ? "" : str.substr(0, end + 1);
}

int computePower(const CubeCounts& counts) {
    return counts.red * counts.green * counts.blue;
}

CubeCounts processGame(const string& gameLine) {
    stringstream ss(gameLine);
    string buffer;
    CubeCounts gameMaxCounts;
    getline(ss, buffer, ':');

    unordered_map<string, int> colorCounts;

    while (getline(ss, buffer, ';')) {
        stringstream part(buffer);
        string color;
        int count;
        colorCounts.clear();

        while (part >> count >> color) {
            color = rtrim(color);
            colorCounts[color] += count;
        }

        gameMaxCounts.red = max(gameMaxCounts.red, colorCounts["red"]);
        gameMaxCounts.green = max(gameMaxCounts.green, colorCounts["green"]);
        gameMaxCounts.blue = max(gameMaxCounts.blue, colorCounts["blue"]);
    }

    return gameMaxCounts;
}

int main() {
    ifstream file("Day2.txt");
    if (!file) {
        cerr << "Error opening file 'Day2.txt'. Please check the file path and permissions." << endl;
        return -1;
    }

    string line;
    int sumOfPowers = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;
        CubeCounts counts = processGame(line);
        int power = computePower(counts);
        sumOfPowers += power;
        cout << "Power: " << power << endl;
    }

    cout << "Sum of powers: " << sumOfPowers << endl;

    return 0;
}
