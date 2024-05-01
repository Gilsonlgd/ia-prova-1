#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

enum ORDER { UNORDERED, ORDERED };

class City {
private:
  string name;
  int heuristic;

public:
  City(string name, int heuristic) : name(name), heuristic(heuristic) {}

  string getName() const { return name; }

  int getHeuristic() const { return heuristic; }

  bool operator==(const City &c) const { return name == c.name; }
};

class State {
private:
  City origin;
  City destiny;
  int cost;
  int index;

  State *parent = nullptr; // used to reconstruct the final path

public:
  State(int index, City origin, City destiny, int cost, State *p)
      : origin(origin), destiny(destiny), index(index), cost(cost) {
    parent = p;
  }

  vector<State *> successors(bool ordered = false) {
    vector<State *> possibilities = {
        new State(2, City("a", 15), City("d", 14), 3, this),
        new State(1, City("d", 14), City("e", 15), 1, this),
        new State(3, City("a", 15), City("b", 7), 7, this),
        new State(4, City("b", 7), City("i", 5), 4, this),
        new State(5, City("i", 5), City("k", 0), 5, this),
        new State(3, City("a", 15), City("c", 6), 9, this),
        new State(8, City("c", 6), City("j", 3), 5, this),
        new State(7, City("j", 3), City("l", 4), 6, this),
        new State(6, City("l", 4), City("k", 0), 4, this),
        new State(9, City("b", 7), City("f", 7), 3, this),
        new State(10, City("f", 7), City("g", 8), 2, this),
        new State(11, City("g", 8), City("h", 5), 3, this),
    };

    vector<State *> succ;
    for (auto p : possibilities) {
      if (p->isValid(this)) {
        succ.push_back(p);
      }
    }

    return succ;
  };

  State *getParent() const { return parent; }

  int getCost() const { return cost; }
  int getHeuristic() const { return destiny.getHeuristic(); }
  int getRealCost() {
    if (parent == nullptr)
      return cost;

    int realCost = 0;
    State *current = this;

    while (current->parent != nullptr) {
      realCost += current->getCost();
      current = current->parent;
    }

    return realCost + destiny.getHeuristic();
  }

  bool isValid(State *previousState, bool ordered = false) const {
    return previousState->destiny == this->origin &&
           (ordered ? this->index > previousState->index : true);
  }

  bool isGoal() { return destiny.getName() == "k"; }

  string fingerprint() {
    return origin.getName() + destiny.getName() + "_" +
           to_string(getRealCost());
  }

  bool operator==(const State &s) const {
    return origin == s.origin && destiny == s.destiny;
  }

  bool operator!=(const State &s) const { return !(*this == s); }

  void print(int index) {
    cout << "(" << index << ")"
         << " " << origin.getName() << " -> " << destiny.getName()
         << " Custo Real: " << getRealCost() << endl;
  }
};

#endif