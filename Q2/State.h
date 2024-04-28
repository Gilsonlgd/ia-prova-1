#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Action { NONE, FILL_X, FILL_Y, EMPTY_X, EMPTY_Y, X_TO_Y, Y_TO_X };

/* Class: State
 * Description: Represents a state in the pitchers problem
 * The pitcher problem consists of two pitchers, X and Y, with capacities
 * pitcher_x and pitcher_y, respectively. The goal is to measure a certain
 * amount of water using only these two pitchers.
 * uma sequência de passos que deixe o jarro de 4 litros com exatamente 2 litros
 * de água. The actions that can be performed are:
 */
class State {
public:
  int pitcher_x;
  int pitcher_y;
  int GOAL = 2;
  Action action;

  State(int x, int y, Action a) : pitcher_x(x), pitcher_y(y), action(a) {}

  vector<State> successors() const {
    vector<State> succ;

    for (int x = 0; x <= 3; x++) {
      for (int y = 0; y <= 4; y++) {
        if (x < 3) {
          State next(3, this->pitcher_y, FILL_X);
          if (next.isValid())
            succ.push_back(next);
        }

        if (y < 4) {
          State next(this->pitcher_x, 4, FILL_Y);
          if (next.isValid())
            succ.push_back(next);
        }

        if (x > 0) {
          State next(0, this->pitcher_y, EMPTY_X);
          if (next.isValid())
            succ.push_back(next);
        }

        if (y > 0) {
          State next(this->pitcher_x, 0, EMPTY_Y);
          if (next.isValid())
            succ.push_back(next);
        }

        if (x > 0 && y < 4 && (x + y) <= 4) {
          State next(0, this->pitcher_x + this->pitcher_y, X_TO_Y);
          if (next.isValid())
            succ.push_back(next);
        }

        if (x > 0 && y < 4 && (x + y) > 4) {
          State next(this->pitcher_x + this->pitcher_y - 4, 4, X_TO_Y);
          if (next.isValid())
            succ.push_back(next);
        }

        if (x < 3 && y > 0 && (x + y) <= 3) {
          State next(this->pitcher_x + this->pitcher_y, 0, Y_TO_X);
          if (next.isValid())
            succ.push_back(next);
        }

        if (x < 3 && y > 0 && (x + y) > 3) {
          State next(3, this->pitcher_x + this->pitcher_y - 3, Y_TO_X);
          if (next.isValid())
            succ.push_back(next);
        }
      }
    }

    return succ;
  }

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