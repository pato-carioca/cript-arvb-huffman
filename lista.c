#include "lista.h"

TL *crial(char c, float f){
    TL *novo = (TL*)malloc(sizeof(TL));
    novo->letra = c;
	novo->freq = f;
    novo->prox = NULL;
}

TL *inserel_fim(TL *l, char c, float f){    
    TL *p = l, *novo = crial(c, f);
    if (!l) l = novo; 
    else{
        while (p->prox) p = p->prox;
        p->prox = novo;
    }
    return l;
}

TL *inserel_freq_cres(TL *l, float f) { // f entra na primeira freq negativa
	TL *p = l;
	while (p->freq != -0.1) p = p->prox;
	p->freq = f;
	return l;
}

TL *removeprimeirol(TL *lista) {
	TL *p = lista; 
	if (lista) lista = lista->prox;
	free(p);
	return lista;
}