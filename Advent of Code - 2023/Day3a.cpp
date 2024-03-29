#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

bool isSymbol(const vector<string>& lines, int i, int j) {
    return i >= 0 && i < lines.size() && j >= 0 && j < lines[i].size() && lines[i][j] != '.' && !isdigit(lines[i][j]);
}

int main() {
    ifstream fin("Day3.txt");
    vector<string> lines;
    string line;

    if (!fin.is_open()) {
        cerr << "Unable to open file";
        return 1;
    }

    while (getline(fin, line)) {
        lines.push_back(line);
    }
    fin.close();

    int n = static_cast<int>(lines.size());
    int m = lines.empty() ? 0 : static_cast<int>(lines[0].size());

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m;) {
            if (!isdigit(lines[i][j])) {
                ++j;
                continue;
            }
            
            int start = j;
            string num;
            while (j < m && isdigit(lines[i][j])) {
                num += lines[i][j++];
            }

            int number;
            try {
                number = stoi(num);
            } catch (const std::invalid_argument& e) {
                cerr << "Invalid number found: " << num << endl;
                return 2;
            }

            bool symbolFound = isSymbol(lines, i, start - 1) || isSymbol(lines, i, j);
            for (int k = start - 1; !symbolFound && k <= j; ++k) {
                if (isSymbol(lines, i - 1, k) || isSymbol(lines, i + 1, k)) {
                    symbolFound = true;
                }
            }
            if (symbolFound) {
                ans += number;
            }
        }
    }
    cout << "Total sum: " << ans << endl;
    return 0;
}
