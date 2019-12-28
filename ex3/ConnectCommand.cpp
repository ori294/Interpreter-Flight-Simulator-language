//
// Created by gadi on 12/12/2019.
//


#include <mutex>
#include "SimulatorManager.h"
#define MAX_LENGTH 256

std::mutex mutex_lock;

/**
 * removeSpaces: Get a string and remove all blank spaces
 * @param str a string
 * @return the trimmed string
 */
std::string connectControlClient::removeSpaces(std::string str) {
  str.erase(remove(str.begin(), str.end(), '"'), str.end());
  return str;
}

/**
 * @param list_of_strings
 * @return 0
 */
int connectControlClient::execute(list<string> list_of_strings) {
  SimulatorManager::getInstance()->set_client(this);
  list<string>::iterator it = list_of_strings.begin();
  string _ip_ = removeSpaces(*list_of_strings.begin());
  char ip[MAX_LENGTH]; //copy to array for strtok function
  std::strcpy(ip, (_ip_).c_str());
  const char *my_ip = ip;
  it++;
  string my_port = to_string(SimulatorManager::getInstance()->get_interpreter()->change_var_to_value(
      *it)->calculate());
  char port[MAX_LENGTH]; //copy to array for strtok function
  std::strcpy(port, (my_port).c_str());
  int _port = atoi(port);
  //check if the iterator move by value or reference!!!
  socket_client = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_client == -1) {
    cerr << "can not create a client socket" << endl;
    return -1;
  }
  //create client socket
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = inet_addr(my_ip);
  address.sin_port = htons(_port);
  int is_connect = connect(socket_client, (struct sockaddr *) &address, sizeof(address));
  if (is_connect == -1) {
    cerr << "Could not connect to host server" << endl;
    return -2;
  }
  this->get_info = thread(run_client_to_simulator, &this->commandsToSim, socket_client);
  return 0;
}
/**
 * run in another thread until the program finish and send commands to simulator
 * @param commandsForS queue member of client for sending to simulator
 * @param socket_client
 */
void connectControlClient::run_client_to_simulator(queue<string> *commandsForS, int socket_client) {
  while (!SimulatorManager::getInstance()->check_end()) {
    while (!commandsForS->empty()) {
      mutex_lock.lock();
      const char *msg = commandsForS->front().c_str();
      int is_send = send(socket_client, msg, strlen(msg), 0);
      if (is_send == -1) {
        cout << "Error sending msg" << endl;
      }
      commandsForS->pop();
      mutex_lock.unlock();
    }
  }
}
/**
 * add one command to the queue of the client
 * @param s
 */
void connectControlClient::add_commands_to_queue(string s) {
  //lock the queue for the main thread!
  mutex_lock.lock();
  this->commandsToSim.push(s);
  mutex_lock.unlock();
}

int connectControlClient::get_num_of_arg() { return 2; }