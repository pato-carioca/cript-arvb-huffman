#include <stdio.h>
#include <stdlib.h>

typedef struct b{
    char *letra, *mm, *cv; // mm == m ou mm == M, m = minuscula, M = maiuscula
    int nch, folha; 
    float *freq; 
    struct b **filho; // cv = c ou cv = v, c = consoante, v = vogal
}TB;

TB *criab(char *arq, int t);
TB *crianob(/*char l, char m, char cv, float f, */int t);
TB *insereb(TB *arv, char l, char m, char cv, float f, int t);
TB *ins_nao_comp(TB *arv, char l, char m, char cv, float f, int t);
TB *divisao(TB *arv, int ind, TB *f, int t);
TB *retirab(TB *arv, char clas, int t, int *existe);
TB *retiraduplab(TB *arv, char clas1, char clas2, int t, int *existe);
TB *removemmb(TB *arv, char clas, int t);
TB *removecvb(TB *arv, char clas, int t);
TB *removeduplab(TB *arv, char clas1, char clas2, int t); 
TB *buscab(TB *arv, char c, char l);
TB *buscaduplab(TB *arv, char clas1, char clas2);
TB *alterafreqb(TB *arv, char l, float f);

float freqletrab(TB *arv, char l);

void imprimenob(TB *arv, char l);
void imprimearvb(TB *arv);
void liberab(TB *arv);
