#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class State {
private:
  int id;
  char origin;
  char destiny;

  State *parent = nullptr; // used to reconstruct the final path

public:
  State(int id, char origin, char destiny, State *p)
      : id(id), origin(origin), destiny(destiny) {
    parent = p;
  }

  vector<State *> successors() {
    vector<State *> possibilities = {
        new State(1, 'a', 'b', this),  new State(2, 'a', 'b', this),
        new State(3, 'a', 'd', this),  new State(4, 'b', 'e', this),
        new State(5, 'b', 'f', this),  new State(6, 'c', 'g', this),
        new State(7, 'c', 'h', this),  new State(8, 'c', 'i', this),
        new State(9, 'd', 'j', this),  new State(10, 'e', 'k', this),
        new State(11, 'e', 'l', this), new State(12, 'g', 'm', this),
        new State(13, 'j', 'n', this), new State(14, 'j', 'o', this),
        new State(15, 'k', 'f', this), new State(16, 'l', 'h', this),
        new State(17, 'm', 'd', this), new State(18, 'o', 'a', this),
        new State(19, 'n', 'b', this),
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

  bool isValid(State *previousState) const {
    return previousState->destiny == this->origin &&
           this->id > previousState->id;
  }

  bool isGoal() { return destiny == 'j'; }

  string fingerprint() const { return to_string(id) + "_" + origin + destiny; }

  bool operator==(const State &s) const {
    return id == s.id && origin == s.origin && destiny == s.destiny;
  }

  bool operator!=(const State &s) const { return !(*this == s); }

  void print(int index) const {
    cout << "(" << index << ")"
         << " = " << to_string(id) + ", " + origin + " -> " + destiny << endl;
  }
};

#endif