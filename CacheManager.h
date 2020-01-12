
#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <list>
#include <fstream>

using namespace std;

template<class T>
class GenericCacheManager {
 private:
  unsigned int capacity_size;
  unordered_map<string, pair<T, list<string>::iterator>> cache;
  list<string> ls;
 public:

  void setCapacity(unsigned int capacity) {
    this->capacity_size = capacity;
  }

  bool isCached(T p) {
    return this->cache.count(p);
  }

  void insert(string key, T obj) {
    //took inspiration from :
    //https://www.geeksforgeeks.org/lru-cache-implementation/

    //Key already exists
    if (cache.count(key)) {
      auto it = cache[key].second;
      //erase it, and push to front.
      ls.erase(it);
      ls.push_front(key);
      auto front = ls.begin();
      auto p = make_pair(obj, front);
      //update the pair in the cache
      cache[key] = p;
    } else if (cache.size() == capacity_size) { // if cache is full
      //get rid of the lru.
      string back = ls.back();
      ls.pop_back();
      //find it in the cache and erase it.
      auto cache_item = cache.find(back);
      cache.erase(cache_item);
      //push to front in ls.
      ls.push_front(key);
      auto front = ls.begin();
      auto p1 = make_pair(obj, front);
      auto p2 = make_pair(key, p1);
      //insert the new pair of key and object to the cache.
      cache.insert(p2);
    } else {//if not full and not exists already.
      //push to front.
      ls.push_front(key);
      auto front = ls.begin();
      auto p1 = make_pair(obj, front);
      auto p2 = make_pair(key, p1);
      //insert the new pair of key and object to the cache.
      cache.insert(p2);
    }
    try {
      //write a new file or override the existing with the wanted object.
      string path(T::class_name + ":" + key + ".txt");
      fstream file(path, std::ios::out | std::ios::binary);
      file.write((char *) &obj, sizeof(obj));
      file.close();
    } catch (const char *e) {
      throw e;
    }
  }

  T get(string key) {
    if (cache.count(key)) { // Already in cache.
      auto it = cache[key].second;
      //erase it and push to front.
      ls.erase(it);
      ls.push_front(key);
      auto front = ls.begin();
      auto p = make_pair(cache[key].first, front);
      //update the need position in ls.
      cache[key] = p;
      //return the object
      return cache[key].first;
    }
    try {
      string path(T::class_name + ":" + key + ".txt");
      fstream file(path, std::ios::in | std::ios::binary);
      if (file) {
        //we use the item again so we need to insert it back into the cache.
        T obj;
        file.read((char *) &obj, sizeof(T)); //read from the file into the object.
        file.close();
        if (ls.empty()) {
          throw "an error";
        }
        //use the lru algorithem
        string back = ls.back();
        ls.pop_back();
        auto cache_item = cache.find(back);
        cache.erase(cache_item);
        ls.push_front(key);
        auto front = ls.begin();
        auto p1 = make_pair(obj, front);
        auto p2 = make_pair(key, p1);
        //insert the pair to the cache
        cache.insert(p2);
        return obj;
      } else {
        file.close();
        throw "an error";
      }

    } catch (const char *e) {
      throw e;
    }
  }

//  void foreach(const function<void(T &)> func) {
//    for (string key : ls) {
//      func(cache[key].first);
//    }
//  }

//  ~CacheManager<T>() {
//    if (!cache.empty())
//      cache.clear();
//    if (!ls.empty())
//      ls.clear();
//  }

};

template<class Problem, class Solution>
class CacheManager {
 public:
  virtual bool isCached(Problem p) = 0;
  virtual Solution getSolutionToProblem(Problem p) = 0;
  virtual void saveSolutionForProblem(Problem p, Solution s) = 0;
};

template<class Solution>
class FileCacheManager : public CacheManager<string, Solution> {
 private:
  GenericCacheManager<Solution> stringGCM;
 public:
  FileCacheManager(unsigned int capacity) {
    this->stringGCM.setCapacity(capacity);
  }
  bool isCached(string p);
  Solution getSolutionToProblem(string p);
  void saveSolutionForProblem(string problem, Solution solution);

};


