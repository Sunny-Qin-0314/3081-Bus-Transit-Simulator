/**
 * @file IObserver.h
 *
 * @copyright Yuqing Qin, All rights reserved.
 */
#ifndef SRC_IOBSERVER_H_
#define SRC_IOBSERVER_H_

#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <string>

#include "src/data_structs.h"

/******************************************************************************
 * Class Definitions
 *****************************************************************************/

/**
 * @brief The abstract class for creating the observer in the observer pattern
 *
 * \ref Notify is a pure virtual method, which will be overrided by 
 * \ref BusWebObserver. Implement the IObserver using template. It can be used 
 * for different type of data.
 */
// The Observer (Abstract (and uninstantiable)) Interface Class
template <typename T>
class IObserver{
 public:
    /**
    * @brief Print out the information updated to observer in web page
    * This function will be used for \ref VisualizationSimulator to show the 
    * updated information.
    *
    * @param[in] info updated BusData information
    *
    */
    virtual void Notify(T info) = 0;
};
#endif  // SRC_IOBSERVER_H_
