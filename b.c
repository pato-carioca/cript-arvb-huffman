#include "b.h"

TB *criab(char *arq, int t){ // cria a arv b inicial, com td o alfabeto
    FILE *F = fopen(arq, "rt");
    if (!F) exit(1);
    int r;
    char l, m, cv;
    float f;
    r = fscanf(F, " %c %c %c %f", &l, &m, &cv, &f);
    
    printf("\nteste %c %c %c %f\n", l, m, cv, f);
    
    TB *arv = NULL;
    while (r == 4 && feof(F)){
    
    	fprintf(stderr,"\nteste 1.25\n");
    
        insereb(arv, l, m, cv, f, t);
        
        fprintf(stderr,"\nteste %c %c %c %f\n", l, m, cv, f);
        
        r = fscanf(F, "%c %c %c %f", &l, &m, &cv, &f);
        //if(feof(F)) break;
        
        printf("\nteste %c %c %c %f\n", l, m, cv, f);
        printf("r = %d\n", r);
	getchar();
    }
    printf("\nteste 1.5\n");
    
    return arv;
}

TB *crianob(/*char l, char m, char cv, float f, */int t){
    TB *novo = (TB*)malloc(sizeof(TB));
    novo->letra = (char*)malloc(sizeof(char)*(2*t-1)); // num max de letras q o nó pode ter
    novo->mm = (char*)malloc(sizeof(char)*(2*t-1));
    novo->cv = (char*)malloc(sizeof(char)*(2*t-1));
    novo->freq = (float*)malloc(sizeof(float)*(2*t-1));
    novo->filho = (TB**)malloc(sizeof(TB)*(2*t));
    int a;
    for (a = 0; a < (2*t); a++) novo->filho[a] = NULL;
    novo->nch = 0;
    novo->folha = 1; /*
    novo->letra[0] = l; // coloca isso agr ou só na inserção?
    novo->mm[0] = m; 
    novo->cv[0] = cv;
    novo->freq[0] = f; */
    return novo;
}

TB *insereb(TB *arv, char l, char m, char cv, float f, int t){
    if (!arv){
        arv = crianob(t); // inserir ou não os outros parâmetros?
        arv->letra[0] = l; 
        arv->mm[0] = m;
        arv->cv[0] = cv;
        arv->freq[0] = f;
        arv->nch++;
        return arv;
    }
    if (arv->nch == (2*t-1)){
        TB *s = crianob(t);
        s->folha = 0;
        s->filho[0] = arv;
        s = divisao(s, 1, arv, t);
        s = ins_nao_comp(s, l, m, cv, f, t);
        return s;
    }
    arv = ins_nao_comp(arv, l, m, cv, f, t);
    return arv;
}

TB *ins_nao_comp(TB *arv, char l, char m, char cv, float f, int t){
    int a = arv->nch-1; // fazer as correções para as class e a freq
    if (arv->folha){
        while ((a >= 0) && (l < arv->letra[a])){
            arv->letra[a+1] = arv->letra[a];
            arv->mm[a+1] = arv->mm[a];
            arv->cv[a+1] = arv->cv[a];
            arv->freq[a+1] = arv->freq[a];
            a--;
        }
        arv->letra[a+1] = l;
        arv->mm[a+1] = m;
        arv->cv[a+1] = cv;
        arv->freq[a+1] = f;
        arv->nch++;
    }
    else{
        while ((a >= 0) && (l < arv->letra[a])) a--;
        a++;
        if (arv->filho[a]->nch == ((2*t-1))){
            arv = divisao(arv, a+1, arv->filho[a], t);
            if(l > arv->letra[a]) a++;
        }
        arv->filho[a] = ins_nao_comp(arv->filho[a], l, m, cv, f, t);
    }
    return arv;
}

TB *divisao(TB *arv, int ind, TB *f, int t){
    TB *irmao = crianob(t);
    irmao->folha = f->folha;
    irmao->nch = t-1;
    int a;
    for (a = 0; a < t-1; a++){
        irmao->letra[a] = f->letra[a+t]; 
        irmao->mm[a] = f->mm[a+t];
        irmao->cv[a] = f->cv[a+t];
        irmao->freq[a] = f->freq[a+t];
    }
    if (!f->folha) // copiar os filhos de f
        for (a = 0; a < t; a++){ 
            irmao->filho[a] = f->filho[a+t]; 
            f->filho[a+t] = NULL; 
        }
    f->nch = t-1; 
    for (a = arv->nch; a >= ind; a--) arv->filho[a+1] = arv->filho[a]; 
    arv->filho[ind] = irmao; 
    for (a = arv->nch; a >= ind; a--){
        arv->letra[a] = arv->letra[a-1]; 
        arv->mm[a] = arv->mm[a-1];
        arv->cv[a] = arv->cv[a-1];
        arv->freq[a] = arv->freq[a=1];
    }
    arv->letra[ind-1] = f->letra[t-1]; 
    arv->mm[ind-1] = f->mm[t-1];
    arv->cv[ind-1] = f->cv[t-1];
    arv->freq[ind-1] = f->freq[t-1];
    arv->nch++; 
    return arv; 
}

TB *novaarvb(char *arq, TB *velha, int t) {
	liberab(velha);
	return criab(arq, t);
}

TB *retirab(TB *arv, char clas, int t, int *existe) { // clas == m || clas == M || clas == c || clas == v
	if ((!arv) || (!buscab(arv, clas, '0'))) {
		*existe = 0;
		return arv;
	}
	if ((clas == 'm') || (clas == 'M')) { // remover baseado em mm
		return removemmb(arv, clas, t);
	}
	else
		return removecvb(arv, clas, t);
}

TB *retiraduplab(TB *arv, char clas1, char clas2, int t, int *existe) {
	if ((!arv) || (!buscaduplab(arv, clas1, clas2))) {
		*existe = 0;
		return arv;
	}
	return removeduplab(arv, clas1, clas2, t);
}

TB *removemmb(TB *arv, char clas, int t) { // remover baseado em maiusculo e minusculo
	if (!arv) return arv;
	int a;
	for (a = 0; (a < arv->nch) && (arv->mm[a] != clas); a++);
	if ((a < arv->nch) && (clas == arv->mm[a])) { // casos 1, 2a, 2b e 2c
		if (arv->folha) { // caso 1
			int b;
			for (b = a; b < arv->nch-1; b++) { // andar c tds as infos um passo pra tras
				arv->letra[b] = arv->letra[b+1];
				arv->mm[b] = arv->mm[b+1];
				arv->cv[b] = arv->cv[b+1];
				arv->freq[b] = arv->freq[b+1];
			}
			arv->nch--;
			return arv;
		}
		if ((!arv->folha) && (arv->filho[a]->nch >= t)) { // caso 2a
			TB *y = arv->filho[a]; // encontrar predecessor k' de k na arv com raiz em y
			while (!y->folha) y = y->filho[y->nch];
			arv->filho[a] = removemmb(arv->filho[a], y->mm[y->nch-1], t); // eliminar recursivamente k e substituir k por k' em x
			
			arv->letra[a] = y->letra[y->nch-1];
			arv->mm[a] = y->mm[y->nch-1];
			arv->cv[a] = y->cv[y->nch]-1;
			arv->freq[a] = y->freq[y->nch-1];
			
			return arv;
		}
		if ((!arv->folha) && (arv->filho[a+1]->nch >= t)) { // caso 2b
			TB *y = arv->filho[a+1]; // encontrar o sucessor k' de k na arv com raiz em y
			while (!y->folha) y = y->filho[0];
			y = removemmb(arv->filho[a+1], y->mm[0], t); // eliminar recursivamente k e substituir k por k' em x
			
			arv->letra[a] = y->letra[0];
			arv->mm[a] = y->mm[0];
			arv->cv[a] = y->cv[0];
			arv->freq[a] = y->freq[0];
			
			return arv;
		}
		if ((!arv->folha) && (arv->filho[a+1]->nch == t-1) && (arv->filho[a]->nch == t-1)) { // caso 2c
			TB *y = arv->filho[a], *z = arv->filho[a+1], *aux = crianob(t);
			
			aux->letra[0] = arv->letra[a];
			aux->mm[0] = arv->mm[a];
			aux->cv[0] = arv->cv[a];
			aux->freq[0] = arv->freq[a];
			
			y->letra[y->nch] = aux->letra[0]; // folocar infos ao final de filho[a]
			y->mm[y->nch] = aux->mm[0];
			y->cv[y->nch] = aux->cv[0];
			y->freq[y->nch] = aux->freq[0];

			int b;
			for (b = 0; b < t-1; b++) { // juntar infos[a+1] com infos[a]
				y->letra[t+b] = z->letra[b];
				y->mm[t+b] = z->mm[b];
				y->cv[t+b] = z->cv[b];
				y->freq[t+b] = z->freq[b];
			}
			for (b = 0; b <= t; b++) // juntar filho[a+1] com filho [a]
				y->filho[t+b] = z->filho[b];
			y->nch = 2*t-1;
			for (b = a; b < arv->nch-1; b++) { // remover infos relacionadas à letra da clas
				arv->letra[b] = arv->letra[b+1];
				arv->mm[b] = arv->mm[b+1];
				arv->cv[b] = arv->cv[b+1];
				arv->freq[b] = arv->freq[b+1];
			}
			for (b = a+1; b <= arv->nch; b++) // remover ponteiro para filho [a+1]
				arv->filho[b] = arv->filho[b+1];
			arv->filho[b] = NULL; // campello
			arv->nch--;
			arv->filho[a] = removemmb(arv->filho[a], aux->mm[0], t);
			return arv;
		}
	}

	TB *y = arv->filho[a], *z = NULL;
	if (y->nch == t-1) { // casos 3a e 3b
		if ((a < arv->nch) && (arv->filho[a+1]->nch >= t)) { // caso 3a
			z = arv->filho[a+1];
			
			y->letra[t-1] = arv->letra[a]; // dar a y as infos da arv
			y->mm[t-1] = arv->mm[a];
			y->cv[t-1] = arv->cv[a];
			y->freq[t-1] = arv->freq[a];

			y->nch--;
			
			arv->letra[a] = z->letra[0]; // dar a arv um conj de infos de z
			arv->mm[a] = z->mm[0];
			arv->cv[a] = z->cv[0];
			arv->freq[a] = z->freq[0];

			int b;
			for (b = 0; b < z->nch-1; b++) { // ajustar infos de z
				z->letra[b] = z->letra[b+1];
				z->mm[b] = z->mm[b+1];
				z->cv[b] = z->cv[b+1];
				z->freq[b] = z->freq[b+1];
			}
			y->filho[y->nch] = z->filho[0]; // ponteiro menor de z vai para o novo elem em y
			for (b = 0; b < z->nch; b++) // ajustar filhos de z
				z->filho[b] = z->filho[b+1];
			z->nch--;
			arv->filho[a] = removemmb(arv->filho[a], clas, t);
			return arv;
		}
		if ((a > 0) && (!z) && (arv->filho[a-1]->nch >= t)) { // caso 3a
			z = arv->filho[a-1];
			int b;
			for (b = y->nch; b > 0; b--) { // encixar lugar do novo conj de infos
				y->letra[b] = y->letra[b-1];
				y->mm[b] = y->mm[b-1];
				y->cv[b] = y->cv[b-1];
				y->freq[b] = y->freq[b-1];
			}
			for (b = y->nch+1; b > 0; b--) // encaixar lugar dos filhos do novo conj de infos
				y->filho[b] = y->filho[b-1];
			
			y->letra[0] = arv->letra[a-1]; // dar a y as infos i da arv
			y->mm[0] = arv->mm[a-1];
			y->cv[0] = arv->cv[a-1];
			y->freq[0] = arv->freq[a-1];

			y->nch++;

			arv->letra[a-1] = z->letra[z->nch-1]; // dar a arv um conj de infos de z
			arv->mm[a-1] = z->mm[z->nch-1];
			arv->cv[a-1] = z->cv[z->nch-1];
			arv->freq[a-1] = z->freq[z->nch-1];

			y->filho[0] = z->filho[z->nch]; // ponteiro de z vai para o novo elem em y
			z->nch--;
			arv->filho[a] = removemmb(y, clas, t);
			return arv;
		}
		if (!z) { // caso 3b 
			if ((a < arv->nch) && (arv->filho[a+1]->nch == t-1)) {
				z = arv->filho[a+1];

				y->letra[t-1] = arv->letra[a]; // pegar conj de infos a e colocar no fim de filho[a]
				y->mm[t-1] = arv->mm[a];
				y->cv[t-1] = arv->cv[a];
				y->freq[t-1] = arv->freq[a];

				y->nch++;
				int b;
				for (b = 0; b < t-1; b++) {
					y->letra[t+b] = z->letra[b]; // passar filho[a+1] para filho[a]
					y->mm[t+b] = z->mm[b];
					y->cv[t+b] = z->cv[b];
					y->freq[t+b] = z->freq[b];

					y->nch++;
				}
				if (!y->folha) 
					for (b = 0; b < t; b++)
						y->filho[t+b] = z->filho[b];
				for (b = a; b < arv->nch-1; b++) { // limpar refs a a
					arv->letra[b] = arv->letra[b+1];
					arv->mm[b] = arv->mm[b+1];
					arv->cv[b] = arv->cv[b+1];
					arv->freq[b] = arv->freq[b+1];

					arv->filho[b+1] = arv->filho[b+2];
				}
				arv->nch--;
				arv = removemmb(arv, clas, t);
				return arv;
			}
			if ((a > 0) && (arv->filho[a-1]->nch == t-1)) {
				z = arv->filho[a-1];
				if (a == arv->nch) {
					z->letra[t-1] = arv->letra[a-1]; // pegar infos[a] e por ao final de filho[a-1]
					z->mm[t-1] = arv->mm[a-1];
					z->cv[t-1] = arv->cv[a-1];
					z->freq[t-1] = arv->freq[a-1];
				}
				else { 
					z->letra[t-1] = arv->letra[a]; // pegra infos[a] e por ao final de filho[a-1]
					z->mm[t-1] = arv->mm[a];
					z->cv[t-1] = arv->cv[a];
					z->freq[t-1] = arv->freq[a];
				}
				z->nch++;
				int b;
				for (b = 0; b < t-1; b++) {
					z->letra[t+b] = y->letra[b]; // passar filho[a+1] para filho [a]
					z->mm[t+b] = y->mm[b];
					z->cv[t+b] = y->cv[b];
					z->freq[t+b] = y->freq[b];

					z->nch++;
				}
				if (!z->folha)
					for (b = 0; b < t; b++)
						z->filho[t+b] = y->filho[b];
				arv->nch--;
				arv->filho[a-1] = z;
				arv = removemmb(arv, clas, t);
				return arv;
			}
		
		}
	}
	arv->filho[a] = removemmb(arv->filho[a], clas, t);
	return arv;
}

TB *removecvb(TB *arv, char clas, int t) { // remover baseado em cv
	if (!arv) return arv;
	int a;
	for (a = 0; (a < arv->nch) && (arv->cv[a] != clas); a++);
	if ((a < arv->nch) && (clas == arv->cv[a])) { // casos 1, 2a, 2b e 2c
		if (arv->folha) { // caso 1
			int b;
			for (b = a; b < arv->nch-1; b++) { // andar c tds as infos um passo pra tras
				arv->letra[b] = arv->letra[b+1];
				arv->mm[b] = arv->mm[b+1];
				arv->cv[b] = arv->cv[b+1];
				arv->freq[b] = arv->freq[b+1];
			}
			arv->nch--;
			return arv;
		}
		if ((!arv->folha) && (arv->filho[a]->nch >= t)) { // caso 2a
			TB *y = arv->filho[a]; // encontrar predecessor k' de k na arv com raiz em y
			while (!y->folha) y = y->filho[y->nch];
			arv->filho[a] = removecvb(arv->filho[a], y->cv[y->nch-1], t); // eliminar recursivamente k e substituir k por k' em x

			arv->letra[a] = y->letra[y->nch-1];
			arv->mm[a] = y->mm[y->nch-1];
			arv->cv[a] = y->cv[y->nch]-1;
			arv->freq[a] = y->freq[y->nch-1];

			return arv;
		}
		if ((!arv->folha) && (arv->filho[a+1]->nch >= t)) { // caso 2b
			TB *y = arv->filho[a+1]; // encontrar o sucessor k' de k na arv com raiz em y
				while (!y->folha) y = y->filho[0];
				y = removecvb(arv->filho[a+1], y->cv[0], t); // eliminar recursivamente k e substituir k por k' em x

				arv->letra[a] = y->letra[0];
				arv->mm[a] = y->mm[0];
				arv->cv[a] = y->cv[0];
				arv->freq[a] = y->freq[0];

				return arv;
		}
		if ((!arv->folha) && (arv->filho[a+1]->nch == t-1) && (arv->filho[a]->nch == t-1)) { // caso 2c
			TB *y = arv->filho[a], *z = arv->filho[a+1], *aux = crianob(t);

			aux->letra[0] = arv->letra[a];
			aux->mm[0] = arv->mm[a];
			aux->cv[0] = arv->cv[a];
			aux->freq[0] = arv->freq[a];

			y->letra[y->nch] = aux->letra[0]; // folocar infos ao final de filho[a]
			y->mm[y->nch] = aux->mm[0];
			y->cv[y->nch] = aux->cv[0];
			y->freq[y->nch] = aux->freq[0];

			int b;
			for (b = 0; b < t-1; b++) { // juntar infos[a+1] com infos[a]
				y->letra[t+b] = z->letra[b];
				y->mm[t+b] = z->mm[b];
				y->cv[t+b] = z->cv[b];
				y->freq[t+b] = z->freq[b];
			}
			for (b = 0; b <= t; b++) // juntar filho[a+1] com filho [a]
				y->filho[t+b] = z->filho[b];
			y->nch = 2 * t-1;
			for (b = a; b < arv->nch-1; b++) { // remover infos relacionadas à letra da clas
				arv->letra[b] = arv->letra[b+1];
				arv->mm[b] = arv->mm[b+1];
				arv->cv[b] = arv->cv[b+1];
				arv->freq[b] = arv->freq[b+1];
			}
			for (b = a+1; b <= arv->nch; b++) // remover ponteiro para filho [a+1]
				arv->filho[b] = arv->filho[b+1];
			arv->filho[b] = NULL; // campello
			arv->nch--;
			arv->filho[a] = removecvb(arv->filho[a], aux->cv[0], t);
			return arv;
		}
	}

	TB *y = arv->filho[a], *z = NULL;
	if (y->nch == t-1) { // casos 3a e 3b
		if ((a < arv->nch) && (arv->filho[a+1]->nch >= t)) { // caso 3a
			z = arv->filho[a+1];

			y->letra[t-1] = arv->letra[a]; // dar a y as infos da arv
			y->mm[t-1] = arv->mm[a];
			y->cv[t-1] = arv->cv[a];
			y->freq[t-1] = arv->freq[a];

			y->nch--;

			arv->letra[a] = z->letra[0]; // dar a arv um conj de infos de z
			arv->mm[a] = z->mm[0];
			arv->cv[a] = z->cv[0];
			arv->freq[a] = z->freq[0];

			int b;
			for (b = 0; b < z->nch-1; b++) { // ajustar infos de z
				z->letra[b] = z->letra[b+1];
				z->mm[b] = z->mm[b+1];
				z->cv[b] = z->cv[b+1];
				z->freq[b] = z->freq[b+1];
			}
			y->filho[y->nch] = z->filho[0]; // ponteiro menor de z vai para o novo elem em y
			for (b = 0; b < z->nch; b++) // ajustar filhos de z
				z->filho[b] = z->filho[b+1];
			z->nch--;
			arv->filho[a] = removecvb(arv->filho[a], clas, t);
			return arv;
		}
		if ((a > 0) && (!z) && (arv->filho[a-1]->nch >= t)) { // caso 3a
			z = arv->filho[a-1];
			int b;
			for (b = y->nch; b > 0; b--) { // encixar lugar do novo conj de infos
				y->letra[b] = y->letra[b-1];
				y->mm[b] = y->mm[b-1];
				y->cv[b] = y->cv[b-1];
				y->freq[b] = y->freq[b-1];
			}
			for (b = y->nch+1; b > 0; b--) // encaixar lugar dos filhos do novo conj de infos
				y->filho[b] = y->filho[b-1];

			y->letra[0] = arv->letra[a-1]; // dar a y as infos i da arv
			y->mm[0] = arv->mm[a-1];
			y->cv[0] = arv->cv[a-1];
			y->freq[0] = arv->freq[a-1];

			y->nch++;

			arv->letra[a-1] = z->letra[z->nch-1]; // dar a arv um conj de infos de z
			arv->mm[a-1] = z->mm[z->nch-1];
			arv->cv[a-1] = z->cv[z->nch-1];
			arv->freq[a-1] = z->freq[z->nch-1];

			y->filho[0] = z->filho[z->nch]; // ponteiro de z vai para o novo elem em y
			z->nch--;
			arv->filho[a] = removecvb(y, clas, t);
			return arv;
		}
		if (!z) { // caso 3b 
			if ((a < arv->nch) && (arv->filho[a+1]->nch == t-1)) {
				z = arv->filho[a+1];

				y->letra[t-1] = arv->letra[a]; // pegar conj de infos a e colocar no fim de filho[a]
				y->mm[t-1] = arv->mm[a];
				y->cv[t-1] = arv->cv[a];
				y->freq[t-1] = arv->freq[a];

				y->nch++;
				int b;
				for (b = 0; b < t-1; b++) {
					y->letra[t+b] = z->letra[b]; // passar filho[a+1] para filho[a]
					y->mm[t+b] = z->mm[b];
					y->cv[t+b] = z->cv[b];
					y->freq[t+b] = z->freq[b];

					y->nch++;
				}
				if (!y->folha)
					for (b = 0; b < t; b++)
						y->filho[t+b] = z->filho[b];
				for (b = a; b < arv->nch-1; b++) { // limpar refs a a
					arv->letra[b] = arv->letra[b+1];
					arv->mm[b] = arv->mm[b+1];
					arv->cv[b] = arv->cv[b+1];
					arv->freq[b] = arv->freq[b+1];

					arv->filho[b+1] = arv->filho[b+2];
				}
				arv->nch--;
				arv = removecvb(arv, clas, t);
				return arv;
			}
			if ((a > 0) && (arv->filho[a-1]->nch == t-1)) {
				z = arv->filho[a-1];
				if (a == arv->nch) {
					z->letra[t-1] = arv->letra[a-1]; // pegar infos[a] e por ao final de filho[a-1]
					z->mm[t-1] = arv->mm[a-1];
					z->cv[t-1] = arv->cv[a-1];
					z->freq[t-1] = arv->freq[a-1];
				}
				else {
					z->letra[t-1] = arv->letra[a]; // pegra infos[a] e por ao final de filho[a-1]
					z->mm[t-1] = arv->mm[a];
					z->cv[t-1] = arv->cv[a];
					z->freq[t-1] = arv->freq[a];
				}
				z->nch++;
				int b;
				for (b = 0; b < t-1; b++) {
					z->letra[t+b] = y->letra[b]; // passar filho[a+1] para filho [a]
					z->mm[t+b] = y->mm[b];
					z->cv[t+b] = y->cv[b];
					z->freq[t+b] = y->freq[b];

					z->nch++;
				}
				if (!z->folha)
					for (b = 0; b < t; b++)
						z->filho[t+b] = y->filho[b];
				arv->nch--;
				arv->filho[a-1] = z;
				arv = removecvb(arv, clas, t);
				return arv;
			}

		}
	}
	arv->filho[a] = removecvb(arv->filho[a], clas, t);
	return arv;
}

TB *removeduplab(TB *arv, char clas1, char clas2, int t) { // remover baseado em duas classificacoes
	if (!arv) return arv;
	int a;
	for (a = 0; ((a < arv->nch) && (arv->mm[a] != clas1) && (arv->cv[a] != clas2)); a++);
	if ((a < arv->nch) && (clas1 == arv->mm[a]) && (clas2 == arv->cv[a])) { // casos 1, 2a, 2b e 2c
		if (arv->folha) { // caso 1
			int b;
			for (b = a; b < arv->nch-1; b++) { // andar c tds as infos um passo pra tras
				arv->letra[b] = arv->letra[b+1];
				arv->mm[b] = arv->mm[b+1];
				arv->cv[b] = arv->cv[b+1];
				arv->freq[b] = arv->freq[b+1];
			}
			arv->nch--;
			return arv;
		}
		if ((!arv->folha) && (arv->filho[a]->nch >= t)) { // caso 2a
			TB *y = arv->filho[a]; // encontrar predecessor k' de k na arv com raiz em y
			while (!y->folha) y = y->filho[y->nch];
			arv->filho[a] = removeduplab(arv->filho[a], y->mm[y->nch-1], y->mm[y->nch-1], t); // eliminar recursivamente k e substituir k por k' em x

			arv->letra[a] = y->letra[y->nch-1];
			arv->mm[a] = y->mm[y->nch-1];
			arv->cv[a] = y->cv[y->nch]-1;
			arv->freq[a] = y->freq[y->nch-1];

			return arv;
		}
		if ((!arv->folha) && (arv->filho[a+1]->nch >= t)) { // caso 2b
			TB *y = arv->filho[a+1]; // encontrar o sucessor k' de k na arv com raiz em y
				while (!y->folha) y = y->filho[0];
				y = removeduplab(arv->filho[a+1], y->mm[0], y->cv[0], t); // eliminar recursivamente k e substituir k por k' em x

				arv->letra[a] = y->letra[0];
				arv->mm[a] = y->mm[0];
				arv->cv[a] = y->cv[0];
				arv->freq[a] = y->freq[0];

				return arv;
		}
		if ((!arv->folha) && (arv->filho[a+1]->nch == t-1) && (arv->filho[a]->nch == t-1)) { // caso 2c
			TB *y = arv->filho[a], *z = arv->filho[a+1], *aux = crianob(t);

			aux->letra[0] = arv->letra[a];
			aux->mm[0] = arv->mm[a];
			aux->cv[0] = arv->cv[a];
			aux->freq[0] = arv->freq[a];

			y->letra[y->nch] = aux->letra[0]; // folocar infos ao final de filho[a]
			y->mm[y->nch] = aux->mm[0];
			y->cv[y->nch] = aux->cv[0];
			y->freq[y->nch] = aux->freq[0];

			int b;
			for (b = 0; b < t-1; b++) { // juntar infos[a+1] com infos[a]
				y->letra[t+b] = z->letra[b];
				y->mm[t+b] = z->mm[b];
				y->cv[t+b] = z->cv[b];
				y->freq[t+b] = z->freq[b];
			}
			for (b = 0; b <= t; b++) // juntar filho[a+1] com filho [a]
				y->filho[t+b] = z->filho[b];
			y->nch = 2 * t-1;
			for (b = a; b < arv->nch-1; b++) { // remover infos relacionadas à letra da clas
				arv->letra[b] = arv->letra[b+1];
				arv->mm[b] = arv->mm[b+1];
				arv->cv[b] = arv->cv[b+1];
				arv->freq[b] = arv->freq[b+1];
			}
			for (b = a+1; b <= arv->nch; b++) // remover ponteiro para filho [a+1]
				arv->filho[b] = arv->filho[b+1];
			arv->filho[b] = NULL; // campello
			arv->nch--;
			arv->filho[a] = removeduplab(arv->filho[a], aux->mm[0], aux->cv[0], t);
			return arv;
		}
	}

	TB *y = arv->filho[a], *z = NULL;
	if (y->nch == t-1) { // casos 3a e 3b
		if ((a < arv->nch) && (arv->filho[a+1]->nch >= t)) { // caso 3a
			z = arv->filho[a+1];

			y->letra[t-1] = arv->letra[a]; // dar a y as infos da arv
			y->mm[t-1] = arv->mm[a];
			y->cv[t-1] = arv->cv[a];
			y->freq[t-1] = arv->freq[a];

			y->nch--;

			arv->letra[a] = z->letra[0]; // dar a arv um conj de infos de z
			arv->mm[a] = z->mm[0];
			arv->cv[a] = z->cv[0];
			arv->freq[a] = z->freq[0];

			int b;
			for (b = 0; b < z->nch-1; b++) { // ajustar infos de z
				z->letra[b] = z->letra[b+1];
				z->mm[b] = z->mm[b+1];
				z->cv[b] = z->cv[b+1];
				z->freq[b] = z->freq[b+1];
			}
			y->filho[y->nch] = z->filho[0]; // ponteiro menor de z vai para o novo elem em y
			for (b = 0; b < z->nch; b++) // ajustar filhos de z
				z->filho[b] = z->filho[b+1];
			z->nch--;
			arv->filho[a] = removeduplab(arv->filho[a], clas1, clas2, t);
			return arv;
		}
		if ((a > 0) && (!z) && (arv->filho[a-1]->nch >= t)) { // caso 3a
			z = arv->filho[a-1];
			int b;
			for (b = y->nch; b > 0; b--) { // encixar lugar do novo conj de infos
				y->letra[b] = y->letra[b-1];
				y->mm[b] = y->mm[b-1];
				y->cv[b] = y->cv[b-1];
				y->freq[b] = y->freq[b-1];
			}
			for (b = y->nch+1; b > 0; b--) // encaixar lugar dos filhos do novo conj de infos
				y->filho[b] = y->filho[b-1];

			y->letra[0] = arv->letra[a-1]; // dar a y as infos i da arv
			y->mm[0] = arv->mm[a-1];
			y->cv[0] = arv->cv[a-1];
			y->freq[0] = arv->freq[a-1];

			y->nch++;

			arv->letra[a-1] = z->letra[z->nch-1]; // dar a arv um conj de infos de z
			arv->mm[a-1] = z->mm[z->nch-1];
			arv->cv[a-1] = z->cv[z->nch-1];
			arv->freq[a-1] = z->freq[z->nch-1];

			y->filho[0] = z->filho[z->nch]; // ponteiro de z vai para o novo elem em y
			z->nch--;
			arv->filho[a] = removeduplab(y, clas1, clas2, t);
			return arv;
		}
		if (!z) { // caso 3b 
			if ((a < arv->nch) && (arv->filho[a+1]->nch == t-1)) {
				z = arv->filho[a+1];

				y->letra[t-1] = arv->letra[a]; // pegar conj de infos a e colocar no fim de filho[a]
				y->mm[t-1] = arv->mm[a];
				y->cv[t-1] = arv->cv[a];
				y->freq[t-1] = arv->freq[a];

				y->nch++;
				int b;
				for (b = 0; b < t-1; b++) {
					y->letra[t+b] = z->letra[b]; // passar filho[a+1] para filho[a]
					y->mm[t+b] = z->mm[b];
					y->cv[t+b] = z->cv[b];
					y->freq[t+b] = z->freq[b];

					y->nch++;
				}
				if (!y->folha)
					for (b = 0; b < t; b++)
						y->filho[t+b] = z->filho[b];
				for (b = a; b < arv->nch-1; b++) { // limpar refs a a
					arv->letra[b] = arv->letra[b+1];
					arv->mm[b] = arv->mm[b+1];
					arv->cv[b] = arv->cv[b+1];
					arv->freq[b] = arv->freq[b+1];

					arv->filho[b+1] = arv->filho[b+2];
				}
				arv->nch--;
				arv = removeduplab(arv, clas1, clas2, t);
				return arv;
			}
			if ((a > 0) && (arv->filho[a-1]->nch == t-1)) {
				z = arv->filho[a-1];
				if (a == arv->nch) {
					z->letra[t-1] = arv->letra[a-1]; // pegar infos[a] e por ao final de filho[a-1]
					z->mm[t-1] = arv->mm[a-1];
					z->cv[t-1] = arv->cv[a-1];
					z->freq[t-1] = arv->freq[a-1];
				}
				else {
					z->letra[t-1] = arv->letra[a]; // pegra infos[a] e por ao final de filho[a-1]
					z->mm[t-1] = arv->mm[a];
					z->cv[t-1] = arv->cv[a];
					z->freq[t-1] = arv->freq[a];
				}
				z->nch++;
				int b;
				for (b = 0; b < t-1; b++) {
					z->letra[t+b] = y->letra[b]; // passar filho[a+1] para filho [a]
					z->mm[t+b] = y->mm[b];
					z->cv[t+b] = y->cv[b];
					z->freq[t+b] = y->freq[b];

					z->nch++;
				}
				if (!z->folha)
					for (b = 0; b < t; b++)
						z->filho[t+b] = y->filho[b];
				arv->nch--;
				arv->filho[a-1] = z;
				arv = removeduplab(arv, clas1, clas2, t);
				return arv;
			}

		}
	}
	arv->filho[a] = removeduplab(arv->filho[a], clas1, clas2, t);
	return arv;
}

TB *buscab(TB *arv, char c, char l){ // c = class, l = letra
    if (!arv) return NULL;
    int a = 0;
    if (c != '0'){ // buscando pela classificação
        while ((a < arv->nch) && ((arv->mm[a] != c) || (arv->cv[a] != c))) a++;
	if ((arv->mm[a] == c) || (arv->cv[a] == c)) return arv;
	for (a = 0; a <= arv->nch; a++) return buscab(arv->filho[a], c, l);
    }
    if (l != '0'){ // buscando pela letra
        while ((a < arv->nch) && (arv->letra[a] < l)) a++;
        if ((a < arv->nch) && (arv->letra[0] == l)) return arv;
    	if (arv->folha) return NULL;
    }
    return buscab(arv->filho[a], c, l);
}

TB *buscaduplab(TB *arv, char clas1, char clas2) {
	if (!arv) return NULL;
	int a = 0;
	while ((a < arv->nch) && (arv->mm[a] != clas1) && (arv->cv[a] != clas2)) a++;
	if ((arv->mm[a] == clas1) && (arv->cv[a] == clas2)) return arv;
	for (a = 0; a <= arv->nch; a++) return buscaduplab(arv->filho[a], clas1, clas2);
}

TB *alterafreqb(TB *arv, char l, float f) {
	TB *p = buscab(arv, '0', l);
	if (!p) return arv;
	int a = 0;
	while (p->letra[a] != l) a++;
	p->freq[a] = f;
	return arv;
}

float freqletrab(TB *no, char l) {
	int a = 0;
	TB *no_aux = buscab(no, '0', l);
	if (!no_aux) return 0.0;
	while (no_aux->letra[a] != l) a++;
	return no_aux->freq[a];
}

void imprimenob(TB *arv, char l) {
	TB *no = buscab(arv, '0', l);
	if (!no) return;
	int a = 0;
	while (no->letra[a] != l) a++;
	printf(" %c ", arv->letra[a]);
	printf(" %c ", arv->mm[a]);
	printf(" %c ", arv->cv[a]);
	printf(" %f ", arv->freq[a]);
}

void imprimearvb(TB *arv){
    if (!arv) return;
    int a;
    for (a = 0; a < arv->nch; a++){
    	imprimearvb(arv->filho[a]);
    	printf(" %c ", arv->letra[a]);
    	printf(" %c ", arv->mm[a]);
    	printf(" %c ", arv->cv[a]);
    	printf(" %f ", arv->freq[a]);
    }
    imprimearvb(arv->filho[a]);
}

void liberab(TB *arv){
    if (!arv) return;
    int a;
    for (a = 0; a <= arv->nch; a++) liberab(arv->filho[a]);
    free (arv->filho);
    free (arv->letra);
    free (arv->mm);
    free (arv->cv);
    free (arv->freq);
    free (arv);
}
