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

  virtual State<T> *findAndReturn(State<T> *state) {
    return this->openList.findAndReturn(state);
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
    //reset counting of evaluated nodes before every run.
    this->resetEvaluatedNodes();
    //add the initial state to the Q.
    this->addToOpenList(searchable->getInitialState());
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    while (this->openListSize() > 0) {
      State<T> *n = this->popOpenList();
      if (searchable->isGoalState(n)) {
        return this->backTrace(n);
      }
      vector<State<T> *> successors = searchable->getAllPossibleStates(n);
      for (State<T> *s : successors) {
        bool inClosed = closed.find(s) != closed.end();
        if (!inClosed) {
          s->setCameFrom(n);
          closed.insert(s);
          this->addToOpenList(s);
        }
      }
      closed.insert(n);
    }
  }
//    this->addToOpenList(searchable->getInitialState());
//    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
//    while (this->openListSize() > 0) {
//      State<T> *n = this->popOpenList();
//      closed.insert(n);
//      if (searchable->isGoalState(n)) {
//        return this->backTrace(n);
//      }
//      vector<State<T> *> successors = searchable->getAllPossibleStates(n);
//
//      for (State<T> *s : successors) {
//        bool inClosed = closed.find(s) != closed.end();
//        bool inOpenList = this->openListContains(s);
//        if (!inClosed && !inOpenList) {
//          s->setCameFrom(n);
//          this->addToOpenList(s);
//        } else {
//          if (!inOpenList) {
//            s->setCameFrom(n);
//            this->addToOpenList(s);
//          } else {
//            auto v = this->findAndRemove(s);
//            if (n->getCost() + s->getSelfCost() < v->getCost()) {
//              v->setCameFrom(n);
//              v->setCost(n->getCost() + s->getSelfCost());
//              v->setStepString(s->getStepString());
//            }
//
//            this->addToOpenList(v);
//          }
//        }
//      }
//    }
//    this->addToOpenList(searchable->getInitialState());
//    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
//    while (this->openListSize() > 0) {
//      State<T> *n = this->popOpenList();
//      closed.insert(n);
//      if (searchable->isGoalState(n)) {
//        return this->backTrace(n);
//      }
//      vector<State<T> *> successors = searchable->getAllPossibleStates(n);
//
//      for (State<T> *s : successors) {
//        bool inClosed = closed.find(s) != closed.end();
//        bool inOpenList = this->openListContains(s);
//        if (!inClosed && !inOpenList) {
//          s->setCameFrom(n);
//          this->addToOpenList(s);
//        } else {
//          if (n->getCost() + s->getSelfCost() < s->getCost()) {
//            if (!inOpenList) {
//              s->setCameFrom(n);
//              this->addToOpenList(s);
//            } else {
//              auto v = this->findAndRemove(s);
//              v->setCameFrom(n);
//              v->setStepString(s->getStepString());
//              v->setCost(n->getCost() + s->getSelfCost());
//              this->addToOpenList(s);
//            }
//          }
//        }
//      }
//    }}

};

template<class T>
class DFS : public Searcher<T> {
 public:
  string getSearcherName() {
    //return typeid(this).name();
    return "DFS";
  }
  vector<State<T> *> search(Searchable<T> *searchable) {
    //reset counting of evaluated nodes before every run.

    this->resetEvaluatedNodes();
    //https://en.wikipedia.org/wiki/Depth-first_search

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
          s->setCameFrom(v);
          dfsStack.push(s);
        }
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
    //reset counting of evaluated nodes before every run.
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

template<class T>
class AStar : public Searcher<T> {
 private:

  FScorePriorityQueue<T, vector<State<T> *>> aStarPQ;

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
    //Same as BestFS but the priority q is by the fscore -  the sum of the total cost like the bfs, and the
    //result from the heuristic function.

    //reset counting of evaluated nodes before every run.
    this->resetEvaluatedNodes();
    State<T> *initState = searchable->getInitialState();
    initState->setFCost(searchable->heuristicsFunction(initState));
    this->addToOpenList(initState);
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    while (this->openListSize() > 0) {
      State<T> *n = this->popOpenList(); // inherited from Searcher, removes the best state
      if (searchable->isGoalState(n)) {
        return this->backTrace(n);
      }
      vector<State<T> *> successors = searchable->getAllPossibleStates(n);
      for (State<T> *s : successors) {
        bool inClosed = closed.find(s) != closed.end();
        if (!inClosed) {
          s->setCameFrom(n);
          s->setFCost(s->getCost() + searchable->heuristicsFunction(s));
          closed.insert(s);
          this->addToOpenList(s);
        }
      }
      closed.insert(n);

      //https://en.wikipedia.org/wiki/A*_search_algorithm
//    State<T> *initState = searchable->getInitialState();
//    initState->setFCost(searchable->heuristicsFunction(initState));
//    this->addToOpenList(initState);
//    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
//    while (this->openListSize() > 0) {
//      State<T> *n = this->popOpenList();
//      if (searchable->isGoalState(n)) {
//        this->aStarPQ.clear();
//        return this->backTrace(n);
//      }
//      closed.insert(n);
//      vector<State<T> *> successors = searchable->getAllPossibleStates(n);
//      for (State<T> *s : successors) {
//        bool inClosed = closed.find(s) != closed.end();
//        bool inOpenList = this->openListContains(s);
//        if (!inClosed && !inOpenList) {
//          //s->setCameFrom(n);
//          s->setFCost(s->getCost() + searchable->heuristicsFunction(s));
//          this->addToOpenList(s);
//        } else {
//          auto v = this->findAndReturn(s);
//          if (v != NULL && n->getCost() + s->getSelfCost() < v->getCost()) {
//            if (!inOpenList) {
//              //s->setCameFrom(n);
//              s->setFCost(s->getCost() + searchable->heuristicsFunction(s));
//              this->addToOpenList(s);
//            } else {
//              v = this->findAndRemove(s);
//              v->setCameFrom(n);
//              v->setStepString(s->getStepString());
//              v->setFCost(v->getCost() + searchable->heuristicsFunction(s));
//              this->addToOpenList(s);
//            }
//          }
//        }
//
//      }
//    }
//    this->addToOpenList(searchable->getInitialState());
//    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
//    while (this->openListSize() > 0) {
//      State<T> *n = this->popOpenList();
//      closed.insert(n);
//      if (searchable->isGoalState(n)) {
//        return this->backTrace(n);
//      }
//      vector<State<T> *> successors = searchable->getAllPossibleStates(n);
//
//      for (State<T> *s : successors) {
//        bool inClosed = closed.find(s) != closed.end();
//        bool inOpenList = this->openListContains(s);
//        if (!inClosed && !inOpenList) {
//          s->setCameFrom(n);
//          s->setFCost(s->getCost() + searchable->heuristicsFunction(s));
//          this->addToOpenList(s);
//        } else {
//          if (n->getCost() + s->getSelfCost() < s->getCost()) {
//            if (!inOpenList) {
//              //s->setCameFrom(n);
//              //s->setFCost(s->getCost() + searchable->heuristicsFunction(s));
//              this->addToOpenList(s);
//            } else {
//              auto v = this->findAndRemove(s);
//              v->setCameFrom(n);
//              v->setStepString(s->getStepString());
//              v->setCost(n->getCost() + s->getSelfCost());
//              v->setFCost(s->getCost() + searchable->heuristicsFunction(s));
//              this->addToOpenList(s);
//            }
//          }
//        }
//      }
    }

  }

 protected :
  State<T> *popOpenList() {
    this->incEvaluatedNodes();
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




