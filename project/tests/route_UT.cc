/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

// #include "../src/passenger_loader.h"
// #include "../src/bus.h"
// #include "../src/passenger.h"
#include "../src/stop.h"
#include "../src/data_structs.h"
#include "../src/passenger_generator.h"
#include "../src/random_passenger_generator.h"
#include "../src/route.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class RouteTests : public ::testing::Test {
protected:
  Route *route;
  Stop ** stops;
  double * distances;
  std::list<double> probs_g;
  std::list<Stop *> stops_g;
  RandomPassengerGenerator * generator;
  int num_stops = 3;

  virtual void SetUp() {
    stops = new Stop*[3];
    stops[0] = new Stop(1);
    stops[1] = new Stop(2, 45.12);
    stops[2] = new Stop(3, 45.12, 45.11);

    for (int i = 0; i < num_stops; i++) {
      stops_g.push_back(stops[i]);
    }

    for (int i = 0; i < num_stops; i++) {
      probs_g.push_back(0.5);
    }

    distances = new double[2];
    distances[0] = 1;
    distances[1] = 100;

    generator =  new RandomPassengerGenerator(probs_g, stops_g);

    route = new Route("r1", stops, distances, num_stops, generator);
  }

  virtual void TearDown() {
    for (int i = 0; i < num_stops; i++) {
      delete stops[i];
      stops[i] = NULL;
    }
    delete []stops;
    delete []distances;
    // delete generator;
    delete route;

    stops = NULL;
    distances = NULL;
    generator = NULL;
    route = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
 TEST_F(RouteTests, Constructor) {
   EXPECT_EQ(route -> GetName(), "r1");
   EXPECT_EQ(route -> GetTotalRouteDistance(), 101);

   Stop * dest = route -> GetDestinationStop();
   EXPECT_EQ(dest -> GetId(), 1);
   EXPECT_EQ(dest -> GetLongitude(), 44.973723);
   EXPECT_EQ(dest -> GetLatitude(), -93.235365);

   route -> ToNextStop();
   EXPECT_EQ(route -> GetNextStopDistance(), 1);
   Stop * dest1 = route -> GetDestinationStop();
   EXPECT_EQ(dest1 -> GetId(), 2);
   EXPECT_EQ(dest1 -> GetLongitude(), 45.12);
   EXPECT_EQ(dest1 -> GetLatitude(), -93.235365);


   route -> ToNextStop();
   EXPECT_EQ(route -> GetNextStopDistance(), 100);
   Stop * dest2 = route -> GetDestinationStop();
   EXPECT_EQ(dest2 -> GetId(), 3);
   EXPECT_EQ(dest2 -> GetLongitude(), 45.12);
   EXPECT_EQ(dest2 -> GetLatitude(), 45.11);

   std::string exp_output1 = "Num stops: 3";
   testing::internal::CaptureStdout();
   route -> Report(std::cout);
   std::string output1 = testing::internal::GetCapturedStdout();
   int p1 = output1.find(exp_output1);
   EXPECT_GE(p1,0);


 };

 TEST_F(RouteTests, IsAtEnd) {
   EXPECT_EQ(route -> IsAtEnd(), false);
   route -> ToNextStop();
   route -> ToNextStop();
   EXPECT_EQ(route -> IsAtEnd(), false);
   route -> ToNextStop();
   EXPECT_EQ(route -> IsAtEnd(), true);
 };
