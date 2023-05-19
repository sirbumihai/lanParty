#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Player{
    int points;
    char *firstName, *secondName;
}Player;
typedef struct NodJucator{
    struct NodJucator *nextPlayer;
    Player Jucator;
}NodJucator;
typedef struct Team{
    char *numeEchipa;
    int numarJucatori;
    float score;
    NodJucator *firstPlayer;
}Team;
typedef struct TeamNode{
    Team Echipa;
    struct TeamNode *nextTeam;
}TeamNode;
typedef struct Element{
    struct Element *next;
    float puncteEchipa1, puncteEchipa2;
    char *numeEchipa1, *numeEchipa2;
}Node;
typedef struct ElementStiva{
    char *numeEchipa;
    float puncteEchipa;
    struct ElementStiva *next;
}StackNode;
typedef struct Coada{
    Node *rear, *front;
}Queue;
int isEmpty(Queue*);
int isEmptyStack(StackNode*);
void copieJucator(Player*, Player*);
void stergeListaJucatori(NodJucator**);
void insereazaJucatorInceput(NodJucator**, Player);
void pop(StackNode**);
void push(StackNode**, char*, float);
Queue *creeazaCoada();
void deQueue(Queue*);
void creeazaStiva(Queue*, StackNode**, StackNode **);
void afiseazaValoriStiva(StackNode*, char*, int);
void enQueue(Queue*, char*, char*, float, float);
void creareEchipa(Team*);
void creareNodEchipa(TeamNode**);
void strcpyEchipa(Team*, Team*);
void afiseazaNumeEchipa(TeamNode*, char*);
void citesteEchipa(Team*, FILE*);
void insereazaNodEchipaInceput(TeamNode**, Team);
int gasireNumarEchipe(unsigned int);
TeamNode *gasireEchipaNecalificata(TeamNode*);
void stergeEchipa(TeamNode**,TeamNode**);
void stergeEchipaDupaNume(TeamNode**, char*);
Queue *creeazaRunde(TeamNode*);
Queue *creeazaRundeDinStiva(StackNode**);
void afiseazaListaRunda(Queue*, char*, int);
void stergePierzatori(TeamNode**, StackNode**);