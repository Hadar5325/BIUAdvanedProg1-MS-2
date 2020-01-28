//
// Created by amit on 12/01/2020.
//


#include <bits/stdc++.h>
#include <algorithm>
#include "Searchable.h"
#include "Searcher.h"
#include "Matrix.h"
#include "StateValueContainer.h"
#include "StringBuilder.h"
#include <vector>
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
  MatrixProblemSolverOA(Searcher<T> *s) {
    this->searcher = s;
  }

  string solve(Matrix<T> *prob) {
    //Solve the problem by using the searcher member's search func.
    vector<State<T> *> states;
    states = this->searcher->search(prob);

    //build the solution.
    StringBuilder<T> sb;
    return sb.getSolutionForSearchingProblem(states);
  }
};

class StringReverser : public Solver<string, string> {

 public:
  string solve(string *prob) {

    string rev = *prob;
    std::reverse(rev.begin(), rev.end());
    return rev;
  }

};

