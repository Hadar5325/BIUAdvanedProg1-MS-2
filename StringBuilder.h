//
// Created by amit on 15/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__STRINGBUILDER_H_
#define BIUADVANEDPROG1_MS_2__STRINGBUILDER_H_

#include "State.h"
#include <string>

using namespace std;
template<class T>
class StringBuilder {

 public:
  string getSolutionForSearchingProblem(vector<State<T> *> states) {

    //with the given states vector, build the path as the solution.
    string path;
    auto size = states.size();
    //The states goes from the last state to the first so we build it backwards.
    unsigned int j = size - 1;
    State<double> *state = states.at(j);
    path += state->toString();

    for (j = size - 2; j >= 1; --j) {
      state = states.at(j);
      path += " ," + state->toString();
    }

    state = states.at(j);
    path += " ," + state->toString();

    return path;
  }

};

#endif //BIUADVANEDPROG1_MS_2__STRINGBUILDER_H_
