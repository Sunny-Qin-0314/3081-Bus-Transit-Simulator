/*
 * Students: Use this file as a guide to writing your own unit tests.
 * See the project instructions for more information on which classes
 * and methods must be tested.
 */

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
#include "../src/passenger.h"
#include "../src/stop.h"

using namespace std;

/******************************************************
* TEST FEATURE SetUp
*******************************************************/
class PassengerTests : public ::testing::Test {
protected:
  PassengerLoader* pass_loader;
  PassengerUnloader* pass_unloader;
  Passenger *passenger, *passenger1, *passenger2;

  virtual void SetUp() {
    pass_loader = new PassengerLoader();
    pass_unloader = new PassengerUnloader();
  }

  virtual void TearDown() {
    delete pass_loader;
    delete pass_unloader;
    delete passenger;
    delete passenger1;
    delete passenger2;
    passenger = NULL;
    pass_loader = NULL;
    pass_unloader = NULL;
    passenger1 = NULL;
    passenger2 = NULL;

  }
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(PassengerTests, Constructor) {
  passenger = new Passenger();
  EXPECT_EQ(passenger->IsOnBus(), false);
  passenger->GetOnBus();
  EXPECT_EQ(passenger->IsOnBus(), true);
  EXPECT_EQ(passenger->GetDestination(), -1);
  EXPECT_EQ(passenger->GetTotalWait(), 1);
  passenger -> Update();
  EXPECT_EQ(passenger->GetTotalWait(), 2);

  std::string exp_output1 = "Name: Nobody";
  testing::internal::CaptureStdout();
  passenger -> Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  int p1 = output1.find(exp_output1);
  EXPECT_GE(p1,0);



  passenger1 = new Passenger(12);
  EXPECT_EQ(passenger1->IsOnBus(), false);
  passenger1->GetOnBus();
  EXPECT_EQ(passenger1->IsOnBus(), true);

  EXPECT_EQ(passenger1->GetDestination(), 12);
  EXPECT_EQ(passenger1->GetTotalWait(), 1);
  passenger1 -> Update();
  EXPECT_EQ(passenger1->GetTotalWait(), 2);

  std::string exp_output2 = "Name: Nobody";
  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();
  int p2 = output2.find(exp_output1);
  EXPECT_GE(p2,0);


  passenger2 = new Passenger(12, "John");
  EXPECT_EQ(passenger2->IsOnBus(), false);
  passenger2->GetOnBus();
  EXPECT_EQ(passenger2->IsOnBus(), true);
  EXPECT_EQ(passenger2->GetDestination(), 12);
  EXPECT_EQ(passenger2->GetTotalWait(), 1);
  passenger2 -> Update();
  EXPECT_EQ(passenger2->GetTotalWait(), 2);

  std::string exp_output3 = "Name: John";
  testing::internal::CaptureStdout();
  passenger2 -> Report(std::cout);
  std::string output3 = testing::internal::GetCapturedStdout();
  int p3 = output3.find(exp_output3);
  EXPECT_GE(p3,0);


};


TEST_F(PassengerTests, Update) {  // Update method
  passenger1 = new Passenger();
  passenger1 -> Update();
  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  int p1 = output1.find("Wait at Stop: 1");
  int p2 = output1.find("Time on bus: 0");
  EXPECT_GE(p1,0);
  EXPECT_GE(p2,0);


  passenger1 -> GetOnBus();
  for(int i = 0; i < 5; i++){
    passenger1 -> Update();
  }
  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();
  int p3 = output2.find("Time on bus: 6");
  EXPECT_GE(p3,0);
};


TEST_F(PassengerTests, GetOnBus) {  // GetOnBus method
  passenger = new Passenger();
  EXPECT_EQ(passenger->IsOnBus(), false);
  passenger->GetOnBus();
  EXPECT_EQ(passenger->IsOnBus(), true);

  passenger1 = new Passenger(12);
  passenger1 -> GetOnBus();
  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  int p1 = output1.find("Time on bus: 1");
  EXPECT_GE(p1,0);
};


TEST_F(PassengerTests, GetTotalWait){  // GetTotalWait method
  passenger1 = new Passenger();
  passenger1 -> Update();
  EXPECT_EQ(passenger1 -> GetTotalWait(), 1);

  passenger1 -> GetOnBus();
  EXPECT_EQ(passenger1 -> GetTotalWait(), 2);
  for(int i = 0; i < 5; i++){
    passenger1 -> Update();
  }
  EXPECT_EQ(passenger1 -> GetTotalWait(), 7);

};


TEST_F(PassengerTests, IsOnBus){  // IsOnBus method
  passenger = new Passenger();
  EXPECT_EQ(passenger->IsOnBus(), false);
  passenger->GetOnBus();
  EXPECT_EQ(passenger->IsOnBus(), true);

};


TEST_F(PassengerTests, GetDestination) {  // GetDestination
  passenger = new Passenger();
  EXPECT_EQ(passenger->GetDestination(), -1);

  passenger1 = new Passenger(12);
  EXPECT_EQ(passenger1->GetDestination(), 12);

  passenger2 = new Passenger(1, "John");
  EXPECT_EQ(passenger2->GetDestination(), 1);

};


TEST_F(PassengerTests, ReportNameCheck){  // Report method
  passenger1 = new Passenger(12,"John Joe");
  passenger2 = new Passenger();

  std::string exp_output1 = "Name: John Joe";
  std::string exp_output2 = "Name: Nobody";

  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  passenger2 -> Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();

  int p1 = output1.find(exp_output1);
  int p2 = output2.find(exp_output2);

  EXPECT_GE(p1,0);
  EXPECT_GE(p2,0);
};


TEST_F(PassengerTests, ReportIDCheck){  // Report method
  passenger1 = new Passenger(12,"John Joe");
  passenger2 = new Passenger();

  std::string exp_output1 = "Destination: 12";
  std::string exp_output2 = "Destination: -1";

  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();

  testing::internal::CaptureStdout();
  passenger2 -> Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();

  int p1 = output1.find(exp_output1);
  int p2 = output2.find(exp_output2);

  EXPECT_GE(p1,0);
  EXPECT_GE(p2,0);
};

TEST_F(PassengerTests, ReportTotalWait){  // Report method
  passenger1 = new Passenger();
  passenger1 -> Update();

  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  int p1 = output1.find("Total Wait: 1");

  passenger1 -> GetOnBus();
  for(int i = 0; i < 5; i++){
    passenger1 -> Update();
  }
  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();
  int p2 = output2.find("Total Wait: 7");

  EXPECT_GE(p1,0);
  EXPECT_GE(p2,0);
};


TEST_F(PassengerTests, ReportWaitAtStop) {  // Report method
  passenger1 = new Passenger();
  passenger1 -> Update();
  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  int p1 = output1.find("Wait at Stop: 1");
  EXPECT_GE(p1,0);

  passenger1 -> Update();
  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();
  int p2 = output2.find("Wait at Stop: 2");
  EXPECT_GE(p2,0);
};


TEST_F(PassengerTests, ReportTimeOnBus) {  // Report method
  passenger1 = new Passenger();
  passenger1 -> Update();
  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output1 = testing::internal::GetCapturedStdout();
  int p1 = output1.find("Time on bus: 0");
  EXPECT_GE(p1,0);

  passenger1 -> GetOnBus();
  passenger1 -> Update();
  testing::internal::CaptureStdout();
  passenger1 -> Report(std::cout);
  std::string output2 = testing::internal::GetCapturedStdout();
  int p2 = output2.find("Time on bus: 2");
  EXPECT_GE(p2,0);
};
