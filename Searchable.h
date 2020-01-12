//
// Created by amit on 13/01/2020.
//

#ifndef BIUADVANEDPROG1_MS_2__SEARCHABLE_H_
#define BIUADVANEDPROG1_MS_2__SEARCHABLE_H_

class Searchable {

  virtual void search() = 0;
};

class Searcher : public Searchable {

  virtual void search() = 0;

};

#endif //BIUADVANEDPROG1_MS_2__SEARCHABLE_H_
