//
// Created by amit on 24/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__MYPRIORITYQUEUE_H_
#define BIUADVANEDPROG1_MS_2__MYPRIORITYQUEUE_H_


//compare function for the min heap priority queue
template<class T>
struct StateCostCompare {
  int operator()(State<T> *ls, State<T> *rs) {
    return ls->getCost() > rs->getCost();
  }
};

template<
    class T, // The inner value of the state - double value in our case.
    class Container = std::vector<State<T> *>
>
//custom priority queue min heap by cost of states
class MyPriorityQueue : public std::priority_queue<T, Container, StateCostCompare<T>> {
 public:
  typedef typename
  std::priority_queue<
      T,
      Container>;
  //Taken from https://stackoverflow.com/questions/16749723/how-i-can-find-value-in-priority-queue.

  bool find(State<T> *val) {
    //iterate on the vector and find the matching state.
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
  State<T> *findAndReturn(State<T> *val) {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
      auto f = *first;
      if (val->equal_to(f)) {
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

//compare function for the min heap priority queue - F costs for the Astar algorithm
template<class T>
struct StateFCostCompare {
  int operator()(State<T> *ls, State<T> *rs) {
    return ls->getFCost() > rs->getFCost();
  }
};


template<
    class T,
    class Container = std::vector<State<T> *>
>
//custom priority queue min heap by cost of states
class FScorePriorityQueue : public std::priority_queue<T, Container, StateFCostCompare<T>> {
 public:
  typedef typename
  std::priority_queue<
      T,
      Container>;
  //Taken from https://stackoverflow.com/questions/16749723/how-i-can-find-value-in-priority-queue.

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
  State<T> *findAndReturn(State<T> *val) {
    auto first = this->c.cbegin();
    auto last = this->c.cend();
    while (first != last) {
      auto f = *first;
      if (val->equal_to(f)) {
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


#endif //BIUADVANEDPROG1_MS_2__MYPRIORITYQUEUE_H_
