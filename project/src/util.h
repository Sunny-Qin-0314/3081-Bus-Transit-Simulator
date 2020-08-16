/**
 * @file util.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

/**
 * @brief The util class is the helper class that used to process the output.
 *
 * \ref processOuput is a static method that used to get the string from the stream
 * and split them into a prefered format. The container with all the informations
 * will be returned as the output. That container will be further used in FileWriter.
 */

class Util{
 public:
    /**
    * @brief Process output in prefered format.
    * 
    * This static function will be used to generate the string container for writing
    * csv files. Process the string from the stream and split the string
    * into prefered format. Add the strings into the container for further
    * using.
    *
    * @param[in] oss output string stream address
    * @param[out] container a container with the processed information that useful 
    * to generate csv files
    */
    static std::vector<std::string> processOutput(std::ostringstream&);
};

#endif  // SRC_UTIL_H_
