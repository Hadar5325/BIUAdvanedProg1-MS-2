

#include "Solver.h"
#include "CacheManager.h"

class ClientHandler{

 protected:
  void readFromClient(int client_port, string &input) const;

 public:
  virtual void handleClient(int client_port) = 0;
};

/**
 *
 * Client handler for the matrix searching problem.
 *
 */
class MatrixSearchingClientHandler : public ClientHandler {
 private:
  Solver<Matrix<double>, string> *solver;
  CacheManager<Matrix<double>, string> *c;
 public:
  MatrixSearchingClientHandler(Solver<Matrix<double>, string> *s, CacheManager<Matrix<double>, string> *cm)
      : solver(s), c(cm) {
  };
  void handleClient(int client_port);

};

class MyTestClientHandler : public ClientHandler {
 private:
  Solver<string, string> *solver;
  CacheManager<string, string> *c;
 public:
  MyTestClientHandler(Solver<string, string> *s, CacheManager<string, string> *cm) : solver(s), c(cm) {

  };
  void handleClient(int client_port);

};
