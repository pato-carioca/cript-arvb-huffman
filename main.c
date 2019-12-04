#include "lista.c"
#include "huff_cript.c" // Trata a cript e decript de Huffman
#include "b_cript.c" // Trata a cript e decript de b
#include "rm.c"
#include "menus.c" // Contém todas as chamadas de menu.

int main(void){
    int a, b, t, aux, input, output, n = 0; // a: Menu de ação; b: Tipo de tabela a ser usada; t: t da arvB; n: n de arqs novos criados;
	TB *arvb;                        // Arvore b
	THuff *arvh;                     // Arvore de Huffman
	char velhoarq[20] = "alfabeto.txt"; // será usada em rm
	
	printf("\nteste 0\n");
	
	input = menu_input(); // 0 = arq, 1 = terminal
	output = menu_output(); // 0 = arq, 1 = terminal, 2 = ambas
	printf("\nDefina t: "); // Usuario define t da arvore b
	scanf("%d", &t);
	b = menu_tabela_padrao(); // 0 = nova tab, 1 = tab alfabeto
	
	printf("\nteste 0.5\n");
	
	if (b){
        // mudar para "alfabeto.txt" antes de enviar para rosseti
        
        printf("\nteste 1\n");
        
        arvb = criab("alfabinho.txt", t);
        
        printf("\nteste 2\n");
        
        arvh = criah("alfabinho.txt");
        
        printf("\nteste 3\n");
        
	}else{
        //char arq = menu_arquivo();
            char arq;
            printf("\nDigite o nome do arquivo que contém a tabela: \n");
    	    scanf(" %c ", &arq); 
    	    
    	    printf("\nteste 1\n");
    	    
            arvb = criab(arq, t);
            
            printf("\nteste 2\n");
            
            arvh = criah(arq);
            
            printf("\nteste 3\n");
            
	}

	a = menu_acao();

    while (a >= 0){
        if (a == 0){ // criptografar

            aux = menu_huff_b(); // 0 = Huff, 1 = Arv B, 2 = Ambas

            if (aux == 0) { // Encrypt Huffman
            encrypta_huff(input, output, arvh);

            }else if (aux == 1) { // Encrypt Arv B
                encrypta_b(input, output, arvb);

            }else if (aux == 2) { // Encrypt Huff e B
                encrypta_huff(input, output, arvh);
                encrypta_b(input, output, arvb);

            }else{
                printf("Digite um valor válido, de 0 a 2, na próxima vez \n");
            }
        }

		if (a == 1){ // decriptografar
		//TODO tudo
		}

        if (a == 2){ // remover (até agr só a b) 
			/* 
			*
			* TODO: criar a funcao de criar tabela alterada e chamar a novaarvh
			*
			*/
			
			int existe = 1;
            b = menu_remocao();
			if (b == 0) { // minúsculas
				char clas = 'm';
				//while (existe) retirab(arvb, clas, t, &existe);
				char *novoarq = geranometabela(n);
				rm_min(velhoarq, novoarq);
				char velhoarq = novoarq;
				arvh = novaarvh(novoarq, arvh); // libera arvh, cria nova arv baseada em novoarq e retorna a nova arv
				arvb = novaarvb(novoarq, arvb, t); // libera arvh, cria nova arv baseada em novoarq e retorna a nova arv
				n++; // num de novas tabelas feitas aumenta em 1
			}
			else if (b == 1) { // maiúsculas
				char clas = 'M';
				//while (existe) retirab(arvb, clas, t, &existe);
				char novoarq = geranometabela(n);
				rm_Mai(velhoarq, novoarq);
				char velhoarq = novoarq;
				arvh = novaarvh(novoarq, arvh); // libera arvh, cria nova arv baseada em novoarq e retorna a nova arv
				arvb = novaarvb(novoarq, arvb, t); // libera arvh, cria nova arv baseada em novoarq e retorna a nova arv
				n++; // num de novas tabelas feitas aumenta em 1
			}
			else if (b == 2) { // vogais
				char clas = 'v';
				//while (existe) retirab(arvb, clas, t, &existe);
				char novoarq = geranometabela(n);
				rm_vog(velhoarq, novoarq);
				char velhoarq = novoarq;
				arvh = novaarvh(novoarq, arvh); // libera arvh, cria nova arv baseada em novoarq e retorna a nova arv
				arvb = novaarvb(novoarq, arvb, t); // libera arvh, cria nova arv baseada em novoarq e retorna a nova arv
				n++; // num de novas tabelas feitas aumenta em 1
			}
			else if (b == 3) { // consoantes
				char clas = 'c';
				//while (existe) retirab(arvb, clas, t, &existe);
				char novoarq = geranometabela(n);
				rm_con(velhoarq, novoarq);
				char velhoarq = novoarq;
				arvh = novaarvh(novoarq, arvh); // libera arvh, cria nova arv baseada em novoarq e retorna a nova arv
				arvb = novaarvb(novoarq, arvb, t); // libera arvh, cria nova arv baseada em novoarq e retorna a nova arv
				n++; // num de novas tabelas feitas aumenta em 1
			}
			else if (b == 4) { // duas categorias simultâneas
				char clas1, clas2;
				menu_remocao_ambas;
				scanf(" %c %c ", &clas1, &clas2);
				if (((clas1 != 'm') && (clas1 != 'M')) || ((clas2 != 'c') && (clas2 != 'v'))) {
					printf("Digite classificações válidas na próxima vez \n");
					break;
				}
				//while (existe) retiraduplab(arvb, clas1, clas2, t, &existe);
				char novoarq = geranometabela(n);
				rm_dupla(velhoarq, novoarq, clas2, clas1);
				char velhoarq = novoarq;
				arvh = novaarvh(novoarq, arvh); // libera arvh, cria nova arv baseada em novoarq e retorna a nova arv
				arvb = novaarvb(novoarq, arvb, t); // libera arvh, cria nova arv baseada em novoarq e retorna a nova arv
				n++; // num de novas tabelas feitas aumenta em 1
			} 
			else 
				printf("Digite um valor válido, de 0 a 4, na próxima vez \n");
        } 

        if (a == 3){ // adicionar

        }

		if (a == 4) { // troca de freq (ambas arvs)
			int n, b;
			char let;
			float freq, somafreq = 0, novasomafreq = 0;
			n = menu_num_freq();
			TL *lista = NULL, *p; //lista das letras e das respec freq a serem alteradas
			printf("Favor colocar as letras a terem frequência trocada em ordem alfabética, de maiúsculas para minúsculas, separads por espaço \n");
			for (b = 0; b < n; b++) {
				scanf(" %c ", &let);
				lista = inserel_fim(lista, let, -0.1);
			}
			p = lista;
			while (p) {
				imprimenob(arvb, p->letra);
				somafreq += freqletrab(arvb, p->letra);
				p = p->prox;
			}
			printf("Favor colocar apenas as frequências, na ordem das letras anteriores, separads por espaço \n");
			printf("Elas devem, obrigatoriamente, somar %f, ou a ação não será efetuada", somafreq);
			for (b = 0; b < n; b++) {
				scanf("%f", &freq);
				lista = inserel_freq_cres(lista, freq);
				novasomafreq += freq;
			}
			if (novasomafreq != somafreq) break;
			while (lista) {
				arvb = alterafreqb(arvb, lista->letra, lista->freq);
				arvh = alterafreqh(arvh, lista->letra, lista->freq);
				lista = removeprimeirol(lista);
			}
		}

		if (a == 5) {
			//arvs_padrao(arvb, arvh, t);
            // mudar para "alfabeto.txt" antes de enviar para rosseti
            arvb = criab("alfabinho.txt", t);
            arvh = criah("alfabinho.txt");
		}

        a = menu_acao();
    }
	liberab(arvb);
	liberah(arvh);
    return 0;
}

/* Eu implementei eles direto no código. Deixei o original aqui caso precise, ou sei lá.
void arvs_padrao(TB *arvb, THuff *arvh, int t) {
    // char arq = "alfabeto.txt"; // descomentar quando enviar à rosseti
    char arq = "alfabinho.txt";
    arvb = criab(arq, t);
    arvh = criah(arq);
}

void arvs_nova_tabela(TB *arvb, THuff *arvh, int t) {
    char arq = menu_arquivo();
    arvb = criab(arq, t);
    arvh = criah(arq);
}
*/

