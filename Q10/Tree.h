#ifndef TREE_H
#define TREE_H

#include "State.h"
#include <cstddef>
#include <list>
#include <queue>

class Tree {
private:
  State *root;
  State *rightLeaf;
  State *leftLeaf;
  int value = 0;
  int count = 0;

  State *initializeTree(int depth, Type type, int value) {
    if (value == 1) {
      return new State(type == MAX ? -1 : 1, depth, type);
    }

    Type nextType = type == MAX ? MIN : MAX;
    vector<State *> children;
    for (int i = 1; i <= 3; i++) {
      if (value - i > 0) {
        children.push_back(initializeTree(depth + 1, nextType, value - i));
      }
    }

    State *newNode = new State(EMPTY, depth, type, nullptr, children);
    for (auto child : children) {
      child->setParent(newNode);
    }

    return newNode;
  }

public:
  Tree() { root = initializeTree(0, MAX, 5); }

  void minMaxPropagation() { minMax(root); }

  void alfaBetaLRPropagation() { alfaBetaLR(root); }

  void alfaBetaRLPropagation() { alfaBetaRL(root); }

  State *maxChild(vector<State *> children, int defaultValue = 0) {
    if (children.size() == 0) {
      return new State(defaultValue, 0, MIN);
    }

    State *max = children[0];
    for (auto child : children) {
      if (child->getValue() > max->getValue()) {
        max = child;
      }
    }
    return max;
  }

  State *minChild(vector<State *> children, int defaultValue = 0) {
    if (children.size() == 0) {
      return new State(defaultValue, 0, MAX);
    }

    State *min = children[0];
    for (auto child : children) {
      if (child->getValue() < min->getValue()) {
        min = child;
      }
    }
    return min;
  }

  State *minMax(State *node) {
    if (node->isLeaf()) {
      return node;
    }

    vector<State *> children;
    for (auto child : node->getChildren()) {
      children.push_back(minMax(child));
    }

    if (node->getType() == MAX) {
      node->setValue(maxChild(children)->getValue());
    } else {
      node->setValue(minChild(children)->getValue());
    }

    return node;
  }

  State *alfaBetaLR(State *node) {
    if (node->isLeaf()) {
      return node;
    }

    State *left = alfaBetaLR(node->getChildrenHead());
    vector<State *> right = {};

    if (node->getType() == MIN) {
      State *maxAncestor = node->getMaxAncestor(left->getValue());
      node->setValue(left->getValue());
      if (maxAncestor == nullptr) {
        for (auto child : node->getChildrenTail()) {
          right.push_back(alfaBetaLR(child));
        }

        int lValue = left->getValue();
        if (minChild(right, lValue)->getValue() < lValue) {
          node->setValue(minChild(right, lValue)->getValue());
        } else {
          node->setValue(left->getValue());
        }
      } else {
        for (auto child : node->getChildrenTail()) {
          child->setValue(PRUNED);
        }
        return node;
      }
    } else {
      State *minAncestor = node->getMinAncestor(left->getValue());
      node->setValue(left->getValue());
      if (minAncestor == nullptr) {
        for (auto child : node->getChildrenTail()) {
          right.push_back(alfaBetaLR(child));
        }

        int lValue = left->getValue();
        if (maxChild(right, lValue)->getValue() > lValue) {
          node->setValue(maxChild(right, lValue)->getValue());
        } else {
          node->setValue(left->getValue());
        }
      } else {
        for (auto child : node->getChildrenTail()) {
          child->setValue(PRUNED);
        }
        return node;
      }
    }

    return node;
  }

  State *alfaBetaRL(State *node) {
    if (node->isLeaf()) {
      return node;
    }

    State *right = alfaBetaRL(node->getChildrenBack());
    vector<State *> left = {};

    if (node->getType() == MIN) {
      State *maxAncestor = node->getMaxAncestor(right->getValue());
      node->setValue(right->getValue());
      if (maxAncestor == nullptr) {
        for (auto child : node->getChildrenTail(RL)) {
          left.push_back(alfaBetaRL(child));
        }

        int rValue = right->getValue();
        if (minChild(left, rValue)->getValue() < rValue) {
          node->setValue(minChild(left, rValue)->getValue());
        } else {
          node->setValue(right->getValue());
        }
      } else {
        for (auto child : node->getChildrenTail(RL)) {
          child->setValue(PRUNED);
        }
        return node;
      }
    } else {
      State *minAncestor = node->getMinAncestor(right->getValue());
      node->setValue(right->getValue());
      if (minAncestor == nullptr) {
        for (auto child : node->getChildrenTail(RL)) {
          left.push_back(alfaBetaRL(child));
        }

        int rValue = right->getValue();
        if (maxChild(left, rValue)->getValue() > rValue) {
          node->setValue(maxChild(left, rValue)->getValue());
        } else {
          node->setValue(right->getValue());
        }
      } else {
        for (auto child : node->getChildrenTail(RL)) {
          child->setValue(PRUNED);
        }
        return node;
      }
    }
    return node;
  }

  void printTree() { printTree(root, 0); }

  void printTree(State *node, int level) {
    if (node == nullptr) {
      return;
    }

    for (int i = node->getChildren().size() - 1; i > 0; i--) {
      printTree(node->getChildren()[i], level + 1);
    }
    for (int i = 0; i < level; i++) {
      cout << "   ";
    }
    cout << (node->getValue() > 0 ? " " : "") << node->getValue() << endl;
    printTree(node->getChildren()[0], level + 1);
  }
};

#endif