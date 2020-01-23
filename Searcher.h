#include <stack>
#include <algorithm>
#include <list>
#include <bits/stdc++.h>
#include "queue"
#include "Searchable.h"

template<class T>
struct StateCostCompare {
  int operator()(State<T> *ls, State<T> *rs) {
    return ls->getCost() > rs->getCost();
  }
};


//Taken from https://stackoverflow.com/questions/16749723/how-i-can-find-value-in-priority-queue.

template<
    class T,
    class Container = std::vector<State<T> *>
>
class MyPriorityQueue : public std::priority_queue<T, Container, StateCostCompare<T>> {
 public:
  typedef typename
  std::priority_queue<
      T,
      Container,
      StateCostCompare<T>>;

  bool find(State<T> *val) {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
      auto f = *first;
      if (val->equal_to(f))
        return true;
      ++first;
    }
    return false;
  }

  State<T> *findAndRemove(State<T> *val) {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
      auto f = *first;
      if (val->equal_to(f)) {
        this->c.erase(first);
        return f;
      }
      ++first;
    }
    return nullptr;
  }

  int size() {
    return this->c.size();
  }

  State<T> *top() {
    auto it = this->c.begin();
    State<T> *s = *it;
    return s;
  }
  void pop() {
    auto it = this->c.begin();
    this->c.erase(it);
  }
  void clear() {
    this->c.clear();
  }

};

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
  virtual vector<State<T> *> search(Searchable<T> *searchable) = 0;

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
  State<T> *popOpenList() {
    evaluatedNodes++;
    State<T> *s = openList.top();
    openList.pop();
    return s;
  }

  void addToOpenList(State<T> *s) {
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
    return backTraceVector;
  }

  State<T> *findAndRemove(State<T> *state) {
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
    this->addToOpenList(searchable->getInitialState()); // inherited from Searcher
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    while (this->openListSize() > 0) {
      State<T> *n = this->popOpenList(); // inherited from Searcher, removes the best state
      closed.insert(n);
      if (searchable->isGoalState(n)) {
        auto size = closed.size();
        State<T> *last = nullptr;
        for (auto c : closed) {
          last = c;
        }
        return this->backTrace(last);
      }
      vector<State<T> *> successors = searchable->getAllPossibleStates(n);
      for (State<T> *s : successors) {
        bool inClosed = closed.find(s) != closed.end();
        bool inOpenList = this->openListContains(s);
        double nCost = n->getCost();
        double sCost = s->getCost();
        if (!inClosed && !inOpenList) {
          this->addToOpenList(s);
        } else {
          if (n->getCost() < s->getCost()) {
            if (!this->openListContains(s)) {
              s->setCost(n->getCost());
              this->addToOpenList(s);
            } else {
              auto v = this->findAndRemove(s);
              v->setCost(n->getCost());
              v->setCameFrom(n);
              v->setStepString(s->getStepString());
              this->addToOpenList(v);
            }
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
    this->addToOpenList(searchable->getInitialState()); // inherited from Searcher
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    while (this->openListSize() > 0) {
      State<T> *v = this->popOpenList();
      if (searchable->isGoalState(v)) {
        return this->backTrace(v);
      }
      if (closed.find(v) == closed.end()) {
        closed.insert(v);
        vector<State<T> *> successors = searchable->getAllPossibleStates(v);
        for (State<T> *s : successors)
          this->addToOpenList(s);
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
  vector<State<T> *> search(Searchable<T> *searchable) {
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    closed.insert(searchable->getInitialState());
    this->addToOpenList(searchable->getInitialState());
    while (this->openListSize() > 0) {
      State<T> *v = this->popOpenList();
      if (searchable->isGoalState(v)) {
        return this->backTrace(v);
      }
      vector<State<T> *> successors = searchable->getAllPossibleStates(v);
      for (State<T> *s : successors) {
        if (closed.find(s) == closed.end()) {
          closed.insert(s);
          s->setCameFrom(v);
          this->addToOpenList(s);
        }
      }
    }
  }
};

template<class T>
class AStar : public Searcher<T> {
 public:
  string getSearcherName() {
    //return typeid(this).name();
    return "AStar";
  }
  vector<State<T> *> search(Searchable<T> *searchable) {

    State<T> *initState = searchable->getInitialState();
    double tentative_score = initState->getCost();
    initState->setCost(initState->getCost() + searchable->h(initState));
    this->addToOpenList(searchable->getInitialState());
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    //unordered_map<State<T>,double> fMap;
    while (this->openListSize() > 0) {
      State<T> *q = this->popOpenList();
      if (searchable->isGoalState(q)) {
        return this->backTrace(searchable, q);
      }

      vector<State<T> *> successors = searchable->getAllPossibleStates(q);
      for (State<T> *s : successors) {

      }

    }
  }

  vector<State<T> *> backTrace(Searchable<T> *searchable, State<T> *goalState) {

    vector<State<T> *> backTraceVector;

    State<T> *last = goalState;
    while (last != nullptr) {
      last->setCost(goalState->getCost() - searchable->h(goalState));
      backTraceVector.push_back(last);
      last = last->getCameFrom();
    }

  }

};




