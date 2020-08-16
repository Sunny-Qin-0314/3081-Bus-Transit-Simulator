/**
 * @file bus_decorator.h
 *
 * @copyright Yuqing Qin, All rights reserved.
 */
#ifndef SRC_BUS_DECORATOR_H_
#define SRC_BUS_DECORATOR_H_

#include <iostream>
#include <list>
#include <string>

#include "src/data_structs.h"
#include "src/IBus.h"
#include "src/route.h"

/**
 * @brief The class for decorating the bus.
 *
 * The BusDecorator class is inherited from IBus class, it implements all
 * the required methods and set up the color information in the GetBusData
 * method.
 * 
 */
class BusDecorator: public IBus{
 protected:
    IBus* BusToDecorate;

 public:
    /**
    * @brief Constructor for BusDecorator.
    * This function will be used for \ref VisualizationSimulator to 
    * decorate the bus in run time.
    *
    * @param[in] bus IBus type bus
    */
    explicit BusDecorator(IBus* bus): BusToDecorate(bus) {}

    /**
    * @brief Check the trip is complete.
    * This function directly uses Bus's IsTripComplete method
    *
    */
    bool IsTripComplete() override { return BusToDecorate -> IsTripComplete();}

    /**
    * @brief Move the bus.
    * This function directly uses Bus's Move method
    *
    */
    bool Move() override { return BusToDecorate -> Move();}

    /**
    * @brief Update Bus data.
    * This function directly uses Bus's UpdateBusData method
    *
    */
    void UpdateBusData() override { return BusToDecorate -> UpdateBusData();}

    /**
    * @brief Get the total number of passengers.
    * This function directly uses Bus's GetNumPassengers method. It will be used
    * in GetBusData method to set up color.
    *
    */
    size_t GetNumPassengers() const override {
        return BusToDecorate -> GetNumPassengers();}

    /**
    * @brief Report the information of a bus to the stream
    * This function directly uses Bus's Report method
    *
    * @param[in] os output stream
    */
    void Report(std::ostream& os) override {
        return BusToDecorate -> Report(os); }

    /**
    * @brief Check the outgoing route complete
    * This function directly uses Bus's OurRouteComplete method
    *
    */
    bool OutRouteComplete() override {
        return BusToDecorate -> OutRouteComplete(); }

    /**
    * @brief Set up the color and return updated bus data
    * This function first uses Bus's GetBusData method to get the uncolored
    * bus. Then, set up the color information based on the route and 
    * number of passengers on the bus.
    *
    * @param[out] data updated bus data with color information
    */
    BusData GetBusData() const override {
        BusData data = BusToDecorate -> GetBusData();
        int num_p =  static_cast<int>(BusToDecorate -> GetNumPassengers());
        bool route_complete = BusToDecorate -> OutRouteComplete();
        if (route_complete) {
        // start from yellow
            data.color.red = 255;
            data.color.green = 255 - num_p * 15;
        } else {
        // start from red
            data.color.red = 255 - num_p * 15;
        }
        return data;
    }

    /**
    * @brief Update the bus and notify all its obeservers
    * This function uses Move, UpdateBusData, GetBusData and NotifyObservers
    * to set up the colored bus information and notify the observers with the
    * updated bus information.
    */
    void Update() override {
        Move();
        UpdateBusData();
        BusData data = GetBusData();
        NotifyObservers(&data);
    }
};

#endif  // SRC_BUS_DECORATOR_H_
