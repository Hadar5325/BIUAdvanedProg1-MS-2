//
// Created by amit on 27/01/2020.
//


#ifndef BIUADVANEDPROG1_MS_2__ASTAR_H_
#define BIUADVANEDPROG1_MS_2__ASTAR_H_

#include "State.h"
#include "Searcher.h"
#include "Searchable.h"


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
    //Same as BestFS but the priority q is by the fcost -  the sum of the total cost like the bfs, and the
    //result from the heuristic function.

    //reset counting of evaluated nodes before every run. FOR THE EXPERIMENT
    this->resetEvaluatedNodes();

    //add the first state to the open list queue
    this->addToOpenList(searchable->getInitialState());
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;


    while (this->openListSize() > 0) {
      //pop states witht the best fcost (lowest)
      State<T> *n = this->popOpenList();
      closed.insert(n);
      if (searchable->isGoalState(n)) {
        this->aStarPQ.clear();
        return this->backTrace(n);
      }
      //get successors - neighbors
      vector<State<T> *> successors = searchable->getAllPossibleStates(n);
      for (State<T> *s : successors) {
        bool inClosed = closed.find(s) != closed.end();
        bool inOpenList = this->openListContains(s);
        if (!inClosed && !inOpenList) {//if neighbors is not in closed or open , update it and add to open list
          s->setCameFrom(n); // update that it came from n
          s->setCost(n->getCost() + s->getSelfCost());
          s->setFCost(s->getCost() + searchable->heuristicsFunction(s)); //update the f cost with the heuristcs
          this->addToOpenList(s);
        } else {
          //if the new path is better then the current path
          if (n->getCost() + s->getSelfCost() < s->getCost()) {
            if (!inOpenList) {
              this->addToOpenList(s);
            } else {
              s->setCameFrom(n); // update that it came from n
              s->setCost(n->getCost() + s->getSelfCost());
              s->setFCost(s->getCost() + searchable->heuristicsFunction(s));
              auto v =this->findAndRemove(s);
              this->addToOpenList(v);
            }
          }
        }
      }
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

#endif //BIUADVANEDPROG1_MS_2__ASTAR_H_
