/**
 * @file file_writer.h
 *
 * @copyright Yuqing Qin, All rights reserved.
 */
#ifndef SRC_FILE_WRITER_H_
#define SRC_FILE_WRITER_H_

#include <string>
#include <iostream>
#include <vector>

/**
 * @brief FileWriter class is used to write the information into the csv file
 *
 * Write the information into the csv file. Information is stored in a vector
 * as one of the input and the csv filename is another input for \ref Write method.
 */

class FileWriter{
 public:
  /**
  * @brief This method is aimed to write the information into the csv file
  * 
  * The information is splitted by comma (csv file deliminator).
  *
  * @param[in] filename csv file name that you want to store information in
  * @param[in] info the container with the information that wants to write into the 
  * csv file.
  */
    void Write(std::string, std::vector<std::string>);
};

#endif  // SRC_FILE_WRITER_H_
