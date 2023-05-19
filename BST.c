#include "BST.h"
NodeBST *nodNou(char *numeEchipa, float puncte){
    NodeBST *Nod;
    Nod = (NodeBST*)malloc(sizeof(NodeBST));
    Nod->numeEchipa=malloc(strlen(numeEchipa));
    strcpy(Nod->numeEchipa,numeEchipa);
    Nod->scorEchipa = puncte;
    Nod->left = Nod->right = NULL;
    return Nod;
}
NodeBST *insereazaBST(NodeBST *root, char *numeEchipa, float scorEchipa){
    if(root == NULL)
        return nodNou(numeEchipa, scorEchipa);
    if((scorEchipa < root->scorEchipa) || (scorEchipa == root->scorEchipa && strcmp(numeEchipa, root->numeEchipa) < 0))
        root->left = insereazaBST(root->left, numeEchipa, scorEchipa);
    else 
        root->right = insereazaBST(root->right, numeEchipa, scorEchipa);
    return root;
}
void inordineDRS(NodeBST *root, FILE *fisier){
    if(root){
        inordineDRS(root->right, fisier);
        fprintf(fisier, "%-34s-  %3.2f\n", root->numeEchipa, root->scorEchipa);
        inordineDRS(root->left, fisier);
    }
}
void freeBST(NodeBST **root) {
    if(*root == NULL) return;
    freeBST(&(*root)->left); freeBST(&(*root)->right);
    free(*root);
}