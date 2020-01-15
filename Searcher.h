
#include "Searchable.h"
template<class T>
class Searcher {
  virtual void search(Searchable<T> searchable) = 0;
};

template<class T>
class BFS : public Searcher<T> {
  void search(Searchable<T> searchable);
};

template<class T>
class DFS : public Searcher<T> {
  void search(Searchable<T> searchable);
};

template<class T>
class BestFS : public Searcher<T> {
  void search(Searchable<T> searchable);
};

template<class T>
class AStar : public Searcher<T> {
  void search(Searchable<T> searchable);
  \

};




