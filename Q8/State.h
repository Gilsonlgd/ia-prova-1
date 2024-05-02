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
enum CostType { COST_1, REAL_COST, HEURISTIC_COST };

class Move {
public:
  int value;
  int xOrigin;
  int yOrigin;
  int xDest;
  int yDest;

  Move() {
    value = EMPTY;
    xOrigin = EMPTY;
    yOrigin = EMPTY;
    xDest = EMPTY;
    yDest = EMPTY;
  }

  Move(int value, int xOrigin, int yOrigin, int xDest, int yDest)
      : value(value), xOrigin(xOrigin), yOrigin(yOrigin), xDest(xDest),
        yDest(yDest) {}

  string toString() {
    return to_string(value) + ":(" + to_string(xOrigin) + "," +
           to_string(yOrigin) + ")->(" + to_string(xDest) + "," +
           to_string(yDest) + ")";
  }
};

class State {
private:
  vector<vector<int>> *board;
  State *parent = nullptr; // used to reconstruct the final path
  Move move;
  map<int, tuple<int, int>> goalPos;
  tuple<int, int> emptyPos;

  void initializeGoalPos() {
    goalPos[1] = make_tuple(0, 0);
    goalPos[2] = make_tuple(0, 1);
    goalPos[3] = make_tuple(0, 2);
    goalPos[4] = make_tuple(1, 2);
    goalPos[5] = make_tuple(2, 2);
    goalPos[6] = make_tuple(2, 1);
    goalPos[7] = make_tuple(2, 0);
    goalPos[8] = make_tuple(1, 0);

    goalPos[EMPTY] = make_tuple(1, 1);
  }

public:
  State(vector<vector<int>> *board, Move move, State *parent = nullptr)
      : parent(parent), board(board), move(move) {
    initializeGoalPos();
  }

  State(vector<vector<int>> *board, tuple<int, int> emptyPos, State *parent = nullptr)
      : parent(parent), board(board), emptyPos(emptyPos) {
    move = Move();
    initializeGoalPos();
  }

  State(State *parent = nullptr) : parent(parent) {
    board = new vector<vector<int>>({{1, 3, 4}, {8, 2, 5}, {7, 6, EMPTY}});
    emptyPos = make_tuple(2, 2);
    move = Move();

    initializeGoalPos();
  }

  vector<State *> successors() {
    vector<State *> succ;

    int i = get<0>(emptyPos);
    int j = get<1>(emptyPos);

    vector<tuple<int, int>> adjPositions = {
        {i, j - 1}, {i, j + 1}, {i - 1, j}, {i + 1, j}};

    for (auto pos : adjPositions) {
      int k = get<0>(pos);
      int l = get<1>(pos);
      if (k < 0 || k >= 3 || l < 0 || l >= 3) {
        continue;
      }

      if (move.xDest == k && move.yDest == l) {
        continue;
      }

      vector<vector<int>> *newBoard = new vector<vector<int>>(*board);
      Move move = Move((*newBoard)[k][l], k, l, i, j);

      (*newBoard)[i][j] = (*newBoard)[k][l];
      (*newBoard)[k][l] = EMPTY;

      State *newState = new State(newBoard, move, this);
      newState->emptyPos = make_tuple(k, l);

      succ.push_back(newState);
    }

    return succ;
  };

  State *getParent() const { return parent; }

  int getHeuristic() {
    int heuristic = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        int value = (*board)[i][j];
        if (value != EMPTY) {
          int targetI = get<0>(goalPos[value]);
          int targetJ = get<1>(goalPos[value]);

          heuristic += abs(i - targetI) + abs(j - targetJ);
        }
      }
    }
    return heuristic;
  }

  int getCost(CostType type = REAL_COST) {
    if (type == COST_1) {
      return 1;
    }

    if (type == REAL_COST) {
      int cost = 0;
      State *current = this;

      while (current->parent != nullptr) {
        cost += current->getCost(COST_1);
        current = current->parent;
      }

      return cost + getHeuristic();
    }

    return 0;
  }

  bool isGoal() {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if ((*board)[i][j] != (*board)[get<0>(goalPos[(*board)[i][j]])]
                                      [get<1>(goalPos[(*board)[i][j]])]) {
          return false;
        }
      }
    }
    return true;
  }

  string fingerprint(CostType type = REAL_COST) {
    if (type == HEURISTIC_COST) {
      return move.toString() + "-" + to_string(getHeuristic());
    }

    return move.toString() + "-" + to_string(getCost(type));
  }

  void print(int index, CostType type = REAL_COST) {
    cout << "(" << index << ")"
         << ": ";
    cout << move.toString() << " - " << getCost(type);
    cout << endl;
  }
};

#endif