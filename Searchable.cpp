//
// Created by amit on 13/01/2020.
//

#include "Searchable.h"
#include <map>
template <class T>
void BFS<T>::search(Searchable<T> searchable) {

  addToOpenList(searchable.getInitialState()); // inherited from Searcher
  map<State<T>> closed;
  while (OpenListSize > 0) {
    State n = popOpenList(); // inherited from Searcher, removes the best state
    closed.Add(n);
    if (n.Equals(searchable. getIGoallState ()))
      return backTrace(); // private method, back traces through the parents
// calling the delegated method, returns a list of states with n as a parent
    List<State> succerssors = searchable. getAllPossibleStates(n);
    foreach (State s in succerssors)
    {
      if (!closed.Contains(s) && !openContaines(s))
      {
// s.setCameFrom(n); // already done by getSuccessors
        addToOpenList(s);
      }
      else
      {


}