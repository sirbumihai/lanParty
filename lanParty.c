#include "echipe.h"
#include "BST.h"
#include "AVL.h"
int main(int num_arg, char *arg_strings[]){
    FILE *file;
    NodeBST *Top8 = NULL;
    AVL *AVLTop8 = NULL;
    Team Echipa;
    TeamNode *primaEchipa = NULL;
    int numarEchipe, Cerinta[6];
    file = fopen(arg_strings[1], "rt");
    fscanf(file,"%d %d %d %d %d", &Cerinta[1], &Cerinta[2], &Cerinta[3], &Cerinta[4], &Cerinta[5]);
    fclose(file);
    if(Cerinta[1]){
        file = fopen(arg_strings[2], "rt");
        fscanf(file, "%d", &numarEchipe);
        for(int i = 0; i < numarEchipe; ++i){
            citesteEchipa(&Echipa,file);
            insereazaNodEchipaInceput(&primaEchipa, Echipa);
        }
        fclose(file);
        afiseazaNumeEchipa(primaEchipa, arg_strings[3]);
    }
    if(Cerinta[2]){
        TeamNode *echipaNecalificata = gasireEchipaNecalificata(primaEchipa);
        int nouNumarEchipe=numarEchipe;
        nouNumarEchipe=gasireNumarEchipe(nouNumarEchipe);
        while (numarEchipe > nouNumarEchipe){
            stergeEchipa(&echipaNecalificata,&primaEchipa);
            echipaNecalificata = gasireEchipaNecalificata(primaEchipa);
            numarEchipe--;
        }
        afiseazaNumeEchipa(primaEchipa, arg_strings[3]);
    }
    if(Cerinta[3]){
        int numarRunda = 1;
        StackNode *castigatori = NULL, *pierzatori = NULL;
        Queue *Coada = creeazaRunde(primaEchipa);
        afiseazaListaRunda(Coada, arg_strings[3], numarRunda);
        creeazaStiva(Coada, &castigatori, &pierzatori);
        afiseazaValoriStiva(castigatori, arg_strings[3], numarRunda);
        stergePierzatori(&primaEchipa, &pierzatori);
        numarRunda=2;
        numarEchipe/=2;
            while(numarEchipe>1){
                Coada = creeazaRundeDinStiva(&castigatori);
                afiseazaListaRunda(Coada, arg_strings[3], numarRunda);
                creeazaStiva(Coada, &castigatori, &pierzatori);
                afiseazaValoriStiva(castigatori, arg_strings[3], numarRunda);
                stergePierzatori(&primaEchipa, &pierzatori);
                numarRunda++;
                numarEchipe/=2;
                if(numarEchipe == 8 && Cerinta[4]){
                    StackNode *curent = castigatori;
                    while(curent){
                        Top8 = insereazaBST(Top8, curent->numeEchipa, curent->puncteEchipa);
                        curent = curent->next;
                    }
                }
                if(numarEchipe == 8 && Cerinta[5])
                    creareAVL(Top8, &AVLTop8);
            }
    }
    if(Cerinta[4]){
        file = fopen(arg_strings[3], "at");
        fprintf(file,"\nTOP 8 TEAMS:\n");
        inordineDRS(Top8, file);
        freeBST(&Top8);
        fclose(file);
    }
    if(Cerinta[5]){
        file = fopen(arg_strings[3], "at");
        fprintf(file,"\nTHE LEVEL 2 TEAMS ARE: \n");
        fprintf(file,"%s\n", AVLTop8->right->right->numeEchipa);
        fprintf(file,"%s\n", AVLTop8->right->left->numeEchipa);
        fprintf(file,"%s\n", AVLTop8->left->right->numeEchipa);
        fprintf(file,"%s", AVLTop8->left->left->numeEchipa);
        fclose(file);
    }
    return 0;
}