/**
 * @file visualization_simulator.cc
 *
 * @Copyright Sunny Qin, All rights reserved.
 */
#include <random>
#include <list>
#include <ctime>
#include <string>

#include "web_code/web/visualization_simulator.h"
#include "src/bus_factory.h"
#include "src/bus.h"
#include "src/IBus.h"
#include "src/bus_decorator.h"
#include "src/stop.h"
#include "src/route.h"
#include "src/IObservable.h"
#include "src/file_writer_manager.h"
#include "src/file_writer.h"
#include "src/util.h"


VisualizationSimulator::VisualizationSimulator(WebInterface* webI,
                                                ConfigManager* configM) {
    webInterface_ = webI;
    configManager_ = configM;
}

VisualizationSimulator::~VisualizationSimulator() {
}

void VisualizationSimulator::Start(const std::vector<int>& busStartTimings,
                                    const int& numTimeSteps) {
    busStartTimings_ = busStartTimings;
    numTimeSteps_ = numTimeSteps;

    timeSinceLastBus_.resize(busStartTimings_.size());
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        timeSinceLastBus_[i] = 0;
    }

    simulationTimeElapsed_ = 0;

    prototypeRoutes_ = configManager_->GetRoutes();
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Report(std::cout);

        prototypeRoutes_[i]->UpdateRouteData();
        webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());
    }
    // when click on Start, the simulation is running.
    running = true;
}
void VisualizationSimulator::Pause() {
  // if the simulation is running and is not paused
  // then the simulation should be paused
  // if the simulation is running and has already been paused
  // then the simulation should resume
  if (running == true && pause == false) {
    pause = true;
  } else if (running == true && pause == true) {
    pause = false;
  }
}

void VisualizationSimulator::Update() {
  // if not click on Pause, then update the simulation
  if (pause == false) {
    simulationTimeElapsed_++;

    std::cout << "~~~~~~~~~~ The time is now " << simulationTimeElapsed_;
    std::cout << "~~~~~~~~~~" << std::endl;

    std::cout << "~~~~~~~~~~ Generating new busses if needed ";
    std::cout << "~~~~~~~~~~" << std::endl;

    // Check if we need to generate new busses
    for (int i = 0; i < static_cast<int>(timeSinceLastBus_.size()); i++) {
        // Check if we need to make a new bus
        if (0 >= timeSinceLastBus_[i]) {
            Route * outbound = prototypeRoutes_[2 * i];
            Route * inbound = prototypeRoutes_[2 * i + 1];
            // std::cout << "test";
            // std::random_device dev1;
            // std::mt19937 rng(dev1());
            // std::uniform_int_distribution<std::mt19937::result_type>
            //   dist1(1, 3);
            // int type = dist1(rng);
            // busses_.push_back(BusFactory::Generate(std::to_string(busId),
            //                outbound->Clone(), inbound->Clone(),type, 1));
            busfactory = new BusFactory();
            time_t rawtime;
            struct tm * ptm;
            time(&rawtime);
            ptm = localtime(&rawtime);
            int hour = ptm->tm_hour;
            std::cout << hour;
            if (hour >= 6 && hour < 8) {
              IBus* new_b = busfactory -> Strategy1(std::to_string(busId),
                                  outbound->Clone(), inbound->Clone(), 1);
              IBus* bus_d = new BusDecorator(new_b);
              busses_.push_back(bus_d);
            } else if (hour >=8 && hour < 15) {
              IBus * new_b = busfactory -> Strategy2(std::to_string(busId),
                                  outbound->Clone(), inbound->Clone(), 1);
              IBus* bus_d = new BusDecorator(new_b);
              busses_.push_back(bus_d);
            } else if (hour >= 15 && hour < 20) {
              IBus * new_b = busfactory -> Strategy3(std::to_string(busId),
                                  outbound->Clone(), inbound->Clone(), 1);
              IBus* bus_d = new BusDecorator(new_b);
              busses_.push_back(bus_d);
            } else {
              IBus* new_b = BusFactory::Generate(std::to_string(busId),
                                  outbound->Clone(), inbound->Clone(), 1, 1);
              IBus* bus_d = new BusDecorator(new_b);
              busses_.push_back(bus_d);
            }
            busId++;

            timeSinceLastBus_[i] = busStartTimings_[i];
        } else {
            timeSinceLastBus_[i]--;
        }
    }

    std::cout << "~~~~~~~~~ Updating busses ";
    std::cout << "~~~~~~~~~" << std::endl;

    std::ostringstream bus_data_oss;
    // // check if finish simulation
    // if (simulationTimeElapsed_ == numTimeSteps_) {
    //   for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
    //       // write the report information into string stream
    //         busses_[i] -> Report(bus_data_oss);
    //         // process the output
    //         std::vector<std::string> bus_data =
    //                       Util::processOutput(bus_data_oss);
    //         FileWriter fw = FileWriterManager::GetInstance();
    //         // write into csv file
    //         fw.Write(bus_stats_file_name, bus_data);

    //         // bus_data_oss.flush();
    //         // empty the stream
    //         bus_data_oss.str("");
    //   }
    // }
    // Update busses
    for (int i = static_cast<int>(busses_.size()) - 1; i >= 0; i--) {
        busses_[i]->Update();

        if (busses_[i]->IsTripComplete()) {
            webInterface_->UpdateBus(busses_[i]->GetBusData(), true);
            // write the information when the bus's trip completes
            busses_[i] -> Report(bus_data_oss);
            std::vector<std::string> bus_data =
                      Util::processOutput(bus_data_oss);
            FileWriter fw = FileWriterManager::GetInstance();
            fw.Write(bus_stats_file_name, bus_data);

            // bus_data_oss.flush();
            bus_data_oss.str("");
            busses_.erase(busses_.begin() + i);
            continue;
        }

        webInterface_->UpdateBus(busses_[i]->GetBusData());

        busses_[i]->Report(std::cout);
    }

    std::cout << "~~~~~~~~~ Updating routes ";
    std::cout << "~~~~~~~~~" << std::endl;
    // Update routes
    for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
        prototypeRoutes_[i]->Update();

        webInterface_->UpdateRoute(prototypeRoutes_[i]->GetRouteData());

        prototypeRoutes_[i]->Report(std::cout);
    }
  }
}

void VisualizationSimulator::ClearListeners() {
  // clear all the observers for each bus
  // even though only one observer in our version
  for (int i = 0; i < static_cast<int>(busses_.size()); i++) {
    busses_[i] -> ClearObservers();
  }
  // clear all the observers for each stop
  for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
    std::list<Stop *> stops_ = prototypeRoutes_[i] -> GetStops();
    for (std::list<Stop *>::iterator it=stops_.begin();
                                    it != stops_.end(); ++it) {
      (*it) -> ClearObservers();
    }
  }
}

void VisualizationSimulator::AddListenerBus(std::string* id,
                                    IObserver<BusData*>* busWebObserver) {
  for (int i = 0; i < static_cast<int>(busses_.size()); i++) {
    // add the observer to the specified bus
    // so first find the bus with the id
    BusData busdata = busses_[i] -> GetBusData();
    if ((*id) == busdata.id) {
      busses_[i] -> RegisterObserver(busWebObserver);
    }
  }
}

void VisualizationSimulator::AddListenerStop(std::string* id,
                        IObserver<StopData*>* stopWebObserver) {
  for (int i = 0; i < static_cast<int>(prototypeRoutes_.size()); i++) {
    // get the stop list for each route
    std::list<Stop *> stops_ = prototypeRoutes_[i] -> GetStops();
    for (std::list<Stop*>::iterator it=stops_.begin();
                                    it != stops_.end(); ++it) {
      // register observer for specific stop
      int id_ = (*it) -> GetId();
      std::string stopid = static_cast<std::ostringstream*>(
                                    &(std::ostringstream() << id_))->str();
      if ((*id) == stopid) {
        (*it) -> RegisterObserver(stopWebObserver);
      }
    }
  }
}
