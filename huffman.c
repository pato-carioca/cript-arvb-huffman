#include "huffman.h"
#include "string.h"


THuff *criah(char *arq){
    FILE *f = fopen(arq, "rt");
    int r;
    float freq;
    char let, m, cv;
    r = fscanf(f, " %c %c %c %f", &let, &m, &cv, &freq);
    THuff *arv = NULL;
    while (r == 4){
        insereh_fim(arv, let, m, cv, freq); // criando a lista base inicial
        r = fscanf(f, " %c %c %c %f", &let, &m, &cv, &freq);
    }
    arv = ordenah(arv);
    while (!arv->prox){
        arv = criah_arv(arv);
    }
    return arv;
}

THuff *crianoh(char *c, char *m, char *cv, float f){
    THuff *novo = (THuff*)malloc(sizeof(THuff));
    novo->letra = c;
    novo->mm = m;
    novo->cv = cv;
    novo->freq = f;
    novo->prox = NULL;
    return novo;
}


THuff *insereh_fim(THuff *huff, char *c, char *m, char *cv, float f){
    THuff *p = huff, *novo;
    novo = crianoh(c, m, cv, f);
    if(!huff) huff = novo;
    else{
        while(p->prox) p = p->prox;
        p->prox = novo;
    }
    return huff;
}

THuff *ordenah(THuff *huff){
    THuff *p, *new;
    for(p = huff; p->prox; p = p->prox){
        THuff *q, *ant = p, *menor = p;
        for(q = p; q->prox; q = q->prox){
            if(menor->freq > q->prox->freq){
                ant = q; menor = q->prox;
            }
            if(menor != p){
                insereh_fim(new, menor->letra, menor->mm, menor->cv, menor->freq);
                removenoh(huff, menor->letra);
            }
        }
    }
    return new;
}

THuff *removenoh(THuff *l, char *c){ // só serve quando está sendo tratado como lista
    THuff *p = l, *ant = NULL;    // se utilizada depois da estruturação em árvore nós são perdidos
    while ((p) && (p->letra != c)){
        ant = p;
        p = p->prox;
    }
    if (!ant) // é o primeiro da lista
        l = l->prox;
    else ant->prox = p->prox;
    free(p);
    return l;
}

THuff *novaarvh(char *arq, THuff *velha) {
    liberah(velha);
    return criah(arq);
}

THuff *criah_arv (THuff *huff){ // cria pai de huff e huff->prox (dois menores) e insere-o ordenado
    if (!huff->prox) return huff; 
    THuff *a = huff, *b = huff->prox;
    THuff *novo;
    char *aux_letra = malloc(strlen(a->letra)+strlen(b->letra)+1);
    for(int i = 0; i < strlen(a->letra); i++){
        aux_letra += a->letra[i];
    }
    for(int i = 0; i < strlen(a->letra); i++){
        aux_letra += a->letra[i];
    }
    novo = crianoh(strcat(a->letra, b->letra), strcat(a->mm, b->mm), strcat(a->cv, b->cv), a->freq + b->freq);
    // TODO strcat junta strings, porém como estamos usando "a->letra" como "char *", então funciona como "a-letra[i]"
    // TODO Acho que uma solução é fazer um FOR para ir adicionando(concatenando) as letras de b em a.
    free(aux_letra);
    novo->esq = a;
    novo->dir = b; 
    huff = b->prox; // passa a ignorar a existencia de a e b
    huff = ins_ord_freq(huff, novo); /*
    if (b->prox && b->prox->prox) novo->prox = criah_arv(b->prox);
    else novo->prox = NULL; */
    return huff; //retorna lista ordenada com pai e ignorando os filhos
}
/* eu só juntei em escada, o melhor seria fazer mais parecida com uma abbb */

THuff *ins_ord_freq(THuff *lista, THuff *no){
    if (!lista) return no;
    if (no->freq <= lista->freq) {
        no->prox = lista;
        lista = no;
    }
    THuff *ant = lista;
    while (no->freq > ant->freq) ant = ant->prox;
    no->prox = ant->prox;
    ant->prox = no;
    return lista;
}

THuff *buscaletrah(THuff *arv, char *l) {
    if ((!arv) || (arv->letra == l)) return arv;
    THuff *resp = buscaletrah(arv->esq, l);
    if (resp) return resp;
    return buscaletrah(arv->dir, l);
}

THuff *alterafreqh(THuff *arv, char *l, float f) {
    THuff *p = buscaletrah(arv, l);
    if (!p) return arv;
    p->freq = f;
    return arv;
}

void liberah(THuff *arv) {
    if (arv) {
        liberah(arv->esq);
        liberah(arv->dir);
        free(arv);
    }
}
