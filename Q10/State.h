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

#define EMPTY 0
#define PRUNED -2

enum Type { MAX, MIN };
enum Direction { LR, RL };

class State {
private:
  int value;
  int depth;
  State *parent = nullptr;
  vector<State *> children;
  int childrenCount = 3;
  Type type;

  void initializeChildren() {
    for (int i = 0; i < childrenCount; i++) {
      children.push_back(nullptr);
    }
  }

public:
  State(int value, int depth, Type type) {
    this->value = value;
    this->depth = depth;
    this->type = type;
    initializeChildren();
  }

  State(int value, int depth, Type type, State *parent) {
    this->value = value;
    this->depth = depth;
    this->type = type;
    this->parent = parent;
    initializeChildren();
  }

  State(int value, int depth, Type type, State *parent,
        vector<State *> children) {
    this->value = value;
    this->depth = depth;
    this->type = type;
    this->parent = parent;
    this->children = children;
  }

  int getValue() { return value; }

  int getDepth() { return depth; }

  State *getParent() { return parent; }

  vector<State *> getChildren() { return children; }

  State *getChildrenHead() { return children[0]; }

  State *getChildrenBack() { return children[children.size() - 1]; }

  vector<State *> getChildrenTail(Direction dir = LR) {
    vector<State *> tail;
    if (dir == LR) {
      for (int i = 1; i < children.size(); i++) {
        tail.push_back(children[i]);
      }
    } else {
      for (int i = 0; i < children.size() - 1; i++) {
        tail.insert(tail.begin(), children[i]);
      }
    }
    return tail;
  }

  State *getMaxAncestor(int greaterThan) {
    State *current = this;
    while (current->getParent() != nullptr) {
      if (current->getParent()->getType() == MAX &&
          current->getParent()->getValue() != EMPTY &&
          current->getParent()->getValue() != PRUNED &&
          current->getParent()->getValue() >= greaterThan) {
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
          current->getParent()->getValue() != PRUNED &&
          current->getParent()->getValue() <= lessThan) {
        return current->getParent();
      }
      current = current->getParent();
    }
    return nullptr;
  }

  Type getType() { return type; }

  void setParent(State *parent) { this->parent = parent; }

  void setChildren(vector<State *> children) { this->children = children; }

  void setValue(int value) { this->value = value; }

  bool isLeaf() {
    bool isLeaf = true;
    for (auto child : children) {
      if (child != nullptr) {
        isLeaf = false;
        break;
      }
    }
    return isLeaf;
  }

  bool isEmpty() { return value == EMPTY; }

  string fingerprint() { return to_string(value); }

  string toString() { return to_string(value); }

  void print() {
    cout << "Value: " << value << " Depth: " << depth << " Type: " << type
         << endl;
  }
};

#endif