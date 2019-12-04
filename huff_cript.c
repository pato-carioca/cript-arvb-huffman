#include "huffman.c"
#include "string.h"
/*
 * IMPORTANTE: Passar apenas uma letra como argumento para o char letra!
 */

void h_encript (char letra, char *filename ,THuff *arv){
    int found=0, test=0;
    FILE* output = fopen(filename, "a+");
    if (letra == arv->letra[0]) return;                //se for a folha da letra, retorna
    for (int i=0; i<strlen(arv->letra); i++){
        if (arv->letra[i] == i) found=1;        //procura a letra na string do nó
    }
    if (!found){                                    //se ela não estiver lá, escreve ? no arquivo
        fprintf(output,"?");
        return;
    }
    
    for (int i=0; i<strlen(arv->esq->letra); i++){
        if (arv->letra[i] == i) test=1;         //confere se a letra aparece no filho da esquerda
    }

    if (test){
        fprintf(output,"0");                   //caso apareça escreve 0 no arquivo e repete o processo, para o filho da esquerda
        fclose(output);
        h_encript(letra,filename,arv->esq);
    }

    else{
        fprintf(output,"1");                  //caso não apareça, escreve 1 no arquivo e repete o processo para o filho da direita
        fclose(output);
        h_encript(letra,filename,arv->dir);
    }
    return;
}

void h_decrypt (char *string_encriptada, char *filename, THuff *arv){
    THuff *aux=arv;
    FILE* output = fopen(filename, "a+");
    for (int i=0;i<strlen(string_encriptada);i++){
        if (string_encriptada[i] == '?'){   //se o caractere atual da string for ? escreve ?
            fprintf(output,"?");
            aux = arv;
        }
        if (string_encriptada[i] == '0'){      //se o caractere atual da string for 0 desce para a esquerda
            aux = aux->esq;
        }
        if (string_encriptada[i] == '1'){      //se o caractere atual da string for 1 desce para a direita
            aux = aux->dir;
        }
        
        if (!aux->esq && !aux->dir){          //se o nó não tiver filhos, escreve a letra no arquivo
            fprintf(output,"%c",aux->letra[0]);
            aux = arv;
        }
    }
    fclose(output);
    return;
}

void encrypta_huff(int input, int output, THuff *arv) {
    char *arq_aux, *texto;
    if (input == 1) { // Encrypta Huffman por TEXTO TERMINAL
        printf("Digite o texto a ser criptografado: ");
        scanf(" %c ", &texto);

        if (output == 0){ // Salva em um arquivo
            printf("Digite o nome do arquivo a ser gerado: ");
            scanf(" %c ", &arq_aux);
            for (int i=0; i < strlen(texto); i++){ // Percorre a variavel letra por letra
                h_encript(texto[i], arq_aux, arv); // Letra por letra é criptografada
            }

        }else if (output == 1){ // Mostra no terminal
            for (int i=0; i < strlen(texto); i++){ // Percorre a variavel letra por letra
                h_encript(texto[i], "temp.txt", arv); // Letra por letra é criptografada e gravada em um arquivo temporário
            }
            FILE *temp = fopen("temp.txt", "r");
            char c = fgetc(temp);
            printf("O texto criptografado é:\n");
            while (c != EOF) { // Le o arquivo criptografado inteiro até o final, e o mostra na tela
                printf ("%c", c);
                c = fgetc(temp);
            }
            fclose(temp);


        }else if (output == 2){ // Salva arquivo e mostra no terminal
            printf("Digite o nome do arquivo a ser gerado: ");
            scanf(" %c ", &arq_aux);
            for (int i=0; i < strlen(texto); i++){ // Percorre a variavel letra por letra
                h_encript(texto[i], arq_aux, arv); // Letra por letra é criptografada
            }
            FILE *temp = fopen(arq_aux, "r");
            char c = fgetc(temp);
            printf("O texto criptografado é:\n");
            while (c != EOF) { // Le o arquivo criptografado inteiro até o final, e o mostra na tela
                printf ("%c", c);
                c = fgetc(temp);
            }
            fclose(temp);
        }
    } else if (input == 0){ // Encrypta Huffman por ARQUIVO do usuario
        char arq_usu;
        printf("Digite o nome do arquivo a ser criptografado: ");
        scanf(" %c ", &arq_usu);
        char * buffer = 0; // Vai receber o texto
        long length; // Tamanho do arquivo
        FILE * f = fopen (&arq_usu, "rb");

        if (f)
        {
            fseek (f, 0, SEEK_END);   // Vai até o final do arquivo
            length = ftell (f);       // Armazena a posição final do arquivo
            fseek (f, 0, SEEK_SET);   // Volta pro começo do arquivo
            buffer = malloc (length); // Aloca o tamanho do arquivo no buffer
            if (buffer)
            {
                fread (buffer, 1, length, f); // Lê o arquivo por inteiro e armazena em buffer
            }
            fclose (f);
        }


        if (output == 0){ // Salva em um arquivo
            printf("Digite o nome do arquivo a ser gerado: ");
            scanf(" %c ", &arq_aux);
            for (int i=0; i < strlen(buffer); i++){ // Percorre a variavel letra por letra
                h_encript(buffer[i], arq_aux, arv); // Letra por letra é criptografada
            }

        }else if (output == 1){ // Mostra no terminal
            for (int i=0; i < strlen(texto); i++){ // Percorre a variavel letra por letra
                h_encript(texto[i], "temp.txt", arv); // Letra por letra é criptografada e gravada em um arquivo temporário
            }
            FILE *temp = fopen("temp.txt", "r");
            char c = fgetc(temp);
            printf("O texto criptografado é:\n");
            while (c != EOF) { // Le o arquivo criptografado inteiro até o final, e o mostra na tela
                printf ("%c", c);
                c = fgetc(temp);
            }
            fclose(temp);


        }else if (output == 2){ // Salva arquivo e mostra no terminal
            printf("Digite o nome do arquivo a ser gerado: ");
            scanf(" %c ", &arq_aux);
            for (int i=0; i < strlen(buffer); i++){ // Percorre a variavel letra por letra
                h_encript(buffer[i], arq_aux, arv); // Letra por letra é criptografada
            }
            FILE *temp = fopen(arq_aux, "r");
            char c = fgetc(temp);
            printf("O texto criptografado é:\n");
            while (c != EOF) { // Le o arquivo criptografado inteiro até o final, e o mostra na tela
                printf ("%c", c);
                c = fgetc(temp);
            }
            fclose(temp);
        }

    }else{

    }
}
