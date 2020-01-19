#include <stack>
#include <algorithm>
#include <list>
#include <bits/stdc++.h>
#include "queue"
#include "Searchable.h"

template<class T>

class ISearcher {
  virtual vector<State<T>> search(Searchable<T> searchable) = 0;
  virtual int getNumberOfNodesEvaluated() = 0;
};

template<class T>
struct StateCostCompare {
  bool operator()(const State<T> &ls, const State<T> &rs) {
    return ls.getCost() > rs.getCost();
  }
};


//Taken from https://stackoverflow.com/questions/16749723/how-i-can-find-value-in-priority-queue.

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
>
class MyPriorityQueue : public std::priority_queue<T, Container, Compare> {
 public:
  typedef typename
  std::priority_queue<
      T,
      Container,
      Compare>::container_type::const_iterator const_iterator;

  bool find(const State<T> &val) const {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
      if (val.equal_to(*first)) return true;
      ++first;
    }
    return false;
  }

  State<T> findAndRemove(const State<T> &val) const {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
      if (val.equal_to(*first)) {
        this->c.erase(first);
        return first;
      }
      ++first;
    }
    return false;
  }

  int size() {
    return this->size();
  }
  void pop() {
    this->pop();
  }

};

template<class T>
class Searcher : public ISearcher<T> {
 private:
  MyPriorityQueue<State<T>, vector<State<T>>, StateCostCompare<T>> openList;
  int evaluatedNodes;
 public:
  Searcher() {
    evaluatedNodes = 0;
  }
  virtual vector<State<T>> search(Searchable<T> searchable) = 0;

  int getNumberOfNodesEvaluated() {
    return evaluatedNodes;
  }
  virtual int openListSize() {
    return openList.size();
  }

  bool openListContains(State<T> state) {
    return this->openList.find(state);
  }

  virtual string getSearcherName() {};

 protected :
  State<T> popOpenList() {
    evaluatedNodes++;
    State<T> s = openList.top();
    openList.pop();
    return s;
  }

  void addToOpenList(State<T> s) {
    this->openList.push(s);
  }

  vector<State<T>> backTrace(unordered_set<State<T>> closed) {
    vector<State<T>> backTraceVector;
    auto lastIt = closed.begin();
    --lastIt;
    State<T> *last = *lastIt;
    while (last != nullptr) {
      backTraceVector.push_back(last);
      last = last->getCameFrom();
    }
    return backTraceVector;
  }

  State<T> findAndRemove(State<T> state) {
    return openList.findAndRemove(state);
  }

};

template<class T>
class BestFS : public Searcher<T> {

 public:
  string getSearcherName() {
    return "BestFS";
  }
  vector<State<T>> search(Searchable<T> searchable) {
    addToOpenList(searchable.getInitialState()); // inherited from Searcher
    unordered_set<State<T>> closed;
    while (this->openListSize() > 0) {
      State<T> n = this->popOpenList(); // inherited from Searcher, removes the best state
      closed.insert(n);
      if (searchable.isGoalState(n)) {
        return this->backTrace(closed);
      }
      vector<State<T>> successors = searchable.getAllPossibleStates(n);
      for (State<T> s : successors) {
        if (closed.find(s) == closed.end() && !openListContains(s)) {
          addToOpenList(s);
        } else if (n.getCost() < s.getCost()) {
          if (!openListContains(s))
            addToOpenList(s);
          else {
            auto v = findAndRemove(s);
            v.setCost(n.getCost());
            addToOpenList(v);
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
    return "DFS";
  }
  vector<State<T>> search(Searchable<T> searchable) {
    addToOpenList(searchable.getInitialState()); // inherited from Searcher
    unordered_set<State<T>> closed;
    while (this->openListSize() > 0) {
      State<T> v = this->popOpenList();
      if (closed.find(v) == closed.end()) {
        closed.insert(v);
        vector<State<T>> successors = searchable.getAllPossibleStates(v);
        for (State<T> s : successors)
          addToOpenList(s);
      }
    }

    return this->backTrace(closed);
  }
};

template<class T>
class BFS : public Searcher<T> {
 public:
  string getSearcherName() {
    return "BFS";
  }
  vector<State<T>> search(Searchable<T> searchable) {
    unordered_set<State<T>> closed;
    closed.insert(searchable.getInitialState());
    addToOpenList(searchable.getInitialState());
    while (this->openListSize() > 0) {
      State<T> v = this->popOpenList();
      if (searchable.isGoalState(v)) {
        return this->backTrace();
      }
      vector<State<T>> successors = searchable.getAllPossibleStates(v);
      for (State<T> s : successors) {
        if (closed.find(s) == closed.end()) {
          closed.insert(s);
          this->addToOpenList(s.getCameFrom());
        }
      }
    }
  }
};

template<class T>
class AStar : public Searcher<T> {
 public:
  string getSearcherName() {
    return "A*";
  }
  vector<State<T>> search(Searchable<T> searchable) {
    addToOpenList(searchable.getInitialState());
    unordered_set<State<T>> closed;

    while (this->openListSize() > 0) {

    }
  }
};




