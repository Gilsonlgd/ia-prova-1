#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Action { NONE, FILL_X, FILL_Y, EMPTY_X, EMPTY_Y, X_TO_Y, Y_TO_X };

class State {
private:
  int pitcher_x;
  int pitcher_y;
  int GOAL = 2;
  Action action;
  State *parent = nullptr; // used to reconstruct the final path

public:
  State(int x, int y, Action a, State *p)
      : pitcher_x(x), pitcher_y(y), action(a) {
    parent = p;
  }

  vector<State *> successors() {
    vector<State *> succ;

    for (int x = 0; x <= 3; x++) {
      for (int y = 0; y <= 4; y++) {
        if (x < 3) {
          State *next = new State(3, this->pitcher_y, FILL_X, this);
          if (next->isValid())
            succ.push_back(next);
        }

        if (y < 4) {
          State *next = new State(this->pitcher_x, 4, FILL_Y, this);
          if (next->isValid())
            succ.push_back(next);
        }

        if (x > 0) {
          State *next = new State(0, this->pitcher_y, EMPTY_X, this);
          if (next->isValid())
            succ.push_back(next);
        }

        if (y > 0) {
          State *next = new State(this->pitcher_x, 0, EMPTY_Y, this);
          if (next->isValid())
            succ.push_back(next);
        }

        if (x > 0 && y < 4 && (x + y) <= 4) {
          State *next =
              new State(0, this->pitcher_x + this->pitcher_y, X_TO_Y, this);
          if (next->isValid())
            succ.push_back(next);
        }

        if (x > 0 && y < 4 && (x + y) > 4) {
          State *next =
              new State(this->pitcher_x + this->pitcher_y - 4, 4, X_TO_Y, this);
          if (next->isValid())
            succ.push_back(next);
        }

        if (x < 3 && y > 0 && (x + y) <= 3) {
          State *next =
              new State(this->pitcher_x + this->pitcher_y, 0, Y_TO_X, this);
          if (next->isValid())
            succ.push_back(next);
        }

        if (x < 3 && y > 0 && (x + y) > 3) {
          State *next =
              new State(3, this->pitcher_x + this->pitcher_y - 3, Y_TO_X, this);
          if (next->isValid())
            succ.push_back(next);
        }
      }
    }

    return succ;
  }

  State *getParent() const { return parent; }

  bool isValid() const {
    return pitcher_x >= 0 && pitcher_y >= 0 && pitcher_x <= 3 && pitcher_y <= 4;
  }

  bool isGoal() const { return pitcher_y == GOAL; }

  bool operator==(const State &other) const {
    return pitcher_x == other.pitcher_x && pitcher_y == other.pitcher_y;
  }

  bool operator!=(const State &other) const { return !(*this == other); }

  void print() const { cout << "(" << pitcher_x << ", " << pitcher_y << ")"; }

  void printAction() const {
    switch (action) {
    case FILL_X:
      cout << "Fill X";
      break;
    case FILL_Y:
      cout << "Fill Y";
      break;
    case EMPTY_X:
      cout << "Empty X";
      break;
    case EMPTY_Y:
      cout << "Empty Y";
      break;
    case X_TO_Y:
      cout << "X to Y";
      break;
    case Y_TO_X:
      cout << "Y to X";
      break;
    case NONE:
      cout << "NONE";
      break;
    }
  }

  void print(int index) const {
    cout << index << " - ";
    print();
    cout << " - ";
    printAction();
    cout << endl;
  }

  string fingerprint() const {
    return to_string(pitcher_x) + to_string(pitcher_y) + "_" +
           to_string(action);
  }
};

#endif