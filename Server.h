//
// Created by amit on 12/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__SERVER_H_
#define BIUADVANEDPROG1_MS_2__SERVER_H_
namespace server_side {
class Server {
 public:
  virtual void open(int port) = 0;
  virtual void stop() = 0;
};

class MySerialServer : public Server{

 public:
  void open(int port);
  void stop();


};

}

#endif //BIUADVANEDPROG1_MS_2__SERVER_H_
