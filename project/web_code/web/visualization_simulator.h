/**
 * @file visualization_simulator.h
 *
 * @Copyright Sunny Qin, All rights reserved.
 */
#ifndef WEB_CODE_WEB_VISUALIZATION_SIMULATOR_H_
#define WEB_CODE_WEB_VISUALIZATION_SIMULATOR_H_

/******************************************************************************
 * Includes
 *****************************************************************************/
#include <vector>
#include <list>
#include <string>


#include "web_code/web/web_interface.h"
#include "src/config_manager.h"
#include "web_code/web/BusWebObserver.h"
#include "web_code/web/StopWebObserver.h"
#include "src/bus_factory.h"
#include "src/IBus.h"
#include "src/file_writer_manager.h"
#include "src/file_writer.h"
#include "src/util.h"



class Route;
class Bus;
class Stop;

/******************************************************************************
 * Class Definitions
 *****************************************************************************/

/**
 * @brief The class for visualize simulator
 *
 * Implement all the button function with backend logics
 */

class VisualizationSimulator {
 public:
        VisualizationSimulator(WebInterface*, ConfigManager*);
        ~VisualizationSimulator();

        void Start(const std::vector<int>&, const int&);
        void Update();
       /**
       * @brief Pause button 
       *
       * This function will be used to pause function. 
       * When click on pause, the simulation will be paused, when click again,
       * the simulation will resume.
       *
       */
        void Pause();

       /**
       * @brief Clear all the listeners
       *
       * This function will be used to set up new observer
       * When click on a subject (a bus or a stop), the simulation will first
       * clear all the listeners by using this method.
       *
       */
        void ClearListeners();

       /**
       * @brief Add new listener to the subject(bus)
       *
       * This function will be used to set up new observer for specified bus
       * When click on a bus, the simulation will first clear the listeners.
       * Then add the observer to the subject by using this method.
       *
       * @param[in] id bus id that can be used to find the specified bus
       * @param[in] busWebObserver the observer that attaches to the bus
       */
        void AddListenerBus(std::string* id,
                            IObserver<BusData*>* busWebObserver);

       /**
       * @brief Add new listener to the subject(stop).
       *
       * This function will be used to set up new observer for specified stop
       * When choose a stop from dropdown list, 
       * the simulation will first clear the listeners.
       * Then add the observer to the subject by using this method.
       *
       * @param[in] id stop id that can be used to find the specified stop
       * @param[in] stopWebObserver the observer that attaches to the stop
       */
        void AddListenerStop(std::string* id,
                            IObserver<StopData*>* stopWebObserver);

 private:
        WebInterface* webInterface_;
        ConfigManager* configManager_;
        std::vector<int> busStartTimings_;
        std::vector<int> timeSinceLastBus_;
        int numTimeSteps_;
        int simulationTimeElapsed_;

        std::vector<Route *> prototypeRoutes_;
        std::vector<IBus *> busses_;
        BusFactory * busfactory;
        bool pause = false;
        bool running = false;
        int busId = 1000;
        std::string bus_stats_file_name = "BusData.csv";
};

#endif  // WEB_CODE_WEB_VISUALIZATION_SIMULATOR_H_
