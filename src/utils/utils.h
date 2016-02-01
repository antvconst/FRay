#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str, const char& delim) {
    std::vector<std::string> tokens;
    int n = str.length();
    char prev = delim;
    std::string word = "";

    for (int i=0; i<n; ++i) {
        char cur = str[i];
        if (cur == delim) {
            if (prev == delim)
                continue;
            else {
                prev = delim;
                tokens.push_back(word);
                word.clear();
            }
        }
        else {
            word.push_back(cur);
            prev = cur;
        }
    }

    return tokens;
}


#endif // UTILS_H

