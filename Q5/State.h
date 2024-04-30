#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum ORDER { UNORDERED, ORDERED };

class State {
private:
  string origin;
  string destiny;
  int cost;
  int index;

  State *parent = nullptr; // used to reconstruct the final path

public:
  State(int index, string origin, string destiny, int cost, State *p)
      : cost(cost), origin(origin), destiny(destiny), index(index) {
    parent = p;
  }

  vector<State *> successors(bool ordered = false) {
    vector<State *> possibilities = {
        new State(1, "a", "b", 1, this),  new State(2, "a", "c", 9, this),
        new State(3, "a", "d", 4, this),  new State(4, "b", "c", 7, this),
        new State(5, "b", "e", 6, this),  new State(6, "b", "f", 1, this),
        new State(7, "c", "f", 7, this),  new State(8, "d", "f", 4, this),
        new State(9, "d", "g", 5, this),  new State(10, "e", "h", 9, this),
        new State(11, "f", "h", 4, this), new State(12, "g", "h", 1, this),
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

  bool isValid(State *previousState, bool ordered = false) const {
    return previousState->destiny == this->origin &&
           (ordered ? this->index > previousState->index : true);
  }

  bool isGoal() { return destiny == "h"; }

  string fingerprint() const {
    return origin + destiny + "_" + to_string(cost);
  }

  bool operator==(const State &s) const {
    return cost == s.cost && origin == s.origin && destiny == s.destiny;
  }

  bool operator<(const State &s) const { return cost < s.cost; }

  bool operator>(const State &s) const { return cost > s.cost; }

  bool operator!=(const State &s) const { return !(*this == s); }

  void print(int index) const {
    cout << "(" << index << ")"
         << " = " << origin + " -> " + destiny + ", "
         << "Custo: " << to_string(cost) << endl;
  }
};

#endif