
#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <list>
#include <fstream>
#include "Searchable.h"
#include "Matrix.h"
#include <mutex>
using namespace std;

extern mutex cacheMutex;

template<class Problem, class Solution>
class CacheManager {
 public:
  virtual bool isCached(Problem *p) = 0;
  virtual Solution getSolutionToProblem(Problem *p) = 0;
  virtual void saveSolutionForProblem(Problem *p, Solution s) = 0;
};

template<class T>
class FileCacheManager : public CacheManager<T, string> {
 private:
  map<string, string> problemStringToFileName;

 public:

  bool isCached(T *p) {

    //check if there is already a file with a solution.

    cacheMutex.lock();
    //Use the string casting - i implemented it on Searchable interfaces so every searchable has string representation.
    hash<string> hasher;
    string problemString = (string) *p;
    string name = to_string(hasher(problemString));
    cacheMutex.unlock();
    string path(name + ".txt");
    fstream file(path, ios::in);
    if (file && file.peek() != std::ifstream::traits_type::eof()) { //if exists
      file.close();
      return true;
    }

    //else :
    //check if exists.
    return this->problemStringToFileName.count(problemString);
  }
  string getSolutionToProblem(T *p) {
    cacheMutex.lock();
    //Use the string casting - i implemented it on Searchable interfaces so every searchable has string representation.
    string problemString = (string) *p;
    //get the name from the map.
    string name = this->problemStringToFileName[problemString];
    if (name.empty()) {
      hash<string> hasher;
      name = to_string(hasher(problemString));
    }
    cacheMutex.unlock();
    string path(name + ".txt");
    ifstream file(path);
    if (file) { // read the solution from the file.
      string obj;
      //read from the file into the object.
      obj.assign((istreambuf_iterator<char>(file)),
                 (istreambuf_iterator<char>()));
      file.close();
      return obj;
    } else {
      file.close();
      throw "an error trying to get solution from file";
    }
  }

  void saveSolutionForProblem(T *problem, string solution) {
    try {
      //create a pair of a problem string and a name with hasher of strings and put the pair in the map.
      cacheMutex.lock();
      hash<string> hasher;
      string prob = (string) *problem;
      string name = to_string(hasher(prob));
      auto p = make_pair(prob, name);
      problemStringToFileName.insert(p);
      cacheMutex.unlock();

      //save the file with the solution
      string path(name + ".txt");
      fstream file(path, std::ios::out);
      file << solution;
      file.close();

    } catch (const char *e) {
      throw "Error saving file of solution for problem";
    }
  }

};
