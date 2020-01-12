//
// Created by amit on 12/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__CLIENTHANDLER_H_
#define BIUADVANEDPROG1_MS_2__CLIENTHANDLER_H_

#include "Solver.h"
#include "CacheManager.h"

class ClientHandler {

 public:
  virtual void handleClient(char* input, char* output) = 0;
};

class MyTestClientHandler : public ClientHandler {
 private:
  Solver<Problem, Solution> *solver;
  CacheManager *c;
 public:
  MyTestClientHandler(Solver<Problem, Solution> *s, CacheManager *cm) : solver(s), c(cm) {

  };
  void handleClient(char* input, char* output);

};
#endif //BIUADVANEDPROG1_MS_2__CLIENTHANDLER_H_
