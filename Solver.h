//
// Created by amit on 12/01/2020.
//


#include <bits/stdc++.h>
#include <algorithm>
#include "Searchable.h"
#include "Searcher.h"
#include "Matrix.h"
#include "StateValueContainer.h"

using namespace std;

template<class Problem, class Solution>
class Solver {
 public:
  virtual Solution solve(Problem *prob) = 0;

};

template<class T>
class MatrixProblemSolverOA : public Solver<Matrix<T>, string> {
 private:
  Searcher<T> *searcher;
 public:
  MatrixProblemSolverOA() {
    this->searcher = new AStar<T>();
  }

  string solve(Matrix<T> *prob) {
    auto states = this->searcher->search(prob);
    //build the path from the vector of states.
    string solution;
    auto size = states.size();
    //start from the end because it is backwards
    unsigned int j = size - 1;
    State<double> *state = states.at(j);
    solution += state->toString();

    for (j = size - 2; j >= 1; --j) {
      state = states.at(j);
      solution += ", " + state->toString();
    }

    state = states.at(j);
    solution += ", " + state->toString();

    return solution;
  }
};

class StringReverser : public Solver<string, string> {

 public:
  string solve(string prob) {

    string rev = prob;
    std::reverse(rev.begin(), rev.end());
    return rev;
  }

};

