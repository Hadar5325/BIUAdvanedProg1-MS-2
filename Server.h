//
// Created by amit on 12/01/2020.
//

#include "ClientHandler.h"

namespace server_side {
class Server {
 public:
  virtual void open(int port, ClientHandler *c) = 0;
  virtual void stop() = 0;
  virtual void start(ClientHandler *c) = 0;
};

class MySerialServer : public Server {

 public:
  void open(int port, ClientHandler *c);
  void stop();
  void start(ClientHandler *c);

};

namespace boot {

class Main {
 public:
  void main(string port);
};
}
}

