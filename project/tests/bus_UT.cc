/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

#include "../src/passenger_loader.h"
#include "../src/passenger_unloader.h"
#include "../src/bus.h"
#include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/data_structs.h"
#include "../src/passenger_generator.h"
#include "../src/random_passenger_generator.h"
#include "../src/route.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class BusTests : public ::testing::Test {
protected:
  Route *in, *out;
  Stop ** stops_in, **stops_out;
  double * distances_in, *distances_out;
  std::list<double> probs_gin, probs_gout;
  std::list<Stop *> stops_gin, stops_gout;
  RandomPassengerGenerator * generator_in, *generator_out;
  int num_stops = 3;
  Bus *bus, *bus2;
  Passenger * p, *p1;

  virtual void SetUp() {
    stops_in = new Stop*[3];
    stops_in[0] = new Stop(1);
    stops_in[1] = new Stop(2, 45.12);
    stops_in[2] = new Stop(3, 45.12, 45.11);

    distances_in = new double[2];
    distances_in[0] = 4;
    distances_in[1] = 4;

    for (int i = 0; i < num_stops; i++) {
      stops_gin.push_back(stops_in[i]);
    }
    for (int i = 0; i < num_stops; i++) {
      probs_gin.push_back(1);
    }
    generator_in =  new RandomPassengerGenerator(probs_gin, stops_gin);

    in = new Route("in", stops_in, distances_in, num_stops, generator_in);


    stops_out = new Stop*[3];
    stops_out[0] = new Stop(4, 45.12, 45.11);
    stops_out[1] = new Stop(5, 45.12, 15);
    stops_out[2] = new Stop(6, 10);

    for (int i = 0; i < num_stops; i++) {
      stops_gout.push_back(stops_out[i]);
    }

    for (int i = 0; i < num_stops; i++) {
      probs_gout.push_back(1);
    }

    distances_out = new double[2];
    distances_out[0] = 6;
    distances_out[1] = 4;

    generator_out =  new RandomPassengerGenerator(probs_gout, stops_gout);

    out = new Route("out", stops_out, distances_out, num_stops, generator_out);

    bus = new Bus("bus", out, in);
    bus2 = new Bus("bus2",out, in, 30, 2);

    p = new Passenger(12, "John");
    p1 = new Passenger();
  }

  virtual void TearDown() {
    for (int i = 0; i < num_stops; i++) {
      delete stops_in[i];
      stops_in[i] = NULL;
    }
    delete []stops_in;
    delete []distances_in;
    // delete generator;
    delete in;

    stops_in = NULL;
    distances_in = NULL;
    // generator_in = NULL;
    in = NULL;


    for (int i = 0; i < num_stops; i++) {
      delete stops_out[i];
      stops_out[i] = NULL;
    }
    delete []stops_out;
    delete []distances_out;
    // delete generator;
    delete out;

    stops_out = NULL;
    distances_out = NULL;
    // generator_out = NULL;
    out = NULL;

    delete bus;
    delete bus2;

    bus = NULL;
    bus2 = NULL;

    delete p;
    delete p1;
    p = NULL;
    p1 = NULL;

  }

};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
 TEST_F(BusTests, Constructor) {
   EXPECT_EQ(bus -> GetName(), "bus");
   EXPECT_EQ(bus2 -> GetName(), "bus2");

   EXPECT_EQ(bus -> GetCapacity(), 60);
   EXPECT_EQ(bus2 -> GetCapacity(), 30);

   std::string exp_output1 = "Speed: 1";
   testing::internal::CaptureStdout();
   bus -> Report(std::cout);
   std::string output1 = testing::internal::GetCapturedStdout();
   int p1 = output1.find(exp_output1);
   EXPECT_GE(p1,0);

   std::string exp_output2 = "Speed: 2";
   testing::internal::CaptureStdout();
   bus2 -> Report(std::cout);
   std::string output2 = testing::internal::GetCapturedStdout();
   int p2 = output2.find(exp_output2);
   EXPECT_GE(p2,0);

   std::string exp_output3 = "Distance to next stop: 0";
   testing::internal::CaptureStdout();
   bus2 -> Report(std::cout);
   std::string output3 = testing::internal::GetCapturedStdout();
   int p3 = output3.find(exp_output3);
   EXPECT_GE(p3,0);


   Stop * next = bus -> GetNextStop();
   EXPECT_EQ(next -> GetId(), 4);

   Stop * next4 = bus2 -> GetNextStop();
   EXPECT_EQ(next4 -> GetId(), 4);
   EXPECT_EQ(next4 -> GetLongitude(), 45.12);
   EXPECT_EQ(next4 -> GetLatitude(), 45.11);


 };

 TEST_F(BusTests, IsTripComplete) {
   EXPECT_EQ(bus -> IsTripComplete(), false);

   EXPECT_EQ(out -> IsAtEnd(), false);
   out -> ToNextStop();
   out -> ToNextStop();
   EXPECT_EQ(out -> IsAtEnd(), false);
   out -> ToNextStop();
   EXPECT_EQ(out -> IsAtEnd(), true);

   EXPECT_EQ(bus -> IsTripComplete(), false);

   EXPECT_EQ(in -> IsAtEnd(), false);
   in -> ToNextStop();
   in -> ToNextStop();
   EXPECT_EQ(in -> IsAtEnd(), false);
   in -> ToNextStop();
   EXPECT_EQ(in -> IsAtEnd(), true);

   EXPECT_EQ(bus -> IsTripComplete(), true);


 };

 TEST_F(BusTests, LoadPassengers){

   EXPECT_EQ(bus -> LoadPassenger(p), true);
   EXPECT_EQ(bus -> LoadPassenger(p), true);
   for (int i = 0; i < 29; i++){
     bus2 -> LoadPassenger(p1);
   }
   EXPECT_EQ(bus2 -> LoadPassenger(p), true);
   EXPECT_EQ(bus2 -> LoadPassenger(p), false);

   EXPECT_EQ(bus2 -> LoadPassenger(p), false);

 };

 TEST_F(BusTests, Move){

   EXPECT_EQ(bus2 -> Move(), false);
   bus2 -> UpdateBusData();
   EXPECT_EQ(bus2 -> Move(), true);
   bus2 -> UpdateBusData();

   for (int i = 0; i < 3; i++){
     bus2 -> LoadPassenger(p1);
   }
   EXPECT_EQ(bus2 -> Move(), false);
   bus2 -> UpdateBusData();

   // go to next stop
   EXPECT_EQ(bus2 -> Move(), true);
   bus2 -> UpdateBusData();

   std::string exp_output1 = "Distance to next stop: 2";
   testing::internal::CaptureStdout();
   bus2 -> Report(std::cout);
   std::string output1 = testing::internal::GetCapturedStdout();
   int p1 = output1.find(exp_output1);
   EXPECT_GE(p1,0);

   EXPECT_EQ(bus2 -> Move(), false);
   bus2 -> UpdateBusData();

   std::string exp_output2 = "Distance to next stop: 0";
   testing::internal::CaptureStdout();
   bus2 -> Report(std::cout);
   std::string output2 = testing::internal::GetCapturedStdout();
   int p2 = output2.find(exp_output2);
   EXPECT_GE(p2,0);

   EXPECT_EQ(bus2 -> Move(), false);
   bus2 -> UpdateBusData();
   EXPECT_EQ(bus2 -> Move(), false);
   bus2 -> UpdateBusData();
   EXPECT_EQ(bus2 -> Move(), true);
   bus2 -> UpdateBusData();
   EXPECT_EQ(bus2 -> Move(), false);
   bus2 -> UpdateBusData();


   EXPECT_EQ(bus2 -> Move(), false);
   bus2 -> UpdateBusData();
   std::string exp_output3 = "Distance to next stop: 999";
   testing::internal::CaptureStdout();
   bus2 -> Report(std::cout);
   std::string output3 = testing::internal::GetCapturedStdout();
   int p3 = output3.find(exp_output3);
   EXPECT_GE(p3,0);

 }
