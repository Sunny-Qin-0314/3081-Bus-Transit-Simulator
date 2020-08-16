/**
 * @file passenger_unloader.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "src/passenger_unloader.h"
#include "src/file_writer_manager.h"
#include "src/file_writer.h"
#include "src/util.h"

int PassengerUnloader::UnloadPassengers(std::list<Passenger *> * passengers,
                                        Stop * current_stop) {
  // TODO(wendt): may need to do end-of-life here
  // instead of in Passenger or Simulator
  int passengers_unloaded = 0;
  std::ostringstream pass_data_oss;

  for (std::list<Passenger *>::iterator it = (*passengers).begin();
      it != (*passengers).end(); it++) {
    if ((*it)->GetDestination() == current_stop->GetId()) {
      // could be used to inform scheduler of end-of-life?
      // This could be a destructor issue as well.
      // *it->FinalUpdate();
      (*it) -> Report(pass_data_oss);
      std::vector<std::string> pass_data = Util::processOutput(pass_data_oss);
      FileWriter fw = FileWriterManager::GetInstance();
      fw.Write(passenger_file_name, pass_data);

      it = (*passengers).erase(it);
      pass_data_oss.str("");
      // getting seg faults, probably due to reference deleted objects
      // here
      it--;
      passengers_unloaded++;
    }
  }
  return passengers_unloaded;
}
