/**
 * @file bus_factory.h
 *
 * @copyright Sunny Qin
 */
#ifndef SRC_BUS_FACTORY_H_
#define SRC_BUS_FACTORY_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <string>

#include "src/bus.h"

/******************************************************************************
 * Class Definitions
 *****************************************************************************/

/**
 * @brief The class for generating a small sized bus
 *
 * Calls to \ref SmallBus constructor to get a new instance of a small bus.
 *  The size for a small bus is 30. The SmallBus is inherited from Bus class.
 *  And it overrides the \ref Report function in Bus. In its \ref Report 
 *  function, it prints its type: small to the output stream as well as the 
 *  original information of a bus.
 */
class SmallBus : public Bus {
 public:
  /**
  * @brief Constructor for small bus with capacity of 30
  * This function will be used for \ref BusFactory to generate new small bus
  *
  * @param[in] name name of the new bus
  * @param[in] out outgoing route for this bus
  * @param[in] in incoming route for this bus
  * @param[in] speed speed of the bus, default is 1
  *
  */
  // use Bus constructor to generate a small bus with 30 capacity
    SmallBus(std::string name, Route * out, Route * in, double speed):
                    Bus(name, out, in, 30, speed) {}
    /**
    * @brief Report the bus basic information and bus type: Small
    * This function will be used for \ref VisualizationSimulator to report bus type
    *
    * @param[in] out output stream
    *
    */
    void Report(std::ostream&) override;
};

/**
 * @brief The class for generating a regular sized bus
 *
 * Calls to \ref RegularBus constructor to get a new instance of a regular bus.
 *  The size for a regular bus is 60. The RegularBus is inherited from Bus class.
 *  And it overrides the \ref Report function in Bus. In its \ref Report 
 *  function, it prints its type: regular to the output stream as well as the 
 *  original information of a bus.
 */
class RegularBus : public Bus {
 public:
  /**
  * @brief Constructor for regular bus with capacity of 60
  * This function will be used for \ref BusFactory to generate new regular bus
  *
  * @param[in] name name of the new bus
  * @param[in] out outgoing route
  * @param[in] in incoming route
  * @param[in] speed speed of the bus, default is 1
  *
  */
  // use Bus constructor to generate a regular bus with 60 capacity
    RegularBus(std::string name, Route * out, Route * in, double speed):
                    Bus(name, out, in, 60, speed) {}
    /**
    * @brief Report the bus basic information and bus type: Regular
    * This function will be used for \ref VisualizationSimulator to report bus type
    *
    * @param[in] out output stream
    *
    */
    void Report(std::ostream&) override;
};

/**
 * @brief The class for generating a large sized bus
 *
 * Calls to \ref LargeBus constructor to get a new instance of a large bus.
 *  The size for a large bus is 90. The LargeBus is inherited from Bus class.
 *  And it overrides the \ref Report function in Bus. In the \ref Report 
 *  function, it prints its type: large to the output stream as well as the 
 *  original information of a bus.
 */
class LargeBus : public Bus {
 public:
  /**
  * @brief Constructor for large bus with capacity of 90
  * This function will be used for \ref BusFactory to generate new large bus
  *
  * @param[in] name name of the new bus
  * @param[in] out outgoing route
  * @param[in] in incoming route
  * @param[in] speed speed of the bus, default is 1
  *
  */
  // use Bus constructor to generate a large bus with 90 capacity
    LargeBus(std::string name, Route * out, Route * in, double speed):
                    Bus(name, out, in, 90, speed) {}
  /**
  * @brief Report the bus basic information and bus type: Large
  * This function will be used for \ref VisualizationSimulator to report bus type
  *
  * @param[in] out output stream
  *
  */
    void Report(std::ostream&) override;
};


/**
 * @brief The class for generating new buses through factory
 *
 * Calls to \ref Generate function to get a new instance of bus.
 *  The size for the new bus depends on the type parameter in \ref Generate. 
 *  Currently, the type is chosen from 1, 2, and 3, which corresponds to small,
 *  regular, and large. 
 */
class BusFactory {
  static int state1;
  static int state2;
  static int state3;

 public:
  /**
  * @brief Generation of a bus for given type: 1(small), 2(regular), 3(large)
  *
  * This function will be used for strategy implementation purposes.
  *
  * @param[in] name name of the new bus
  * @param[in] out outgoing route
  * @param[in] in incoming route
  * @param[in] type type of generated bus, chosen from 1(small), 2(regular), 3(large)
  * @param[in] speed speed of the bus, default is 1
  *
  * @return Bus object with different size.
  */
  static Bus * Generate(std::string, Route *, Route *, int, double);

  /**
  * @brief Generation of a bus based on a repeat sequence (small regular...)
  * Keep tracking the state, when state equals 0, then generate small bus,
  * when state equals 1, then generate regular bus. This function will be 
  * used for simulation purposes.                                                                       
  *
  * @param[in] name name of the new bus
  * @param[in] out outgoing route
  * @param[in] in incoming route
  * @param[in] speed speed of the bus, default is 1
  *
  * @return Bus object with different size.
  */
  Bus * Strategy1(std::string, Route *, Route *, double);

  /**
  * @brief Generation of a bus based on a repeat sequence (regular large....)
  * Keep tracking the state, when state equals 0, then generate regular bus,
  * when state equals 1, then generate large bus. This function will be 
  * used for simulation purposes.                                                                       
  *
  * @param[in] name name of the new bus
  * @param[in] out outgoing route
  * @param[in] in incoming route
  * @param[in] speed speed of the bus, default is 1
  *
  * @return Bus object with different size.
  */
  Bus * Strategy2(std::string, Route *, Route *, double);

  /**
  * @brief Generation of a bus based on a repeat sequence (small regular large...)
  * Keep tracking the state, when state equals 0, then generate small bus,
  * when state equals 1, then generate regular bus. When state equals to 2, then
  * generate large bus. This function will be used for simulation purposes.                                                                       
  *
  * @param[in] name name of the new bus
  * @param[in] out outgoing route
  * @param[in] in incoming route
  * @param[in] speed speed of the bus, default is 1
  *
  * @return Bus object with different size.
  */
  Bus * Strategy3(std::string, Route *, Route *, double);
};
#endif  // SRC_BUS_FACTORY_H_
