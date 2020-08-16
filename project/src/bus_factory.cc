/**
 * @file bus_factory.cc
 *
 * @copyright Sunny Qin
 */
#include <vector>
#include "src/bus_factory.h"

int BusFactory::state1 = 0;
int BusFactory::state2 = 0;
int BusFactory::state3 = 0;


Bus * BusFactory::Generate(std::string name, Route * out, Route * in, int type,
                                                double speed) {
// create a new bus pointer
  Bus * new_bus;

// type parameter determines which bus type should be called
// 1 corresponds to small, 2 corresponds to reguar, and 3 corresponds to large
  if (type == 1) {
      new_bus =  new SmallBus(name, out, in, speed);
  } else if (type == 2) {
      new_bus = new RegularBus(name, out, in, speed);
  } else if (type == 3) {
      new_bus = new LargeBus(name, out, in, speed);
  }
  return new_bus;
}

Bus * BusFactory::Strategy1(std::string name, Route * out, Route * in,
                                                    double speed) {
    // std::cout << (state1%2);
    int type;
    if ((state1%2) == 0) {
        // use mod to track static variable
        // if equals 0, then generate small bus
        type = 1;
    } else if ((state1%2) == 1) {
        // if equals 1, then generate regular bus
        type = 2;
    }
    // keep updating state
    state1++;

    return BusFactory::Generate(name, out, in, type, speed);
}


Bus * BusFactory::Strategy2(std::string name, Route * out, Route * in,
                                                    double speed) {
    Bus * bus;
    if ((state2%2) == 0) {
        // use mod to track static variable
        // if equals 0, then generate regular bus
        bus = BusFactory::Generate(name, out, in, 2, speed);
    } else if ((state2%2) == 1) {
        // if equals 1, then generate large bus
        bus = BusFactory::Generate(name, out, in, 3, speed);
    }
    state2++;
    return bus;
}


Bus * BusFactory::Strategy3(std::string name, Route * out, Route * in,
                                                    double speed) {
    Bus * bus;
    if ((state3%3) == 0) {
        // use mod to track static variable
        // if equals 0, then generate small bus
        bus = BusFactory::Generate(name, out, in, 1, speed);
    } else if ((state3%3) == 1) {
        // if equals 1, then generate regular bus
        bus = BusFactory::Generate(name, out, in, 2, speed);
    } else if ((state3%3) == 2) {
        // if equals 2, then generate large bus
        bus = BusFactory::Generate(name, out, in, 3, speed);
    }
    // keep updating state
    state3++;
    return bus;
}

void SmallBus::Report(std::ostream& out) {
    out << "Type: Small" << std::endl;
    // call bus's report to report regular information of a bus.
    Bus::Report(out);
}

void RegularBus::Report(std::ostream& out) {
    out << "Type: Regular" << std::endl;
    // call bus's report to report regular information of a bus.
    Bus::Report(out);
}

void LargeBus::Report(std::ostream& out) {
    out << "Type: Large" << std::endl;
    // call bus's report to report regular information of a bus.
    Bus::Report(out);
}

