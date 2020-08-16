/**
 * @file IBus.h
 *
 * @copyright Yuqing Qin, All rights reserved.
 */
#ifndef SRC_IBUS_H_
#define SRC_IBUS_H_

#include <list>

#include "src/data_structs.h"
#include "src/IObservable.h"
#include "src/route.h"
class Route;

/**
* @brief Bus Interface
*
* This class is the interface class for bus object. It contains most of
* the methods in Bus class. All the methods in this interface is pure virtual.
*
*/
class IBus : public IObservable<BusData*>{
 public:
  /**
  * @brief pure virtual method UpdateBusData
  */
  virtual void UpdateBusData() = 0;

  /**
  * @brief pure virtual method GetBusData
  */
  virtual BusData GetBusData() const = 0;

  /**
  * @brief pure virtual method GetNumPassengers
  */
  virtual size_t GetNumPassengers() const = 0;

  /**
  * @brief pure virtual method OutRouteComplete
  */
  virtual bool OutRouteComplete() = 0;

  /**
  * @brief pure virtual method Report
  */
  virtual void Report(std::ostream&) = 0;

  /**
  * @brief pure virtual method IsTripComplete
  */
  virtual bool IsTripComplete() = 0;

  /**
  * @brief pure virtual method Move
  */
  virtual bool Move() = 0;

  /**
  * @brief pure virtual method Update
  */
  virtual void Update() = 0;
};

#endif  // SRC_IBUS_H_
