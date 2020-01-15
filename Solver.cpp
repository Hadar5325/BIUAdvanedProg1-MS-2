//
// Created by amit on 12/01/2020.
//

#include "Solver.h"

template<class Problem, class Solution>
Solution ObjectAdapter::solve(Problem prob) {

  this->searcher.search(prob);
}