//
// Created by amit on 12/01/2020.
//


#include <bits/stdc++.h>
#include <algorithm>
#include "Searchable.h"
#include "Searcher.h"
using namespace std;

template<class Problem, class Solution>
class Solver {
 public:
  virtual Solution solve(Problem prob) = 0;

};
template<class Problem, class Solution>
class ObjectAdapter : public Solver<Problem, Solution> {
 private:
  ISearcher<Problem> searcher;
 public:

  Solution solve(Problem prob);
};

class StringReverser : public Solver<string, string> {

 public:
  string solve(string prob) {

    string rev = prob;
    std::reverse(rev.begin(), rev.end());
    return rev;
  }

};

