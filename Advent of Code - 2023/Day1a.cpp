#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream file("Day1.txt");
    if (!file.is_open()) {
        cerr << "Unable to open file!" << endl;
        return 1;
    }
    
    int totalCalibrationSum = 0;
    string line;
    
    while (getline(file, line)) {

        size_t first_digit_pos = line.find_first_of("0123456789");
        if (first_digit_pos == string::npos)
            continue;
        
        size_t last_digit_pos = line.find_last_of("0123456789");
        if (last_digit_pos == string::npos)
            continue;
        
        int first_digit = line[first_digit_pos];
        int last_digit = line[last_digit_pos];
        
        int calibration_value = (first_digit - '0') * 10 + (last_digit - '0');
        totalCalibrationSum += calibration_value;
    }
    file.close();
    cout << "Sum of all calibration values: " << totalCalibrationSum << endl;
    
    return 0;
}
