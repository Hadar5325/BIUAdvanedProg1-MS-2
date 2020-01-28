#include <stack>
#include <algorithm>
#include <list>
#include <bits/stdc++.h>
#include <queue>
#include "Searchable.h"
#include "MyPriorityQueue.h"


#ifndef BIUADVANEDPROG1_MS_2__SEARCHER_H_
#define BIUADVANEDPROG1_MS_2__SEARCHER_H_

template<class T>
class ISearcher {
  virtual vector<State<T> *> search(Searchable<T> *searchable) = 0;
  virtual int getNumberOfNodesEvaluated() = 0;
};

template<class T>
class Searcher : public ISearcher<T> {
 private:
  //Min heap priority queue
  MyPriorityQueue<T, vector<State<T> *>> openList;
  int evaluatedNodes;
 public:
  Searcher() {
    evaluatedNodes = 0;
  }
  virtual vector<State<T> *> search(Searchable<T> *searchable) {};

  int getNumberOfNodesEvaluated() {
    return evaluatedNodes;
  }
  virtual int openListSize() {
    return openList.size();
  }

  bool openListContains(State<T> *state) {
    return this->openList.find(state);
  }

  virtual string getSearcherName() {};

 protected :
  virtual State<T> *popOpenList() {
    evaluatedNodes++;
    State<T> *s = openList.top();
    openList.pop();
    return s;
  }

  virtual void addToOpenList(State<T> *s) {
    this->openList.push(s);
  }

  void incEvaluatedNodes() {
    evaluatedNodes++;
  }
  void resetEvaluatedNodes() {
    evaluatedNodes = 0;
  }

  virtual vector<State<T> *> backTrace(State<T> *lastState) {
    vector<State<T> *> backTraceVector;
    //The last state is the last one that was popped from the openlist - it is the goal.
    //every time access the came from property and add it to the vector. thats how we build the wanted path.
    State<T> *last = lastState;
    while (last != nullptr) {
      if (last->getCameFrom() != nullptr) {
        backTraceVector.push_back(last);
        last = last->getCameFrom();
      } else
        last = nullptr;
    }
    this->openList.clear();
    return backTraceVector;
  }

  virtual State<T> *findAndRemove(State<T> *state) {
    return this->openList.findAndRemove(state);
  }

};

template<class T>
struct StatesHasher {
 public:
  size_t operator()(State<T> *key) const {
    hash<string> hasher;
    return hasher(key->getIndetifier());
  }
};
template<class T>
class EqualFn {
 public:
  bool operator()(State<T> *key1, State<T> *key2) const {
    return key1->equal_to(key2);
  }
};

#endif //BIUADVANEDPROG1_MS_2__SEARCHER_H_
