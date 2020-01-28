//
// Created by amit on 27/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__BESTFS_H_
#define BIUADVANEDPROG1_MS_2__BESTFS_H_

#include "State.h"
#include "Searcher.h"
#include "Searchable.h"

template<class T>
class BestFS : public Searcher<T> {

 public:
  string getSearcherName() {
    //return typeid(this).name();
    return "BestFS";
  }
  vector<State<T> *> search(Searchable<T> *searchable) {
    //taken from the lecture
    //reset counting of evaluated nodes before every run. FOR THE EXPERIMENT
    this->resetEvaluatedNodes();

    //add the initial state to the Q.
    this->addToOpenList(searchable->getInitialState());
    unordered_set<State<T> *, StatesHasher<T>, EqualFn<T>> closed;
    while (this->openListSize() > 0) {
      State<T> *n = this->popOpenList();
      closed.insert(n);
      if (searchable->isGoalState(n)) {
        return this->backTrace(n);
      }
      vector<State<T> *> successors = searchable->getAllPossibleStates(n);

      for (State<T> *s : successors) {
        bool inClosed = closed.find(s) != closed.end();
        bool inOpenList = this->openListContains(s);
        if (!inClosed && !inOpenList) {//if neighbors is not in closed or open , update it and add to open list
          s->setCameFrom(n); //update that we came from n;
          s->setCost(n->getCost() + s->getSelfCost());
          this->addToOpenList(s);
        } else {
          //if the new path is better then the current path
          if (n->getCost() + s->getSelfCost() < s->getCost()) {
            if (!inOpenList) {
              this->addToOpenList(s);
            } else {
              s->setCameFrom(n); //update that we came from n;
              s->setCost(n->getCost() + s->getSelfCost());
              auto v = this->findAndRemove(s);
              this->addToOpenList(v);
            }
          }
        }
      }
    }
  }

};

#endif //BIUADVANEDPROG1_MS_2__BESTFS_H_
