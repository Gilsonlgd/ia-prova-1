#ifndef STATE_H
#define STATE_H

#include <iostream>
using namespace std;

class Side {
public:
  int missionaries;
  int cannibals;

  Side(int m, int c) {
    missionaries = m;
    cannibals = c;
  }

  bool operator==(const Side &s) const {
    return missionaries == s.missionaries && cannibals == s.cannibals;
  }
};

class State {
public:
  Side left;      // estado inicial
  Side right;     // estado final
  bool boat_left; // true se o barco está à esquerda

  State(int ml, int cl, int mr, int cr, bool bl)
      : left(ml, cl), right(mr, cr), boat_left(bl) {}

  bool isValid() const {
    if (left.missionaries < 0 || left.cannibals < 0 || right.missionaries < 0 ||
        right.cannibals < 0)
      return false;
    if (left.missionaries != 0 && left.missionaries < left.cannibals)
      return false;
    if (right.missionaries != 0 && right.missionaries < right.cannibals)
      return false;
    return true;
  }

  bool isGoal() const { return left.missionaries == 0 && left.cannibals == 0; }

  bool operator==(const State &other) const {
    return left.missionaries == other.left.missionaries &&
           left.cannibals == other.left.cannibals &&
           right.missionaries == other.right.missionaries &&
           right.cannibals == other.right.cannibals &&
           boat_left == other.boat_left;
  }

  bool operator!=(const State &other) const { return !(*this == other); }

  void print(int index) const {
    cout << index << " - "
         << "("
         << "m: " << left.missionaries << ", "
         << "c: " << left.cannibals << ", " << (boat_left ? "left" : "right")
         << ", "
         << "m: " << right.missionaries << ", "
         << "c: " << right.cannibals << ")" << endl;
  }

  void print() const {
    cout << "("
         << "m: " << left.missionaries << ", "
         << "c: " << left.cannibals << ", " << (boat_left ? "left" : "right")
         << ", "
         << "m: " << right.missionaries << ", "
         << "c: " << right.cannibals << ")" << endl;
  }
};

#endif