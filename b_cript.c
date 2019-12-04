#include "b.c"
#include "string.h"

TB *b_encript(TB* x, char* saida, char letra){
    FILE* temp = fopen("temp", "a+");         //arquivo temporario
    FILE* output = fopen(saida, "a+");        //arquivo de saida
    char* linha;
    TB *resp = NULL;
    if(!x) return resp;                      //retorna NULL se n houver arvore
    int i = 0;
                                             //anda arvore ate encontrar nó maior que a frequencia
    while(i < x->nch && letra > x->letra[i]) i++;
    if(i < x->nch && letra == x->letra[i]){  //se encontrar letra
        fprintf(temp,"%d",i);            //escreve posicao no arquivo temp
        getline(&linha,0,temp);          //le arquivo temp como string
        fprintf(output,"%s",linha);      //escreve string no arquivo permanente
        fprintf(output,",");             //escreve indicador no arquivo permanente
        fclose(output);                  //fecha arquivo permanente
        fclose(temp);                    //fecha && apaga arquivo temporario
        remove("temp");
        return x;
    }

    if(x->folha){                           //se não encontrar letra
        fprintf(output,"?");            //escreve ? no arquivo permanente
        fclose(output);
        fclose(temp);
        remove("temp");                 //apaga arquivo temporario
        return resp;
    }

    fprintf(temp,"%d",i);                   //caso NDA, escreve posicao no arquivo temporario
    fclose(output);
    fclose(temp);
                                           //chama funcao recursivamente
    return b_encript(x->filho[i], saida, letra);
}
TB *b_decript(TB* arv,char *string_encriptada, char* saida){
    FILE* output = fopen(saida,"a+");
    TB *aux=arv;
                                          //pelo tamanho da string
    for (int i=0;i<strlen(string_encriptada);i++){
        if(string_encriptada[i]=='?'){ 
            fprintf(output,"?"); //esreve ? se o encriptado for ?
            aux = arv;
        }
        if(string_encriptada[i]!=','){ //se o char for um numero
            aux=arv->filho[i];     //move arvore
                                   //se o proximo char for o indicador escreve a letra da posicao atual
            if(string_encriptada[i+1]==','){
                fprintf(output,"%s",aux->letra[i]);
                aux=arv;
            }
        }
    }

}

void encrypta_b(int input, int output, TB *arv) {
    char *arq_aux, *texto;
    if (input == 1) { // Encrypta b por TEXTO TERMINAL
        printf("Digite o texto a ser criptografado: ");
        scanf(" %c ", &texto);

        if (output == 0){ // Salva em um arquivo
            printf("Digite o nome do arquivo a ser gerado: ");
            scanf(" %c ", &arq_aux);
            for (int i=0; i < strlen(texto); i++){ // Percorre a variavel letra por letra
                b_encript(arv, arq_aux, texto[i]); // Letra por letra é criptografada
            }

        }else if (output == 1){ // Mostra no terminal
            for (int i=0; i < strlen(texto); i++){ // Percorre a variavel letra por letra
                b_encript(arv, "temp.txt", texto[i]); // Letra por letra é criptografada e gravada em um arquivo temporário
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
                b_encript(arv, arq_aux, texto[i]); // Letra por letra é criptografada
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
    } else if (input == 0){ // Encrypta b por ARQUIVO do usuario
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
                b_encript(arv, "temp.txt", buffer[i]); // Letra por letra é criptografada
            }

        }else if (output == 1){ // Mostra no terminal
            for (int i=0; i < strlen(texto); i++){ // Percorre a variavel letra por letra
                b_encript(arv, "temp.txt", buffer[i]); // Letra por letra é criptografada e gravada em um arquivo temporário
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
                b_encript(arv, arq_aux, texto[i]); // Letra por letra é criptografada
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