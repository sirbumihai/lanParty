#include "echipe.h"
int isEmpty(Queue *Coada) {return (Coada->front == NULL);}
int isEmptyStack(StackNode *stackNode) {return (stackNode == NULL);}
void copieJucator(Player *Jucator1, Player *Jucator2){
    Jucator1->firstName=malloc(strlen(Jucator2->firstName)+1);Jucator1->secondName=malloc(strlen(Jucator2->secondName)+1);
    strcpy(Jucator1->firstName,Jucator2->firstName);strcpy(Jucator1->secondName,Jucator2->secondName);
    Jucator1->points = Jucator2->points;
}
void stergeListaJucatori(NodJucator **primulJucator){
    NodJucator *stergeJucator;
    while(*primulJucator){
        stergeJucator = (*primulJucator);
        (*primulJucator) = (*primulJucator)->nextPlayer;
        free(stergeJucator);
    }
    (*primulJucator) = NULL;
}
void insereazaJucatorInceput(NodJucator **primulJucator, Player Jucator){
    NodJucator *JucatorNou;
    JucatorNou = malloc(sizeof(NodJucator));
    (*JucatorNou).Jucator.firstName = NULL; (*JucatorNou).Jucator.secondName = NULL;
    (*JucatorNou).Jucator.points = 0;
    (*JucatorNou).nextPlayer = NULL;
    copieJucator(&JucatorNou->Jucator, &Jucator);
    if((*primulJucator) == NULL)
        (*primulJucator) = JucatorNou;
    else{
        JucatorNou->nextPlayer = (*primulJucator);
        (*primulJucator) = JucatorNou;
    }
}
void pop(StackNode **top){
    StackNode *stergeNod;
    stergeNod = (*top);
    (*top) = (*top)->next;
    free(stergeNod);
}
void push(StackNode **stackNode, char *numeEchipa, float puncteEchipa){
    StackNode *nodNou;
    nodNou = (StackNode*)malloc(sizeof(StackNode));
    nodNou->numeEchipa=malloc(strlen(numeEchipa)+1);
    strcpy(nodNou->numeEchipa,numeEchipa);
    nodNou->puncteEchipa = puncteEchipa;
    nodNou->next = (*stackNode);
    (*stackNode) = nodNou;
}
Queue *creeazaCoada(){
    Queue *coada; coada = (Queue*)malloc(sizeof(Queue));
    if(coada == NULL) return NULL;
    coada->rear = NULL;coada->front = NULL;
    return coada;
}
void deQueue(Queue *Coada){
    Node *stergeNod;
    if(!isEmpty(Coada)){
        stergeNod = Coada->front;
        Coada->front = Coada->front->next;
        free(stergeNod);
    }
}
void creeazaStiva(Queue *Coada, StackNode **castigatori, StackNode **pierzatori){
    (*castigatori) = (*pierzatori) = NULL;
    while(!isEmpty(Coada)){
        if(Coada->front->puncteEchipa1 > Coada->front->puncteEchipa2){
            push(castigatori, Coada->front->numeEchipa1, Coada->front->puncteEchipa1 + 1);
            push(pierzatori, Coada->front->numeEchipa2, Coada->front->puncteEchipa2);
        } else {
            push(castigatori, Coada->front->numeEchipa2, Coada->front->puncteEchipa2 + 1);
            push(pierzatori, Coada->front->numeEchipa1, Coada->front->puncteEchipa1);
        }
        deQueue(Coada);
    }
}
void afiseazaValoriStiva(StackNode *Element, char *numeFisier, int rundaNumar){
    FILE *fisier;
    fisier = fopen(numeFisier, "at");
    fprintf(fisier, "\nWINNERS OF ROUND NO:%d\n", rundaNumar);
    while(Element){
        //if((int)(Element->puncteEchipa*1000)%10==5) fprintf(fisier,"%-34s-  %3.2f\n", Element->numeEchipa, Element->puncteEchipa-0.01); else 
        fprintf(fisier,"%-34s-  %3.2f\n", Element->numeEchipa, Element->puncteEchipa);
        Element = Element->next;
    }
    fclose(fisier);
}
void enQueue(Queue *Coada, char *numeEchipa1, char *numeEchipa2, float puncteEchipa1, float puncteEchipa2){
    Node *nodNou; nodNou = (Node*)malloc(sizeof(Node));
    nodNou->numeEchipa1=malloc(strlen(numeEchipa1)+1);nodNou->numeEchipa2=malloc(strlen(numeEchipa2)+1);
    strcpy(nodNou->numeEchipa1,numeEchipa1);strcpy(nodNou->numeEchipa2,numeEchipa2);
    nodNou->puncteEchipa1 = puncteEchipa1; nodNou->puncteEchipa2 = puncteEchipa2;
    nodNou->next = NULL;
    if(isEmpty(Coada)) Coada->front = nodNou;
    if(Coada->rear == NULL)
        Coada->rear = nodNou;
    else{
        Coada->rear->next = nodNou;
        Coada->rear = nodNou;
    }
}
void creareEchipa(Team *Echipa){
    Echipa->numeEchipa = NULL;
    Echipa->numarJucatori = 0; Echipa->score = 0;
    Echipa->firstPlayer = malloc(sizeof(NodJucator));
    (*Echipa->firstPlayer).Jucator.firstName = NULL; (*Echipa->firstPlayer).Jucator.secondName = NULL;
    (*Echipa->firstPlayer).Jucator.points = 0;
    (*Echipa->firstPlayer).nextPlayer = NULL;
}
void creareNodEchipa(TeamNode **NodEchipa){
    (*NodEchipa) = malloc(sizeof(TeamNode));
    creareEchipa(&(*NodEchipa)->Echipa);
    (*NodEchipa)->nextTeam = NULL;
}
void strcpyEchipa(Team *Echipa1, Team *Echipa2){
    Echipa1->numeEchipa=malloc(strlen(Echipa2->numeEchipa)+1);
    strcpy(Echipa1->numeEchipa,Echipa2->numeEchipa);
    Echipa1->firstPlayer = Echipa2->firstPlayer; Echipa1->numarJucatori = Echipa2->numarJucatori; Echipa1->score = Echipa2->score;
}
void afiseazaNumeEchipa(TeamNode *primaEchipa, char *numeFisier){
    FILE* fisier;
    fisier = fopen(numeFisier, "wt");
    TeamNode *ParcurgeEchipe = primaEchipa;
    while(ParcurgeEchipe){
        fprintf(fisier, "%s\n", ParcurgeEchipe->Echipa.numeEchipa);
        ParcurgeEchipe = ParcurgeEchipe->nextTeam;
    }
    fclose(fisier);
}
void citesteEchipa(Team *Echipa, FILE *file){
    char buff[50]; Player Jucator;
    Jucator.firstName = NULL; Jucator.secondName = NULL;
    Jucator.points = 0;
    fscanf(file, "%d ", &Echipa->numarJucatori);
    fgets(buff, 50, file);
    buff[strlen(buff)-1] = '\0';
    if(buff[strlen(buff)-1] ==' ') buff[strlen(buff)-1] ='\0';
    Echipa->numeEchipa = (char*)malloc(strlen(buff)+1); strcpy(Echipa->numeEchipa, buff);
    Echipa->firstPlayer = NULL; Echipa->score = 0;
    for(int i=0; i < Echipa->numarJucatori; i++){
        fscanf(file, "%s", buff); Jucator.secondName = (char*)malloc(strlen(buff)+1); strcpy(Jucator.secondName, buff);
        fscanf(file, "%s", buff); Jucator.firstName = (char*)malloc(strlen(buff)+1); strcpy(Jucator.firstName, buff); 
        fscanf(file, "%d", &Jucator.points);
        insereazaJucatorInceput(&Echipa->firstPlayer, Jucator);
        Echipa->score += Jucator.points;
    }
    Echipa->score /= Echipa->numarJucatori;
}
void insereazaNodEchipaInceput(TeamNode **primaEchipa, Team Echipa){
    TeamNode *echipaNoua;
    creareNodEchipa(&echipaNoua);
    strcpyEchipa(&echipaNoua->Echipa, &Echipa);
    if((*primaEchipa) == NULL) 
        (*primaEchipa) = echipaNoua;
    else{
        echipaNoua->nextTeam = (*primaEchipa);
        (*primaEchipa) = echipaNoua;
    }
}
int gasireNumarEchipe(unsigned int numar){
    int rezultat = 1;
    for (int i = 0; i < 8 * sizeof(unsigned int); i++) {
        int putere2 = 1 << i;
        if (putere2 > numar) break;
        rezultat = putere2;
    }
    return rezultat;
}
TeamNode *gasireEchipaNecalificata(TeamNode *primaEchipa) {
    float aux = primaEchipa->Echipa.score;
    TeamNode *echipaEliminata = primaEchipa;
    while(primaEchipa && primaEchipa->nextTeam){
        if(aux > primaEchipa->nextTeam->Echipa.score){
            aux = primaEchipa->nextTeam->Echipa.score; 
            echipaEliminata = primaEchipa;
        }
    primaEchipa = primaEchipa->nextTeam;
    }
    return echipaEliminata;
}
void stergeEchipa(TeamNode **nodSters,TeamNode **primulSters){
    if(((*nodSters) != (*primulSters)) || ((*nodSters) == (*primulSters) && (*primulSters)->nextTeam->Echipa.score < (*primulSters)->Echipa.score)){
        TeamNode *sterge = (*nodSters)->nextTeam;
        (*nodSters)->nextTeam = sterge->nextTeam;
        stergeListaJucatori(&sterge->Echipa.firstPlayer);
        free(sterge);
    } else {
        TeamNode *sterge = (*primulSters);
        (*primulSters) = sterge->nextTeam;
        stergeListaJucatori(&sterge->Echipa.firstPlayer);
        free(sterge);
    }
}
void stergeEchipaDupaNume(TeamNode **primaEchipa, char *numeEchipa){
    TeamNode *nodSters, *echipaCurenta = (*primaEchipa);
    if(strcmp((*primaEchipa)->Echipa.numeEchipa, numeEchipa) == 0){
        nodSters = (*primaEchipa);
        (*primaEchipa) = (*primaEchipa)->nextTeam;
        stergeListaJucatori(&nodSters->Echipa.firstPlayer);
        free(nodSters);
        return;
    }
    while(echipaCurenta && echipaCurenta->nextTeam){
        if(strcmp(echipaCurenta->nextTeam->Echipa.numeEchipa, numeEchipa) == 0){
            nodSters = echipaCurenta->nextTeam;
            echipaCurenta->nextTeam = echipaCurenta->nextTeam->nextTeam;
            stergeListaJucatori(&nodSters->Echipa.firstPlayer);
            free(nodSters);
        }
        echipaCurenta = echipaCurenta->nextTeam;
    }
}
Queue *creeazaRunde(TeamNode *listaEchipa){
    Queue *coadaRunda = creeazaCoada(); TeamNode *echipa2;
    while(listaEchipa && listaEchipa->nextTeam){
        echipa2 = listaEchipa->nextTeam;
        enQueue(coadaRunda, listaEchipa->Echipa.numeEchipa, echipa2->Echipa.numeEchipa, listaEchipa->Echipa.score, echipa2->Echipa.score);
        listaEchipa = listaEchipa->nextTeam->nextTeam;
    }
    return coadaRunda;
}
Queue *creeazaRundeDinStiva(StackNode **listaEchipa){
    Queue *coadaRunda = creeazaCoada();
    while(!isEmptyStack(*listaEchipa)){
        enQueue(coadaRunda, (*listaEchipa)->numeEchipa, (*listaEchipa)->next->numeEchipa, (*listaEchipa)->puncteEchipa, (*listaEchipa)->next->puncteEchipa);
        pop(listaEchipa); pop(listaEchipa);
    }
    return coadaRunda;    
}
void afiseazaListaRunda(Queue *Coada, char *numeFisier, int numarRunde){
    Node *primulJoc = Coada->front; FILE *fisier;
    fisier = fopen(numeFisier, "at");
    fprintf(fisier, "\n--- ROUND NO:%d\n", numarRunde);
    while(primulJoc){
        fprintf(fisier, "%-33s-%33s\n", primulJoc->numeEchipa1, primulJoc->numeEchipa2);
        primulJoc = primulJoc->next;
    }
    fclose(fisier);
}
void stergePierzatori(TeamNode **primaEchipa, StackNode **Stiva){
    while(!isEmptyStack(*Stiva)){
        stergeEchipaDupaNume(primaEchipa, (*Stiva)->numeEchipa);
        pop(Stiva);
    }
}