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
  list<State *> prunedNodes = {};

  State *initializeTree(int depth, Type type) {
    if (depth == 0) {
      return new State(EMPTY, 0, type);
    }

    Type nextType = type == MAX ? MIN : MAX;
    State *left = initializeTree(depth - 1, nextType);
    State *right = initializeTree(depth - 1, nextType);

    State *node = new State(EMPTY, depth, type, nullptr, left, right);
    left->setParent(node);
    right->setParent(node);

    return node;
  }

  bool isFirstLeaf(queue<int> *values) {
    if (values->size() == 16) {
      return true;
    }
    return false;
  }

  void initializeLeafs(State *root, queue<int> *values) {
    if (root == nullptr) {
      return;
    }

    if (root->isLeaf()) {
      root->setValue(values->front());
      values->pop();
    }

    initializeLeafs(root->getLeft(), values);
    initializeLeafs(root->getRight(), values);
  }

public:
  Tree(int depth, queue<int> *leafValues) {
    root = initializeTree(depth - 1, MAX);
    initializeLeafs(root, leafValues);
  }

  void minMaxPropagation() { minMax(root); }

  void alfaBetaLRPropagation() { alfaBetaLR(root); }

  void alfaBetaRLPropagation() { alfaBetaRL(root); }

  State *minMax(State *node) {
    if (node->isLeaf()) {
      return node;
    }

    State *left = minMax(node->getLeft());
    State *right = minMax(node->getRight());

    if (node->getType() == MAX) {
      if (left->getValue() > right->getValue())
        node->setValue(left->getValue());
      else
        node->setValue(right->getValue());
    } else {
      if (left->getValue() < right->getValue())
        node->setValue(left->getValue());
      else
        node->setValue(right->getValue());
    }

    return node;
  }

  State *alfaBetaLR(State *node) {
    if (node->isLeaf()) {
      return node;
    }

    State *left = alfaBetaLR(node->getLeft());
    State *right = nullptr;

    if (node->getType() == MIN) {
      State *maxAncestor = node->getMaxAncestor(left->getValue());
      node->setValue(left->getValue());
      if (maxAncestor == nullptr) {
        right = alfaBetaLR(node->getRight());
        if (right->getValue() < left->getValue()) {
          node->setValue(right->getValue());
        } else {
          node->setValue(left->getValue());
        }
      } else {
        prunedNodes.push_back(node);
        node->getRight()->setValue(PRUNED);
        return node;
      }
    } else {
      State *minAncestor = node->getMinAncestor(left->getValue());
      node->setValue(left->getValue());
      if (minAncestor == nullptr) {
        right = alfaBetaLR(node->getRight());
        if (right->getValue() > left->getValue()) {
          node->setValue(right->getValue());
        } else {
          node->setValue(left->getValue());
        }
      } else {
        prunedNodes.push_back(node);
        node->getRight()->setValue(PRUNED);
        return node;
      }
    }

    return node;
  }

  State *alfaBetaRL(State *node) {
    if (node->isLeaf()) {
      return node;
    }

    State *right = alfaBetaRL(node->getRight());
    State *left = nullptr;

    if (node->getType() == MIN) {
      State *maxAncestor = node->getMaxAncestor(right->getValue());
      node->setValue(right->getValue());
      if (maxAncestor == nullptr) {
        left = alfaBetaRL(node->getLeft());
        if (left->getValue() < right->getValue()) {
          node->setValue(left->getValue());
        } else {
          node->setValue(right->getValue());
        }
      } else {
        prunedNodes.push_back(node);
        node->getLeft()->setValue(PRUNED);
        return node;
      }
    } else {
      State *minAncestor = node->getMinAncestor(right->getValue());
      node->setValue(right->getValue());
      if (minAncestor == nullptr) {
        left = alfaBetaRL(node->getLeft());
        if (left->getValue() > right->getValue()) {
          node->setValue(left->getValue());
        } else {
          node->setValue(right->getValue());
        }
      } else {
        prunedNodes.push_back(node);
        node->getLeft()->setValue(PRUNED);
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

    printTree(node->getRight(), level + 1);
    for (int i = 0; i < level; i++) {
      cout << "   ";
    }
    cout << node->getValue() << endl;
    printTree(node->getLeft(), level + 1);
  }

  void printPrunedNodes() {
    cout << prunedNodes.size();
    for (auto node : prunedNodes) {
      cout << "Pruned node: " << node->getValue() << endl;
    }
  }
};

#endif