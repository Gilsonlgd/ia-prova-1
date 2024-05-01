#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Action {
  NONE,
  GOES,
  RETURNS,
  TAKES_WOLF,
  TAKES_SHEEP,
  TAKES_CABBAGE,
  BRINGS_WOLF,
  BRINGS_SHEEP,
  BRINGS_CABBAGE
};

enum Operator { LEFT, RIGHT };

class State {
private:
  Operator farmer;
  Operator wolf;
  Operator sheep;
  Operator cabbage;

  Action action;
  State *parent = nullptr; // used to reconstruct the final path

public:
  State(Action a, Operator f, Operator w, Operator s, Operator c, State *p)
      : farmer(f), wolf(w), sheep(s), cabbage(c), action(a) {
    parent = p;
  }

  vector<State *> successors() {
    vector<State *> succ;

    if (this->farmer == LEFT) {
      if (wolf != sheep && sheep != cabbage) {
        State *next = new State(GOES, RIGHT, wolf, sheep, cabbage, this);
        if (next->isValid())
          succ.push_back(next);
      }

      if (wolf == LEFT && sheep != cabbage) {
        State *next = new State(TAKES_WOLF, RIGHT, RIGHT, sheep, cabbage, this);
        if (next->isValid())
          succ.push_back(next);
      }

      if (sheep == LEFT) {
        State *next = new State(TAKES_SHEEP, RIGHT, wolf, RIGHT, cabbage, this);
        if (next->isValid())
          succ.push_back(next);
      }

      if (cabbage == LEFT && wolf != sheep) {
        State *next = new State(TAKES_CABBAGE, RIGHT, wolf, sheep, RIGHT, this);
        if (next->isValid())
          succ.push_back(next);
      }

    } else if (this->farmer == RIGHT) {
      if (wolf != sheep && sheep != cabbage) {
        State *next = new State(RETURNS, LEFT, wolf, sheep, cabbage, this);
        if (next->isValid())
          succ.push_back(next);
      }

      if (wolf == RIGHT && sheep != cabbage) {
        State *next = new State(BRINGS_WOLF, LEFT, LEFT, sheep, cabbage, this);
        if (next->isValid())
          succ.push_back(next);
      }

      if (sheep == RIGHT) {
        State *next = new State(BRINGS_SHEEP, LEFT, wolf, LEFT, cabbage, this);
        if (next->isValid())
          succ.push_back(next);
      }

      if (cabbage == RIGHT && wolf != sheep) {
        State *next = new State(BRINGS_CABBAGE, LEFT, wolf, sheep, LEFT, this);
        if (next->isValid())
          succ.push_back(next);
      }
    }

    return succ;
  };

  State *getParent() const { return parent; }

  bool isValid() const {
    if (wolf == sheep && farmer != wolf)
      return false;
    if (sheep == cabbage && farmer != sheep)
      return false;
    return true;
  }

  bool isGoal() const {
    return farmer == RIGHT && wolf == RIGHT && sheep == RIGHT &&
           cabbage == RIGHT;
  }

  string fingerprint() const {
    return to_string(farmer) + to_string(wolf) + to_string(sheep) +
           to_string(cabbage) + "_" + to_string(action);
  }

  bool operator==(const State &s) const {
    return farmer == s.farmer && wolf == s.wolf && sheep == s.sheep &&
           cabbage == s.cabbage;
  }

  bool operator!=(const State &s) const { return !(*this == s); }

  void print(int index) const {
    cout << index << " - ";
    cout << "F: " << farmer << " | ";
    cout << "W: " << wolf << " | ";
    cout << "S: " << sheep << " | ";
    cout << "C: " << cabbage << " | ";
    cout << "Action: ";
    printAction();
    cout << endl;
  }

  void printAction() const {
    switch (action) {
    case GOES:
      cout << "Goes";
      break;
    case RETURNS:
      cout << "Returns";
      break;
    case TAKES_WOLF:
      cout << "Takes Wolf";
      break;
    case TAKES_SHEEP:
      cout << "Takes Sheep";
      break;
    case TAKES_CABBAGE:
      cout << "Takes Cabbage";
      break;
    case BRINGS_WOLF:
      cout << "Brings Wolf";
      break;
    case BRINGS_SHEEP:
      cout << "Brings Sheep";
      break;
    case BRINGS_CABBAGE:
      cout << "Brings Cabbage";
      break;
    case NONE:
      cout << "NONE";
      break;
    }
  }
};

#endif