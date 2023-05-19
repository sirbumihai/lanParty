#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct NodeBST{
    struct NodeBST *left, *right;
    float scorEchipa;
    char *numeEchipa;
}NodeBST;
NodeBST *nodNou(char*, float);
NodeBST *insereazaBST(NodeBST*, char*, float);
void inordineDRS(NodeBST*, FILE*);
void freeBST(NodeBST**);