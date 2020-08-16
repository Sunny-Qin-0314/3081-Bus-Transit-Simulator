/**
 * @file util.cc
 *
 * @copyright Yuqing Qin All rights reserved.
 */
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "src/util.h"

std::vector<std::string> Util::processOutput(std::ostringstream& oss) {
    // stringfy the stream
    std::string s = oss.str();
    // replace the newline charactor with space charactor
    std::replace(s.begin(), s.end(), '\n', ' ');

    std::vector<std::string> result;
    size_t pos = 0;
    std::string token;

    while ((pos = s.find(" ")) != std::string::npos) {
        // split string by space and push into a vector
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + 1);
    }
    result.push_back(s);
    return result;
}
