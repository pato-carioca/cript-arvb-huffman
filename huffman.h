#include <stdio.h>
#include <stdlib.h>

typedef struct huffman{
    char *letra, *mm, *cv;
    float freq;
    struct huffman *prox, *esq, *dir;
}THuff;

THuff *criah(char *arq);
THuff *insereh_fim(THuff *huff, char *c, char *m, char *cv, float f);
THuff *ordenah(THuff *huff);
THuff *removenoh(THuff *l, char *c);  // s� enquanto lista
THuff *novaarvh(char *arq, THuff *velha);
THuff *criah_arv (THuff *huff);
THuff *ins_ord_freq(THuff *lista, THuff *no);
THuff *crianoh(char *c, char *m, char *cv, float f);
THuff *buscaletrah(THuff *arv, char *l);
THuff *alterafreqh(THuff *arv, char *l, float f);

void liberah(THuff *arv);
