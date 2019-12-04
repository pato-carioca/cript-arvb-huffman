#include <stdio.h>
#include <stdlib.h>

typedef struct prato{
    char letra;
	float freq;
    struct prato *prox;
}TL; 

TL *crial(char c, float f);
TL *inserel_fim(TL *l, char c, float f);
TL *inserel_freq_cres(TL *l, float f);
TL *removeprimeirol(TL *lista);
