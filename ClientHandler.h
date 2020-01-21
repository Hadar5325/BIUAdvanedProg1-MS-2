

#include "Solver.h"
#include "CacheManager.h"

class ClientHandler {

 public:
  virtual void handleClient(int client_port) = 0;
};

class MyTestClientHandler : public ClientHandler {
 private:
  //TODO Handle the problem solution templates
  Solver<string, string> *solver;
  CacheManager<string , string> *c;
 public:
  MyTestClientHandler(Solver<string, string> *s, CacheManager<string, string> *cm) : solver(s), c(cm) {

  };
  void handleClient(int client_port);

};
