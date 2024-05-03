#include <iostream>
using namespace std;

#include "Tree.h"
#include <queue>

/*TODO: A princípio, tá tudo certo. Só verificar se os outros estão funcionando normalmente.*/
/* Ver a 9 também. Estava usando > e < ao inves de >= <= no acesters*/
/* Desenhar as árvores do LR E RL*/
int main() {
  Tree *tree = new Tree();

  // tree->minMaxPropagation();
  // tree->alfaBetaLRPropagation();
  tree->alfaBetaRLPropagation();
  tree->printTree();

  return 0;
}