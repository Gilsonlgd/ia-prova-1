#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <string>
#include <vector>

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
private:
  Side left;     // estado inicial
  Side right;    // estado final
  bool boatLeft; // true se o barco está à esquerda
  State *parent = nullptr;

public:
  State(int ml, int cl, int mr, int cr, bool bl, State *p)
      : left(ml, cl), right(mr, cr), boatLeft(bl) {
    parent = p;
  }

  /*  Function: successors
   * Description: Generates all possible states that can be reached from the
   * current state
   */
  vector<State *> successors(int MAX_OPERATORS, int MIN_OPERATORS) {
    vector<State *> succ;

    if (this->boatLeft) {
      for (int m = 0; m <= MAX_OPERATORS; m++) {
        for (int c = 0; c <= MAX_OPERATORS; c++) {
          if (m + c >= MIN_OPERATORS &&
              m + c <= MAX_OPERATORS) { /* Move at most MAX_OPERATORS people */
            int n_ml = this->left.missionaries - m;
            int n_cl = this->left.cannibals - c;
            int n_mr = this->right.missionaries + m;
            int n_cr = this->right.cannibals + c;
            State *next = new State(n_ml, n_cl, n_mr, n_cr, false,
                                    this); /* Move boat to right */

            if (next->isValid()) {
              succ.push_back(next);
            }
          }
        }
      }
    } else { // Boat is on the right side
      for (int m = 0; m <= MAX_OPERATORS; m++) {
        for (int c = 0; c <= MAX_OPERATORS; c++) {
          if (m + c >= MIN_OPERATORS &&
              m + c <= MAX_OPERATORS) { // Move at most MAX_OPERATORS people
            int n_ml = this->left.missionaries + m;
            int n_cl = this->left.cannibals + c;
            int n_mr = this->right.missionaries - m;
            int n_cr = this->right.cannibals - c;
            State *next = new State(n_ml, n_cl, n_mr, n_cr, true,
                                    this); // Move boat to left

            if (next->isValid()) {
              succ.push_back(next);
            }
          }
        }
      }
    }

    return succ;
  }
  
  State *getParent() const { return parent; }

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

  string fingerprint() const {
    return to_string(left.missionaries) + to_string(left.cannibals) +
           to_string(right.missionaries) + to_string(right.cannibals) +
           to_string(boatLeft);
  }

  bool operator==(const State &other) const {
    return left.missionaries == other.left.missionaries &&
           left.cannibals == other.left.cannibals &&
           right.missionaries == other.right.missionaries &&
           right.cannibals == other.right.cannibals &&
           boatLeft == other.boatLeft;
  }

  bool operator!=(const State &other) const { return !(*this == other); }

  void print(int index) const {
    cout << index << " - "
         << "("
         << "m: " << left.missionaries << ", "
         << "c: " << left.cannibals << ", " << (boatLeft ? "left" : "right")
         << ", "
         << "m: " << right.missionaries << ", "
         << "c: " << right.cannibals << ")" << endl;
  }

  void print() const {
    cout << "("
         << "m: " << left.missionaries << ", "
         << "c: " << left.cannibals << ", " << (boatLeft ? "left" : "right")
         << ", "
         << "m: " << right.missionaries << ", "
         << "c: " << right.cannibals << ")" << endl;
  }
};

#endif