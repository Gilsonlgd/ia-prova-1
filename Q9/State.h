#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

#define EMPTY -1

enum Type { MAX, MIN };

class State {
private:
  int value;
  int depth;
  State *parent = nullptr;
  State *left = nullptr;
  State *right = nullptr;
  Type type;

public:
  State(int value, int depth, Type type) {
    this->value = value;
    this->depth = depth;
    this->type = type;
  }

  State(int value, int depth, Type type, State *parent) {
    this->value = value;
    this->depth = depth;
    this->type = type;
    this->parent = parent;
  }

  State(int value, int depth, Type type, State *parent, State *left,
        State *right) {
    this->value = value;
    this->depth = depth;
    this->type = type;
    this->parent = parent;
    this->left = left;
    this->right = right;
  }

  int getValue() { return value; }

  int getDepth() { return depth; }

  State *getParent() { return parent; }

  State *getLeft() { return left; }

  State *getRight() { return right; }

  State *getMaxAncestor(int greaterThan) {
    State *current = this;
    while (current->getParent() != nullptr) {
      if (current->getParent()->getType() == MAX &&
          current->getParent()->getValue() != EMPTY &&
          current->getParent()->getValue() > greaterThan) {
        return current->getParent();
      }
      current = current->getParent();
    }
    return nullptr;
  }

  State *getMinAncestor(int lessThan) {
    State *current = this;
    while (current->getParent() != nullptr) {
      if (current->getParent()->getType() == MIN &&
          current->getParent()->getValue() != EMPTY &&
          current->getParent()->getValue() < lessThan){
        return current->getParent();
      }
      current = current->getParent();
    }
    return nullptr;
  }

  Type getType() { return type; }

  void setParent(State *parent) { this->parent = parent; }

  void setLeft(State *left) { this->left = left; }

  void setRight(State *right) { this->right = right; }

  void setValue(int value) { this->value = value; }

  bool isGoal() { return value == 0; }

  bool isLeaf() { return left == nullptr && right == nullptr; }

  bool isEmpty() { return value == EMPTY; }

  string fingerprint() { return to_string(value); }

  string toString() { return to_string(value); }

  void print() {
    cout << "Value: " << value << " Depth: " << depth << " Type: " << type
         << endl;
  }
};

#endif