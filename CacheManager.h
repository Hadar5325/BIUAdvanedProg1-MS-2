
#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <list>
#include <fstream>
#include "Searchable.h"
#include "Matrix.h"
using namespace std;

template<class Problem, class Solution>
class CacheManager {
 public:
  virtual bool isCached(Problem *p) = 0;
  virtual Solution getSolutionToProblem(Problem *p) = 0;
  virtual void saveSolutionForProblem(Problem *p, Solution s) = 0;
};

//template<class T>
//class SearchableProblemFileCacheManager : public CacheManager<Searchable<T>, string> {
// protected:
//  map<string, string> problemStringToFileName;
// public:
//
//  virtual bool isCached(Searchable<T> *p) = 0;
//  virtual string getSolutionToProblem(Searchable<T> *p) = 0;
//  virtual void saveSolutionForProblem(Searchable<T> *p, string s) = 0;
//};

template<class T>
class MatrixProblemFileCacheManager : public CacheManager<Matrix<T>, string> {
 private:
  map<string, string> problemStringToFileName;

 public:

  bool isCached(Matrix<T> *p) {
    string problemString = p->to_string();
    return this->problemStringToFileName.count(problemString);
  }

  string getSolutionToProblem(Matrix<T> *p) {
    string str = p->to_string();
    string name = this->problemStringToFileName[str];
    string path(name + ".txt");
    fstream file(path, std::ios::in | std::ios::binary);
    if (file) {
      string obj;
      file.read((char *) &obj, sizeof(string)); //read from the file into the object.
      file.close();
      return obj;
    } else {
      file.close();
      throw "an error";
    }
  }

  void saveSolutionForProblem(Matrix<T> *problem, string solution) {
    try {
      //create a pair of a problem string and a name with hasher of strings and put the pair in the map.
      hash<string> hasher;
      string prob = problem->to_string();
      string name = to_string(hasher(prob));
      this->problemStringToFileName.insert(make_pair(prob, name));

      //save the file with the solution
      string path(name + ".txt");
      fstream file(path, std::ios::out | std::ios::binary);
      file.write((char *) &solution, sizeof(solution));
      file.close();
    } catch (const char *e) {
      throw "Error saving file of solution for problem";
    }
  }

};


