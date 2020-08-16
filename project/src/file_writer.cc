/**
 * @file file_writer.cc
 *
 * @copyright Yuqing Qin, All rights reserved.
 */
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "src/file_writer.h"

void FileWriter::Write(std::string file, std::vector<std::string> container) {
    std::fstream myFile;
    // create a file or open existed file
    myFile.open(file, std::ios::out | std::ios::app);

    for (int i = 0; i < container.size(); ++i) {
        myFile << container.at(i) << ",";  // add deliminator
    }
    myFile << "\n";  // new line after each information
    myFile.close();
}
