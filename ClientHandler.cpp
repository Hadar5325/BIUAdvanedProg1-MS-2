
#include "ClientHandler.h"

void MyTestClientHandler::handleClient(istream input, ostream output) {
  char *line;
  input >> line;
  try {
    output << this->c->getSolutionToProblem(line)
  } catch (...) {
    output << this->solver.solve(line);
  }
}


