

#include "Solver.h"
#include "CacheManager.h"

class ClientHandler {

 public:
  virtual void handleClient(int client_port) = 0;
};

class MyTestClientHandler : public ClientHandler {
 private:
  Solver<Problem, Solution> *solver;
  CacheManager<Problem, Solution> *c;
 public:
  MyTestClientHandler(Solver<Problem, Solution> *s, CacheManager<Problem, Solution> *cm) : solver(s), c(cm) {

  };
  void handleClient(int client_port);

};
