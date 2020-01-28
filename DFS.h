//
// Created by amit on 27/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__DFS_H_
#define BIUADVANEDPROG1_MS_2__DFS_H_

#include "Searchable.h"
#include "State.h"
#include "Searcher.h"
template<class T>
class DFS : public Searcher<T> {
 private:
  unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
//  State<T> *recursiveDFS(State<T> *state,
//                         Searchable<T> *searchable) {
//    //https://en.wikipedia.org/wiki/Depth-first_search
//    this->incEvaluatedNodes();
//    closed.insert(state);
//    if (searchable->isGoalState(state)){
//      return state;
//    }
//    vector<State<T> *> successors = searchable->getAllPossibleStates(state);
//    for (State<T> *s : successors) {
//      if (closed.find(s) == closed.end()) {
//        s->setCameFrom(state);
//        if(searchable->isGoalState(s)) return s;
//        return recursiveDFS(s, searchable);
//      }
//    }
//
//
//  }
 public:
  string getSearcherName() {
    //return typeid(this).name();
    return "DFS";
  }
  vector<State<T> *> search(Searchable<T> *searchable) {

    //https://en.wikipedia.org/wiki/Depth-first_search

    //reset counting of evaluated nodes before every run. FOR THE EXPERIMENT
    this->resetEvaluatedNodes();

    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    auto initState = searchable->getInitialState();
    //create a stack
    stack<State<T> *> dfsStack;
    dfsStack.push(initState);
    while (!dfsStack.empty()) {
      State<T> *v = dfsStack.top();
      dfsStack.pop();
      this->incEvaluatedNodes();
      if (searchable->isGoalState(v)) {
        return this->backTrace(v);
      }
      if (closed.find(v) == closed.end()) {
        closed.insert(v);
        vector<State<T> *> successors = searchable->getAllPossibleStates(v);
        for (State<T> *s : successors) {
          if(closed.find(s) == closed.end()){
            s->setCameFrom(v);
            dfsStack.push(s);
          }
        }
      }
    }

//    //reset counting of evaluated nodes before every run.
//    this->resetEvaluatedNodes();
//    auto initialState = searchable->getInitialState();
//    auto goal = recursiveDFS(initialState, searchable);
//    auto v = this->backTrace(goal);
//    closed.clear();
//    return v;
  }

};

#endif //BIUADVANEDPROG1_MS_2__DFS_H_
