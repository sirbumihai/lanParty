#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct AVL{
    struct AVL *left, *right;
    char *numeEchipa;
    float scorEchipa;
    int height;
}AVL;
int maxim(int, int);
int inaltimeNod(AVL*);
AVL *leftRotation(AVL*);
AVL *rightRotation(AVL*);
AVL *RLRotation(AVL*);
AVL *LRRotation(AVL*);
AVL *insereazaAVL(AVL*, char*, float);
void creareAVL(NodeBST*, AVL**);
