//
// Created by gadi on 10/12/2019.
//
#ifndef INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_OPENSERVERCOMMAND_H_
#define INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_OPENSERVERCOMMAND_H_

#include <string>
#include <iostream>
#include "Command.h"
#include <list>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <map>
#include <cstring>
#include "../SimulatorManager.h"
#include <mutex>

using namespace std;

class OpenServerCommand : public Command {
 private:
  int numOfArg;
  map<int, pair<string, string>> data_about_airplane;
 public:
  thread get_info;
  OpenServerCommand() {
      data_about_airplane.insert(make_pair(0,
                                           make_pair("/instrumentation/airspeed-indicator/indicated-speed-kt", "0")));
      data_about_airplane.insert(make_pair(1, make_pair("/instrumentation/heading-indicator/offset-deg", "0")));
      data_about_airplane.insert(make_pair(2, make_pair("/instrumentation/altimeter/indicated-altitude-ft", "0")));
      data_about_airplane.insert(make_pair(3, make_pair("/instrumentation/altimeter/pressure-alt-ft", "0")));
      data_about_airplane.insert(make_pair(4,
                                           make_pair("/instrumentation/attitude-indicator/indicated-pitch-deg", "0")));
      data_about_airplane.insert(make_pair(5,
                                           make_pair("/instrumentation/attitude-indicator/indicated-roll-deg", "0")));
      data_about_airplane.insert(make_pair(6,
                                           make_pair("/instrumentation/attitude-indicator/internal-pitch-deg", "0")));
      data_about_airplane.insert(make_pair(7, make_pair("/instrumentation/attitude-indicator/internal-roll-deg", "0")));
      data_about_airplane.insert(make_pair(8, make_pair("/instrumentation/encoder/indicated-altitude-ft", "0")));
      data_about_airplane.insert(make_pair(9, make_pair("/instrumentation/encoder/pressure-alt-ft", "0")));
      data_about_airplane.insert(make_pair(10, make_pair("/instrumentation/gps/indicated-altitude-ft", "0")));
      data_about_airplane.insert(make_pair(11, make_pair("/instrumentation/gps/indicated-ground-speed-kt", "0")));
      data_about_airplane.insert(make_pair(12, make_pair("/instrumentation/gps/indicated-vertical-speed", "0")));
      data_about_airplane.insert(make_pair(13,
                                           make_pair("/instrumentation/heading-indicator/indicated-heading-deg", "0")));
      data_about_airplane.insert(make_pair(14,
                                           make_pair("/instrumentation/magnetic-compass/indicated-heading-deg", "0")));
      data_about_airplane.insert(make_pair(15, make_pair("/instrumentation/slip-skid-ball/indicated-slip-skid", "0")));
      data_about_airplane.insert(make_pair(16, make_pair("/instrumentation/turn-indicator/indicated-turn-rate", "0")));
      data_about_airplane.insert(make_pair(17,
                                           make_pair("/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
                                                     "0")));
      data_about_airplane.insert(make_pair(18, make_pair("/controls/flight/aileron", "0")));
      data_about_airplane.insert(make_pair(19, make_pair("/controls/flight/elevator", "0")));
      data_about_airplane.insert(make_pair(20, make_pair("/controls/flight/rudder", "0")));
      data_about_airplane.insert(make_pair(21, make_pair("/controls/flight/flaps", "0")));
      data_about_airplane.insert(make_pair(22, make_pair("/controls/engines/engine/throttle", "0")));
      data_about_airplane.insert(make_pair(23, make_pair("/engines/engine/rpm", "0")));

  }
  int execute(list<string> list_of_strings) override;
  int get_num_of_arg() override { return 1; }
  static void get_data_from_air_plane(int client_socket, map<int, pair<string, string>> *map_data);
  static void split_and_update_data(char *buffer, map<int, pair<string, string>> *map_data);
  float get_value(string s);
};

#endif //INTERPRETER_FLIGHT_SIMULATOR_LANGUAGE_EX3_OPENSERVERCOMMAND_H_