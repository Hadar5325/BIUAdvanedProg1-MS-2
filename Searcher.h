#include <stack>
#include <algorithm>
#include <list>
#include <bits/stdc++.h>
#include <queue>
#include "Searchable.h"
#include "MyPriorityQueue.h"


template<class T>
class ISearcher {
  virtual vector<State<T> *> search(Searchable<T> *searchable) = 0;
  virtual int getNumberOfNodesEvaluated() = 0;
};

template<class T>
class Searcher : public ISearcher<T> {
 private:
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

  virtual vector<State<T> *> backTrace(State<T> *lastState) {
    vector<State<T> *> backTraceVector;

    State<T> *last = lastState;
    while (last != nullptr) {
      if (last->getCameFrom() != nullptr) {
        backTraceVector.push_back(last);
        last = last->getCameFrom();
      } else
        last = nullptr;
    }
    this->openList.clear();
    this->evaluatedNodes = 0;
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
    return hasher(key->identifier());
  }
};
template<class T>
class EqualFn {
 public:
  bool operator()(State<T> *key1, State<T> *key2) const {
    return key1->equal_to(key2);
  }
};
template<class T>
class BestFS : public Searcher<T> {

 public:
  string getSearcherName() {
    //return typeid(this).name();
    return "BestFS";
  }
  vector<State<T> *> search(Searchable<T> *searchable) {
//    this->addToOpenList(searchable->getInitialState()); // inherited from Searcher
//    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
//    while (this->openListSize() > 0) {
//      State<T> *n = this->popOpenList(); // inherited from Searcher, removes the best state
//      if (searchable->isGoalState(n)) {
//        auto size = closed.size();
//        State<T> *last = nullptr;
//        for (auto c : closed) {
//          last = c;
//        }
//        return this->backTrace(last);
//      }
//      vector<State<T> *> successors = searchable->getAllPossibleStates(n);
//      for (State<T> *s : successors) {
//        bool inClosed = closed.find(s) != closed.end();
//        bool inOpenList = this->openListContains(s);
//        if (!inClosed) {
//          closed.insert(s);
//          this->addToOpenList(s);
//        }
//      }
//      closed.insert(n);
//    }
//  }

    this->addToOpenList(searchable->getInitialState()); // inherited from Searcher
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    while (this->openListSize() > 0) {
      State<T> *n = this->popOpenList(); // inherited from Searcher, removes the best state
      closed.insert(n);
      if (searchable->isGoalState(n)) {
        return this->backTrace(n);
      }
      vector<State<T> *> successors = searchable->getAllPossibleStates(n);
      for (State<T> *s : successors) {
        bool inClosed = closed.find(s) != closed.end();
        bool inOpenList = this->openListContains(s);
        if (!inClosed && !inOpenList) {
          this->addToOpenList(s);
        } else {
          if (!this->openListContains(s)) {
            //s->setCost(n->getCost());
            this->addToOpenList(s);
          } else {
            auto v = this->findAndRemove(s);
            if (s->getCost() < v->getCost()) {
              v->setCost(s->getCost());
              v->setCameFrom(n);
              v->setStepString(s->getStepString());
            }
            this->addToOpenList(v);
          }
        }
      }
    }
  }
};

template<class T>
class DFS : public Searcher<T> {
 public:
  string getSearcherName() {
    //return typeid(this).name();
    return "DFS";
  }
  vector<State<T> *> search(Searchable<T> *searchable) {

    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    auto initState = searchable->getInitialState();
    stack<State<T> *> dfsStack;
    dfsStack.push(initState);
    while (!dfsStack.empty()) {
      State<T> *v = dfsStack.top();
      dfsStack.pop();
      if (searchable->isGoalState(v)) {
        return this->backTrace(v);
      }
      if (closed.find(v) == closed.end()) {
        closed.insert(v);
        vector<State<T> *> successors = searchable->getAllPossibleStates(v);
        for (State<T> *s : successors)
          dfsStack.push(s);
      }
    }
  }
};

template<class T>
class BFS : public Searcher<T> {
 public:
  string getSearcherName() {
    //return typeid(this).name();
    return "BFS";
  }
  //taken from https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/

  vector<State<T> *> search(Searchable<T> *searchable) {
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    auto initState = searchable->getInitialState();
    closed.insert(initState);
    list<State<T> *> bfsQueue;
    bfsQueue.push_back(initState);
    //this->addToOpenList(searchable->getInitialState());
    while (!bfsQueue.empty()) {
      State<T> *v = bfsQueue.front();
      bfsQueue.pop_front();
      if (searchable->isGoalState(v)) {
        return this->backTrace(v);
      }
      vector<State<T> *> successors = searchable->getAllPossibleStates(v);
      for (State<T> *s : successors) {
        if (closed.find(s) == closed.end()) {
          closed.insert(s);
          bfsQueue.push_back(s);
        }
      }
    }
  }
};

template<class T>
class AStar : public Searcher<T> {
 private:

  FScorePriorityQueue<T, vector<State<T> *>> aStarPQ;
  int evaluatedNodes;

 public:
  string getSearcherName() {
    //return typeid(this).name();
    return "AStar";
  }

  int openListSize() {
    return aStarPQ.size();
  }

  bool openListContains(State<T> *state) {
    return aStarPQ.find(state);
  }

  vector<State<T> *> search(Searchable<T> *searchable) {
    State<T> *initState = searchable->getInitialState();
    initState->setFCost(searchable->heuristicsFunction(initState));
    this->addToOpenList(initState);
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    while (this->openListSize() > 0) {
      State<T> *q = this->popOpenList();
      if (searchable->isGoalState(q)) {
        this->aStarPQ.clear();
        return this->backTrace(q);
      }
      closed.insert(q);
      vector<State<T> *> successors = searchable->getAllPossibleStates(q);
      for (State<T> *s : successors) {
        for (State<T> *s : successors) {
          bool inClosed = closed.find(s) != closed.end();
          bool inOpenList = this->openListContains(s);
          if (!inClosed && !inOpenList) {
            this->addToOpenList(s);
          } else {
            double tentative_score = q->getCost() + s->getSelfCost();
            if (!this->openListContains(s)) {
              s->setCameFrom(q);
              s->setStepString(s->getStepString());
              s->setCost(tentative_score);
              s->setFCost(s->getCost() + searchable->heuristicsFunction(s));
              this->addToOpenList(s);
            } else {
              auto v = this->findAndRemove(s);
              if (tentative_score < v->getCost()) {
                v->setCameFrom(q);
                v->setStepString(s->getStepString());
                v->setCost(tentative_score);
                v->setFCost(v->getCost() + searchable->heuristicsFunction(v));
              }
              this->addToOpenList(v);
            }
          }
        }
      }
    }
  }

 protected :
  State<T> *popOpenList() {
    evaluatedNodes++;
    State<T> *s = aStarPQ.top();
    aStarPQ.pop();
    return s;
  }

  void addToOpenList(State<T> *s) {
    aStarPQ.push(s);
  }

  State<T> *findAndRemove(State<T> *state) {
    return aStarPQ.findAndRemove(state);
  }

};




