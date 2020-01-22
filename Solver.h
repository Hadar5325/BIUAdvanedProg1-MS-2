//
// Created by amit on 12/01/2020.
//


#include <bits/stdc++.h>
#include <algorithm>
#include "Searchable.h"
#include "Searcher.h"
#include "Matrix.h"
using namespace std;

template<class Problem, class Solution>
class Solver {
 public:
  virtual Solution solve(Problem prob) = 0;

};

template<class Problem, class Solution>
class SearcherObjectAdapter : public Solver<Problem, Solution> {
 protected:
  ISearcher<Problem> *searcher;
 public:
  virtual Solution solve(Problem prob) = 0;

};
template<class T>
class MatrixSearcherObjectAdapter : public SearcherObjectAdapter<Matrix<T>, string> {
 public:
  MatrixSearcherObjectAdapter() {
    this->searcher = new AStar<Cell<T>>();
  }

  string solve(Matrix<T> prob) {
    auto states = this->searcher.search(prob);

    //build the path from the vector of states.
    string solution;
    auto size = states.size();
    unsigned int j;
    for (j = 0; j < size - 1; j++) {
      auto state = states.at(j);
      solution += state.getStepString() + " (" + to_string(state.getStateValue().getValue()) + ") ,";
    }
    //on the last one, dont add a comma after it.
    auto state = states.at(j);
    solution += state.getStepString() + " (" + to_string(state.getStateValue().getValue()) + ")";

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

