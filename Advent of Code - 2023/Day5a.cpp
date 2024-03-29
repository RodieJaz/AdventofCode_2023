#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <limits>
#include <utility>

using namespace std;

struct MapRange {
    uint64_t destinationStart;
    uint64_t sourceStart;
    uint64_t rangeLength;
};

using Map = vector<MapRange>;
using Maps = vector<Map>;

vector<string> readFile(const string& fileName) {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        throw runtime_error("Cannot open file: " + fileName);
    }

    vector<string> lines;
    string line;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();
    return lines;
}

uint64_t applyMappings(uint64_t seed, const Maps& maps) {
    for (const auto& map : maps) {
        for (const auto& range : map) {
            if (seed >= range.sourceStart && seed < range.sourceStart + range.rangeLength) {
                seed = range.destinationStart + (seed - range.sourceStart);
                break;
            }
        }
    }
    return seed;
}

int main() {
    try {
        const string fileName = "Day5.txt";
        vector<string> lines = readFile(fileName);

        vector<uint64_t> seeds;
        stringstream ss(lines[0].substr(6)); // Assumes "seeds: " prefix
        uint64_t seed;
        while (ss >> seed) {
            seeds.push_back(seed);
        }

        Maps maps;
        Map currentMap;
        for (size_t i = 1; i < lines.size(); ++i) {
            if (lines[i].empty()) {
                maps.push_back(std::move(currentMap));
                currentMap.clear();
            } else {
                uint64_t d, s, l;
                stringstream iss(lines[i]);
                iss >> d >> s >> l;
                currentMap.emplace_back(MapRange{d, s, l});
            }
        }
        if (!currentMap.empty()) {
            maps.push_back(std::move(currentMap));
        }

        uint64_t minLocation = numeric_limits<uint64_t>::max();
        for (const auto& s : seeds) {
            uint64_t finalLocation = applyMappings(s, maps);
            minLocation = min(minLocation, finalLocation);
        }

        cout << "Minimum Location Number: " << minLocation << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
