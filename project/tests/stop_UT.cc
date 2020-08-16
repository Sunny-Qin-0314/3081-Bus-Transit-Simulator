/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>

#include <iostream>
#include <string>
#include <list>
#include <string>

// #include "../src/passenger_loader.h"
#include "../src/bus.h"
#include "../src/passenger.h"
#include "../src/stop.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class StopTests : public ::testing::Test {
protected:
  Stop * stop, *stop1,*stop2;

  virtual void SetUp() {
    stop = new Stop(1);
    stop1 = new Stop(2, 45.12);
    stop2 = new Stop(3, 45.12, 45.11);

  }

  virtual void TearDown() {
    delete stop;
    delete stop1;
    delete stop2;

    stop = NULL;
    stop1 = NULL;
    stop2 = NULL;
  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
 TEST_F(StopTests, Constructor) {
   EXPECT_EQ(stop -> GetId(), 1);
   EXPECT_EQ(stop -> GetLongitude(), 44.973723);
   EXPECT_EQ(stop -> GetLatitude(), -93.235365);

   EXPECT_EQ(stop1 -> GetId(), 2);
   EXPECT_EQ(stop1 -> GetLongitude(), 45.12);
   EXPECT_EQ(stop1 -> GetLatitude(), -93.235365);

   EXPECT_EQ(stop2 -> GetId(), 3);
   EXPECT_EQ(stop2 -> GetLongitude(), 45.12);
   EXPECT_EQ(stop2 -> GetLatitude(), 45.11);


 };
