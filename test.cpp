#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    std::map<char, int> frequency;
    std::map<char, double> p;
    std::map<char, double> low;
    std::map<char, double> high;

    std::string line;
    std::getline(std::cin, line);
    size_t pos;
    while ((pos = line.find(' ')) != std::string::npos) {
        line.erase(pos, 1);
    }

    for (char c : line) {
        frequency[c]++;
    }
    int n = line.length();
    for (auto &pair : frequency) {
        p[pair.first] = (double)pair.second / n;
    }
    double curr = 0.0;
    for (auto &pair : p) {
        char sym = pair.first;
        double prob = pair.second;
        low[sym] = curr;
        high[sym] = curr + prob;
        curr = high[sym];
    }
    double L = 0.0;
    double R = 1.0;
    for (char c : line) {
        double range = R - L;
        double newR = L + range * high[c];
        double newL = L + range * low[c];
        L = newL;
        R = newR;
    }
    double code = (L + R) / 2;
    std::cout << code << "\n";

    std::string binary;
    while (code > 0 && binary.length() < 32) {
        code *= 2;
        if (code >= 1) {
            binary += '1';
            code -= 1;
        }
        else {
            binary += '0';
        }
    }
    std::cout << binary << '\n';
    for (auto &pair : low) {
        double l = pair.second;
        double h = high[pair.first];
        std::cout << pair.first << ' ' << l << ' ' << h << '\n';
    }
}
