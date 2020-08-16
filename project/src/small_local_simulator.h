/**
 * @file small_local_simulator.h
 *
 * @copyright Yuqing Qin
 */
#ifndef SRC_SMALL_LOCAL_SIMULATOR_H_
#define SRC_SMALL_LOCAL_SIMULATOR_H_

#include <vector>
#include <string>
#include "src/simulator.h"

/******************************************************************************
 * Class Definitions
 *****************************************************************************/

/**
 * @brief The class for creating regression test
 *
 * Calls to \ref Start method to start the local simulation.
 * \ref Update method can update the bus information.
 */

class smallLocalSimulator : public Simulator {
 public:
  /**
  * @brief Start the local simulator to test other functions work fine.
  *
  */
  bool Start() override;

  /**
  * @brief Update the bus information and to make sure the basic 
  * function works fine.
  *
  */
  bool Update() override;
 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
};

#endif  // SRC_SMALL_LOCAL_SIMULATOR_H_
