//
// Created by amit on 27/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__BFS_H_
#define BIUADVANEDPROG1_MS_2__BFS_H_

#include "Searcher.h"
#include "Searchable.h"
#include "State.h"
template<class T>
class BFS : public Searcher<T> {
 public:
  string getSearcherName() {
    //return typeid(this).name();
    return "BFS";
  }
  //taken from https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

  vector<State<T> *> search(Searchable<T> *searchable) {
    //reset counting of evaluated nodes before every run. FOR THE EXPERIMENT
    this->resetEvaluatedNodes();
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    auto initState = searchable->getInitialState();
    closed.insert(initState);
    //create a regular q .
    list<State<T> *> bfsQueue;
    bfsQueue.push_back(initState);
    while (!bfsQueue.empty()) {
      State<T> *v = bfsQueue.front();
      bfsQueue.pop_front();
      this->incEvaluatedNodes();
      if (searchable->isGoalState(v)) {
        return this->backTrace(v);
      }
      vector<State<T> *> successors = searchable->getAllPossibleStates(v);
      for (State<T> *s : successors) {
        if (closed.find(s) == closed.end()) {
          s->setCameFrom(v);
          closed.insert(s);
          bfsQueue.push_back(s);
        }
      }
    }
  }
};


#endif //BIUADVANEDPROG1_MS_2__BFS_H_
