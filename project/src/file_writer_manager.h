/**
 * @file file_writer_manager.h
 *
 * @copyright Yuqing Qin, All rights reserved.
 */
#ifndef SRC_FILE_WRITER_MANAGER_H_
#define SRC_FILE_WRITER_MANAGER_H_

#include <string>
#include <iostream>
#include <vector>

#include "src/file_writer.h"

/**
 * @brief FileWriterManager class is used to help manage the FileWriter
 *
 * This is implemented by using singleton pattern. \ref GetInstance method
 * can help generate FileWriter.
 */
class FileWriterManager{
    static FileWriter file_writer;
 public:
   /**
   * @brief Get a FileWriter instance
   * 
   * This method helps get a FileWriter instance to write into csv file
   *
   * @param[out] FileWriter instance
   */
    static FileWriter GetInstance(){return file_writer;}
};

#endif  // SRC_FILE_WRITER_MANAGER_H_
