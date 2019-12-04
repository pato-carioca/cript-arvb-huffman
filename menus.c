int menu_acao(void){
    printf("\nQual ação gostaria de realizar? \n");
    printf("0. Encriptação \n");
    printf("1. Decriptação \n");
    printf("2. Remoção \n");
    printf("3. Adição \n");
    printf("4. Troca de frequência \n");
    printf("5. Restaurar árvores originais \n"); // recriar as arvs padrão
    printf("-1. Encerrar \n");
    int a;
    scanf("%d", &a);
    return (a);
}

int menu_remocao(void){
    printf("\nQual remoção gostaria de ralizar? \n");
    printf("0. Minúsculas \n");
    printf("1. Maiúsculas \n");
    printf("2. Vogais \n");
    printf("3. Consoantes \n");
    printf("4. Duas classificações simultâneas \n");
    int a;
    scanf("%d", &a);
    return (a);
}

void menu_remocao_ambas(void){
    printf("\nFavor colocar os dígitos correspontes, separados por espaço, em ordem \n");
    printf("m = Minúscula \t M = Maiúscula \n");
    printf("c = Consoante \t v = Vogal \n");
}

int menu_input(void){
    printf("\nQual o meio de recebimento da mensagem a ser criptografada? \n");
    printf("0. Arquivo \n");
    printf("1. Terminal \n");
    int a;
    scanf("%d", &a);
    return (a);
}

int menu_output(void){
    printf("\nQual a forma de retorno da mensagem já criptogafada? \n");
    printf("0. Arquivo \n");
    printf("1. Terminal \n");
    printf("2. Ambas formas \n");
    int a;
    scanf("%d", &a);
    return (a);
}

int menu_tabela_padrao(void) {
    printf("\nDeseja usar a tabela padrão? \n");
    printf("0. Não \n");
    printf("1. Sim \n");
    int a;
    
    printf("\nteste 0.125\n"); 
    
    scanf("%d", &a);
    
    printf("\nteste 0.25\n");
    
    return (a);
}

char menu_arquivo(void) {
    printf("\nDigite o nome do arquivo que contém a tabela: \n");
    char a;
    scanf(" %c ", &a);
    return (a);
}

int menu_huff_b(void){
    printf("\nQual forma de criptografia? \n");
    printf("0. Huffman \n");
    printf("1. Árvore B \n");
    printf("2. Ambas \n");
    int a;
    scanf("%d", &a);
    return (a);
}

int menu_keep_arv(void){ // só se já houver registro de input de tabela para huffman
    printf("\nUtilizar a criptografia anterior de Huffman? \n");
    printf("0. Não \n");
    printf("1. Sim \n");
    int a;
    scanf("%d", &a);
    return (a);
}

int menu_num_freq(void) {
    printf("\nQuantas frequências serão alteradas? \n");
    int a;
    scanf("%d", &a);
    return (a);
}

char geranometabela (int n) { // não sei se funciona, fiz baseado na ci da rosseti
    char novoarq[20], nchar[5]; // novoarq formato: novatabela(n), ex: novatabela0, novatabela1; nchar: versão char de n;
    strcpy(novoarq, "novatabela"); // novoarq = "novatabela"
    sprintf(nchar, "%d", n); // transforma o num n em char em nchar; nchar = "(n)"
    strcat(novoarq, nchar); // novoarq += nchar
    strcat(novoarq, ".txt"); // formato: novatabela(n).txt
    return novoarq;
}
