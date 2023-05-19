#include "BST.h"
#include "AVL.h"
int maxim(int nr1, int nr2) {return (nr1>nr2) ? nr1 : nr2;}
int inaltimeNod(AVL *root){
    if(root == NULL) return -1;
    return root->height;
}
AVL *leftRotation(AVL *N){
    AVL *A = N->right;
    AVL *AUX = A->left;
    A->left = N;
    N->right = AUX;
    N->height = maxim(inaltimeNod(N->left), inaltimeNod(N->right)) + 1;
    A->height = maxim(inaltimeNod(A->left), inaltimeNod(A->right)) + 1;
    return A;
}
AVL *rightRotation(AVL *N){
    AVL *A = N->left;
    AVL *AUX = A->right;
    A->right = N;
    N->left = AUX;
    N->height = maxim(inaltimeNod(N->left), inaltimeNod(N->right)) + 1;
    A->height = maxim(inaltimeNod(A->left), inaltimeNod(A->right)) + 1;
    return A;
}
AVL *RLRotation(AVL *N){
    N->right = rightRotation(N->right);
    return leftRotation(N);
}
AVL *LRRotation(AVL *N){
    N->left = leftRotation(N->left);
    return rightRotation(N);
}
AVL *insereazaAVL(AVL *Node, char *numeEchipa, float scorEchipa){
    if(Node == NULL){
        Node = (AVL*)malloc(sizeof(AVL));
        Node->scorEchipa = scorEchipa;
        Node->numeEchipa=malloc(strlen(numeEchipa));
        strcpy(Node->numeEchipa,numeEchipa);
        Node->left = Node->right = NULL;
        Node->height = 0;
        return Node;
    }
    if((scorEchipa < Node->scorEchipa) || (scorEchipa == Node->scorEchipa && strcmp(numeEchipa, Node->numeEchipa) < 0))
        Node->left = insereazaAVL(Node->left, numeEchipa, scorEchipa);
    else
        Node->right = insereazaAVL(Node->right, numeEchipa, scorEchipa);
    Node->height = maxim(inaltimeNod(Node->left), inaltimeNod(Node->right)) + 1;
    int k = inaltimeNod(Node->left) - inaltimeNod(Node->right);
    if(k > 1 && ((scorEchipa < Node->left->scorEchipa) || (scorEchipa == Node->left->scorEchipa && strcmp(numeEchipa, Node->left->numeEchipa) < 0)) )
        return rightRotation(Node);
    if(k > 1 && ((scorEchipa > Node->left->scorEchipa) || (scorEchipa == Node->left->scorEchipa && strcmp(numeEchipa, Node->left->numeEchipa) > 0)) )
        return RLRotation(Node);
    if(k < -1 && ((scorEchipa > Node->right->scorEchipa) || (scorEchipa == Node->right->scorEchipa && strcmp(numeEchipa, Node->right->numeEchipa) > 0)) )
        return LRRotation(Node);
    if(k < -1 && ((scorEchipa < Node->right->scorEchipa) || (scorEchipa == Node->right->scorEchipa && strcmp(numeEchipa, Node->right->numeEchipa) < 0)) )
        return leftRotation(Node);
    return Node;     
}
void creareAVL(NodeBST *Nod, AVL **AVL){
    if(Nod){
        creareAVL(Nod->right, AVL);
        *AVL = insereazaAVL(*AVL, Nod->numeEchipa, Nod->scorEchipa);
        creareAVL(Nod->left, AVL);
    }
}