#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAM 100

typedef struct tipo_cliente
{
    char nome[TAM];
    int RG;
    struct tipo_cliente *proximo;
}Tcliente;

/*Criação das listas*/
void listaEncadeada(Tcliente **cabeca, Tcliente **inicio ,FILE* fp);//Criação de uma lista Encadeada
Tcliente* listaSequencial(FILE* fp, int linhas, int* tam);//Criação de uma lista Sequencial

/*Funções com retorno.*/
Tcliente* criaçãoDeNo();//Criação de um nó
int getRG();//Recebe um valor de RG
int getPos(int caso, int tam);//Recebe um valor de posição
int getListaTam(Tcliente *cabeca);//Recebe o tamanho da lista encadeada

/*Inserção de clientes*/
void inserirClienteInicioE(Tcliente **cabeca, int *C, int *M);//Insere um novo cliente no início da lista Encadeada
void inserirClienteFinalE(Tcliente **final, int *C, int *M);//Insere um novo cliente no fim da lista Encadeada
void inserirClienteE(Tcliente **cabeca, int *C, int *M);//Insere um novo cliente em qualquer posição da lista Encadeada
void inserirClienteInicioS(Tcliente **usuario, int tam, int* C, int *M);//Insere um novo cliente no início da lista Sequencial
void inserirClienteFinalS(Tcliente **usuario, int tam, int* C, int *M);//Insere um novo cliente no fim da lista Sequencial
void inserirClienteS(Tcliente **usuario, int tam, int *C, int *M);//Insere um novo cliente em qualquer posição da lista Sequencial

/*Remoção de clientes*/
void removerClienteInicioE(Tcliente** inicio, int *C, int *M);//Remove o primeiro cliente da lista Encadeada
void removerClienteFinalE(Tcliente** cabeca, int *C, int *M);//Remove o último cliente da lista Encadeada
void removerClienteE(Tcliente** cabeca, int *C, int *M);//Remove um cliente de qualquer posição da lista Encadeada
void removerClienteInicioS(Tcliente** usuario, int tam, int* C, int *M);//Remove o primeiro cliente da lista Sequencial
void removerClienteFinalS(Tcliente** usuario, int tam, int* C, int* M);//Remove o último cliente da lista Sequencial
void removerClienteS(Tcliente** usuario, int tam, int *C, int *M);//Remove um cliente de qualquer posição da lista Sequencial

/*Buscar clientes*/
void buscarClienteE(Tcliente *cabeca, int *C, int *M);// Encontra um cliente em especifico através do RG em uma lista enccadeada
void buscarClienteS(Tcliente *usuario, int tam, int *C, int *M);// Encontra um cliente em especifico através do RG em uma lista sequencial
void buscarClienteBinario(Tcliente *usuario, int tam, int *C, int *M);//Encontra um cliente em específico através do RG em uma lista sequencial ordenada

/*Imprimir lista*/
void imprimirListaE(Tcliente *cabeca);//imprime a lista encadeada
void imprimirListaS(Tcliente *usuario, int tam);//imprime a lista sequencial

/*Ordenações*/
void selectionSort(Tcliente **usuario, int tam, int *C, int *M);//Oredena com SelectionSort 
void insertSort(Tcliente **usuario, int tam, int *C, int *M);//Ordena com InsertSort
void bubbleSort(Tcliente **usuario, int tam, int *C, int *M);//Ordena com BubbleSort
void shellSort(Tcliente **usuario, int tam, int *C, int *M);//Ordena com ShellSort
void quickSort(Tcliente **usuario, int inicio, int fim, int *C, int *M);//Ordena com QuickSort
void mergeSort(Tcliente **usuario, int inicio, int fim, int *C, int *M);// Ordena com MergeSort
void merge(Tcliente *usuario, int inicio, int meio, int fim, int *C, int *M);// Ordena com Merge

/*Manipulação de arquivos*/
void escreverListaArquivoE(FILE *fp, Tcliente* cabeca);//Escreve um arquivo da lista encadeada criada
void lerListaArquivoE(FILE *fp, Tcliente *cabeca);//Lê um arquivo de uma lista encadeada
void escreverListaArquivoS(FILE *fp, int tam, Tcliente *usuario);//Escreve um arquivo da lista sequencial criada 
void lerListaArquivoS(FILE *fp, int tam,Tcliente *usuario);//Lê um arquivo de uma lista sequencial

int main()
{
    FILE *fp;//Abrir arquivo
    clock_t t;//Marca o tempo em milissegundos
    char arq[30];//Armazena Nome e RG
    char pasta[TAM] = "PastaDeLista/NomeRG/";
    char lista;//Define lista Sequencial ou Encadeada
    int op;//Op��es de Menu
    int C = 0, M = 0;

    printf("Informe o nome do arquivo a ser lido: \n");
    gets(arq);
    
    strcat(pasta, arq);
    fp = fopen(pasta, "r");

    if(fp == NULL)
    {
        printf("O arquivo nao pode ser aberto =(.\n");
        system("Pause");
        exit(1);
    }

    
    do{
        printf("\nEscolha uma lista para ser formada:\nE para Lista Encadeada\nS para Sequencial\n");
        scanf("%c", &lista);
    }while(lista != 'E' && lista != 'S');

    if(lista == 'E'){
        Tcliente *careca = NULL; //Ponteiro para a cabe�a da lista
        Tcliente *noAtual, *inicio = NULL, *anterior;
        FILE *file;

        char *nome, *RG;//Armazena Nome RG

        t = clock();
        listaEncadeada(&careca, &inicio, fp);
        t = clock() - t;
        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
        fclose(fp);

        do{
            printf("\n\nOpcoes: \n1 -> inserir novo cliente no inicio da lista;\n2 -> inserir um novo cliente no final da lista;");
            printf("\n3 -> inserir novo cliente em alguma posicao especifica;\n4 -> retirar o primeiro cliente da lista;\n5 -> retirar o ultimo cliente da lista;");
            printf("\n6 -> retirar um cliente especifico;\n7 -> procurar alguem baseado em seu RG;\n8 -> ordenar a lista; (inoperante)\n9 -> imprimir a lista;\n10 -> salvar lista em um arquivo;");
            printf("\n11 -> ler lista de um arquivo;\n12 -> sair do sistema.\n");
            scanf("%d", &op);
            switch(op){
                case 1: t = clock();//Inserir cliente no in�cio da lista
                        inserirClienteInicioE(&inicio, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 2: t = clock();//Inserir cliente no Final da Lista
                        inserirClienteFinalE(&careca, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 3: t = clock();//Inserir Clientes em Outras Partes da Lista
                        inserirClienteE(&inicio, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 4: t = clock();//Retirar Cliente do Inicio da Lista
                        removerClienteInicioE(&inicio, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 5: t = clock();//Retirar Cliente do Final da Lista
                        removerClienteFinalE(&inicio, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 6: t = clock();//Retirar Cliente de Outras Partes da Lista
                        removerClienteE(&inicio, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 7: t = clock();//encontrar um cliente Em Especifico pelo RG
                        buscarClienteE(inicio, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 8: break;//Ordenar a lista

                case 9: imprimirListaE(inicio); break;//Imprimir Lista

                case 10: escreverListaArquivoE(file, inicio); break;

                case 11: lerListaArquivoE(file, inicio); break;//Imprimir arquivo

                case 12: continue;//Sair

                default: printf("\n\n Opcao nao valida\n");
            }
            system("pause");
            system("cls"); //Limpa o buffer de entrada
            C = 0; M = 0;
        }while (op != 12);

        
        noAtual = inicio;
        while(noAtual != NULL){
            careca = noAtual->proximo;
            free(noAtual);
            noAtual = careca;
        }
        return 0;
    }
    else{
        FILE *fileS;
        Tcliente *usuario;
        int tam = 0, caractere, quant_linhas = 0, RGS, op8, op7;
        t = clock();

        while((caractere = fgetc(fp)) != EOF){
            if(caractere == '\n')
                quant_linhas++;
        }
        fclose(fp);

        fp = fopen(pasta, "r");
        usuario = listaSequencial(fp, quant_linhas, &tam);
        t = clock() - t;
        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
        fclose(fp);
        do{
            printf("\n\nOpcoes: \n1 -> inserir novo cliente no inicio da lista;\n2 -> inserir um novo cliente no final da lista;");
            printf("\n3 -> inserir novo cliente em alguma posicao especifica;\n4 -> retirar o primeiro cliente da lista;\n5 -> retirar o ultimo cliente da lista;");
            printf("\n6 -> retirar um cliente especifico;\n7 -> procurar alguem baseado em seu RG;\n8 -> ordenar a lista;\n9 -> imprimir a lista;\n10 -> salvar lista em um arquivo;");
            printf("\n11 -> ler lista de um arquivo;\n12 -> sair do sistema.\n");
            scanf("%d", &op);
            switch(op){
                case 1: t = clock();
                        tam++;
                        usuario = (Tcliente*) realloc(usuario, sizeof(Tcliente)*tam);
                        inserirClienteInicioS(&usuario, tam, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 2: t = clock();
                        tam++;
                        usuario = (Tcliente*) realloc(usuario, sizeof(Tcliente)*tam);
                        inserirClienteFinalS(&usuario, tam, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 3: t = clock();
                        tam++;
                        usuario = (Tcliente*) realloc(usuario, sizeof(Tcliente)*tam);
                        inserirClienteS(&usuario, tam, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 4: t = clock();
                        tam--;
                        removerClienteInicioS(&usuario, tam, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 5: t = clock();
                        tam--;
                        removerClienteFinalS(&usuario, tam, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 6: t = clock();
                        tam--;
                        removerClienteS(&usuario, tam, &C, &M);
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 7: system("cls");
                        printf("Escolha a forma de busca: \nI -> Busca Sequecial \nII -> Busca Binaria(apenas apos ordenar a lista)\n");
                        scanf("%d", &op7);
                        t = clock();
                        switch(op7)
                        {
                            case 1: buscarClienteS(usuario, tam, &C, &M); break;
                            case 2: buscarClienteBinario(usuario, tam-1, &C, &M); break;
                            default: printf("\n\n Opcao nao valida\n");
                        }
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 8: system("cls");
                        printf("Escolha uma das formas de ordenar a lista: \nI -> Selection Sort;\nII -> Insert Sort;\nIII -> Bubble Sort;\n");
                        printf("IV -> Shell Sort;\nV -> Quick Sort;\nVI -> Merge Sort\n");
                        scanf("%d", &op8);
                        t = clock();
                        switch(op8)
                        {
                            case 1: selectionSort(&usuario, tam, &C, &M); break;
                            case 2: insertSort(&usuario, tam, &C, &M); break;
                            case 3: bubbleSort(&usuario, tam, &C, &M); break;
                            case 4: shellSort(&usuario, tam, &C, &M); break;
                            case 5: quickSort(&usuario, 0, tam-1, &C, &M); break;
                            case 6: mergeSort(&usuario, 0, tam-1, &C, &M); break;
                            default: printf("\n\n Opcao nao valida\n");
                        }
                        t = clock() - t;
                        printf("C(n) = %d\nM(n) = %d\n", C, M);
                        printf("Tempo de execucao: %lfms\n", ((double)t)/((CLOCKS_PER_SEC/1000)));
                        break;

                case 9: system("cls");
                        imprimirListaS(usuario, tam);
                        break;

                case 10: escreverListaArquivoS(fileS, tam, usuario); break;

                case 11:lerListaArquivoS(fileS, tam, usuario);
                        break;

                case 12: continue;
                default: printf("\n\n Opcao nao valida\n");
            }
            system("pause");
            system("cls"); //Limpa o buffer de entrada
            C = 0; M = 0;
        }while (op != 12);

        free(usuario);

        return 0;
    }

}

void listaEncadeada(Tcliente **cabeca, Tcliente **inicio ,FILE* fp)
{
    char info[2*TAM];
    char *nome, *RG;//Armazena Nome RG
    Tcliente *anterior;

        while(fgets(info, 30, fp) != NULL){
            *cabeca = (Tcliente*) malloc(sizeof(Tcliente));
            nome = (char*) strtok(info, ",");
            strcpy((*cabeca)->nome, nome);
            RG = (char*) strtok (NULL, ",");
            (*cabeca)->RG = atoi(RG);
            (*cabeca)->proximo = NULL;
            if(*inicio == NULL){
                *inicio = *cabeca;
            }
            else{
                anterior->proximo = *cabeca;
            }
            anterior = *cabeca;
        }//Cria uma Lista Encadeada
}

Tcliente* listaSequencial(FILE* fp, int linhas, int* tam)
{
    Tcliente *usuario;
    char info[2*TAM], *pedaco, nome[TAM];

    usuario = (Tcliente*) malloc(sizeof(Tcliente)*linhas);
    while((fgets(info, 50, fp))!= NULL){
        //O pedaço recolhe as informações do arquivo dividindo o nome e o RG
        pedaco = (char*) strtok(info, ",");
        strcpy(usuario[(*tam)].nome, pedaco);
        pedaco = (char*) strtok (NULL, ",");
        usuario[(*tam)].RG = atoi(pedaco);
        usuario[(*tam)].proximo = NULL;
        (*tam)++;
    }

    return usuario;
}

Tcliente* criaçãoDeNo()
{
    Tcliente *novoNo;
    char nome[30];
    int RG;

    printf("Digite o nome do Cliente: \n");
    scanf("%s", nome);
    printf("Digite seu RG: \n");
    scanf("%d", &RG);
    //Criação de Novo Nó
    novoNo = (Tcliente*) malloc(sizeof(Tcliente));
    strcpy(novoNo->nome, nome);
    novoNo->RG = RG;
    novoNo->proximo = NULL;

    return novoNo;
}

int getRG()
{
    int RG;
    
    printf("Digite o RG da pessoa que deseja encontrar: \n");
    scanf("%d", &RG);

    return RG;
}

int getPos(int caso, int tam)
{
    int pos;

    do{
        if(caso == 0){
            printf("Escolha a posicao que deseja incluir: (0 a %d)\n", tam);
            scanf("%d", &pos);
        }
        else{
            printf("Escolha a posicao que deseja excluir: (0 a %d)\n", tam);
            scanf("%d", &pos);
        }
    }while(pos < 0 || pos > tam);

    return pos;
}

int getListaTam(Tcliente *cabeca){
    int tam = 0;
    while (cabeca != NULL){
        cabeca = cabeca->proximo; //faz cabe�a apontar para o proximo n�
        tam++;
    }
    return tam;
}

void inserirClienteInicioE(Tcliente **inicio, int *C, int *M)
{
    Tcliente *novoNo = criaçãoDeNo();
    novoNo->proximo = *inicio;
    (*inicio) = novoNo;
    *M = 1;
    *C = 2;
}

void inserirClienteFinalE(Tcliente **final, int *C, int *M)
{
    Tcliente *novoNo = criaçãoDeNo();
    (*final)->proximo = novoNo;
    *final = novoNo;
    *M = 1;
    *C = 2;
}

void inserirClienteE(Tcliente **cabeca, int *C, int *M)
{
    Tcliente *novoNo;
    Tcliente *posA = *cabeca,
    *posB = (*cabeca)->proximo;
    int pos = getPos(0, getListaTam(*cabeca));
    (*C)++;

    if(pos == 0)
        inserirClienteInicioE(cabeca, C, M);
    else{
        novoNo = criaçãoDeNo();
        for(int i = 1; i < pos; i++){
            posA = posA->proximo;
            posB = posB->proximo;
            *M = *M + 2;
            (*C)++;
        }
        posA->proximo = novoNo;
        novoNo->proximo = posB;
        *M = *M + 2;
    }
}

void inserirClienteInicioS(Tcliente **usuario, int tam, int* C, int *M)
{
    Tcliente *pessoa = criaçãoDeNo();

    for(int i = tam-1; i > 0; i--){
        strcpy((*usuario)[i].nome, (*usuario)[i-1].nome);
        (*usuario)[i].RG = (*usuario)[i-1].RG;
        *M = *M + 1;
        *C = *C + 1;
    }
    strcpy((*usuario)[0].nome, pessoa->nome);
    (*usuario)[0].RG = pessoa->RG;
}

void inserirClienteFinalS(Tcliente **usuario, int tam, int* C, int *M)
{
    Tcliente *pessoa = criaçãoDeNo();
    
    strcpy((*usuario)[tam-1].nome, pessoa->nome);
    (*usuario)[tam-1].RG = pessoa->RG;
}

void inserirClienteS(Tcliente **usuario, int tam, int *C, int *M)
{
    int pos = getPos(0, tam-1);
    Tcliente *pessoa = criaçãoDeNo();
    
    for(int i = tam-1; i > 0; i--){
        *C = *C + 2;
        if(i == pos)
            break;

        strcpy((*usuario)[i].nome, (*usuario)[i-1].nome);
        (*usuario)[i].RG = (*usuario)[i-1].RG;
        *M = *M + 1;
    }
    *C = *C + 1;

    strcpy((*usuario)[pos].nome, pessoa->nome);
    (*usuario)[pos].RG = pessoa->RG;
}

void removerClienteInicioE(Tcliente** inicio, int *C, int *M)
{
    Tcliente *tpm = (*inicio)->proximo;
    free((*inicio));
    (*inicio) = tpm;
    *M = 2;
}

void removerClienteFinalE(Tcliente** cabeca, int *C, int *M)
{
    Tcliente *ultimoNo, *penultimoNo;
    *C = 2;
    ultimoNo = *cabeca;
    *M = 1;
    while (ultimoNo->proximo != NULL){
        *C = *C + 1;
        penultimoNo = ultimoNo;
        ultimoNo = ultimoNo->proximo;
        *M = *M + 2;
    }
    *C = *C + 1;

    free(ultimoNo);
    penultimoNo->proximo = NULL;
    *M = *M + 1;
}

void removerClienteE(Tcliente** cabeca, int *C, int *M)
{
    int pos = getPos(-1, getListaTam(*cabeca)-1);
    Tcliente *posA = *cabeca;
    Tcliente *posB = (*cabeca)->proximo;
    *C = 3;
    *M = 2;

    if(pos == 0)
        removerClienteInicioE(cabeca, C, M);
    else{
        for(int i = 1; i < pos; i++){
            *C = *C + 1;
            posA = posA->proximo;
            posB = posB->proximo;
        }
        posA->proximo = posB->proximo;
        free(posB);
    }
}

void removerClienteInicioS(Tcliente** usuario, int tam, int* C, int *M)
{
    for(int i = 0; i < tam; i++){
        *C = *C + 1;
        *M = *M + 1;
        strcpy((*usuario)[i].nome, (*usuario)[i+1].nome);
        (*usuario)[i].RG = (*usuario)[i+1].RG;
    }
    (*usuario) = (Tcliente*) realloc((*usuario), sizeof(Tcliente)*tam);
}

void removerClienteFinalS(Tcliente** usuario, int tam, int* C, int* M)
{
    (*usuario) = (Tcliente*) realloc((*usuario), sizeof(Tcliente)*tam);
}

void removerClienteS(Tcliente** usuario, int tam, int *C, int *M)
{
    int pos = getPos(-1, tam);

    for(int i = 0; i < tam; i++){
        if(i >= pos){
            strcpy((*usuario)[i].nome, (*usuario)[i+1].nome);
            (*usuario)[i].RG = (*usuario)[i+1].RG;
            *M = *M + 1;
        }
    }
    (*usuario) = (Tcliente*) realloc((*usuario), sizeof(Tcliente)*tam);
}

void buscarClienteE(Tcliente *cabeca, int *C, int *M)
{
    int RG = getRG(), Encontrou = 0;
    int i = 0;

    *C = 0;
    *M = 0;

    while(cabeca != NULL){
        *C = *C + 1;
        if(RG == cabeca->RG){
            Encontrou = 1;
            printf("Nome: %s, ", cabeca->nome);
            printf("RG: %d e Posicao: %d\n\n", cabeca->RG, i);
            break;
        }
        i++;
        cabeca = cabeca->proximo;
        *M = *M + 1;
    }

    if(Encontrou == 0)
        printf("Sinto muito, %d nao foi encontrado.\n\n", RG);
}

void buscarClienteS(Tcliente *usuario, int tam, int *C, int *M)
{
    int RG = getRG(), Encontrou = 0;

    for(int i = 0; i < tam; i++){
        *C = *C + 2;
        *M = *M + 1;
        if(usuario[i].RG == RG){
            Encontrou = 1;
            printf("\n\nNome: %s, ", usuario[i].nome);
            printf("RG: %d e Posicao: %d\n\n", usuario[i].RG, i);
            break;
        }
    }
    *C = *C + 1;
    if(Encontrou == 0)
        printf("Sinto muito, %d nao foi encontrado.\n\n", RG);
}

void buscarClienteBinario(Tcliente *usuario, int tam, int *C, int *M)
{
    int RG = getRG(), Encontrou = 0, meio, inic = 0;
    
    *C = 3;
    while(inic <= tam){
        *C = *C + 1;
        *M = *M + 1;
        meio = (inic+tam)/2;
        if(usuario[meio].RG == RG){
            *C = *C + 1;
            Encontrou = 1;
            printf("\n\nNome: %s, ", usuario[meio].nome);
            printf("RG: %d e Posicao: %d\n\n", usuario[meio].RG, meio);
            break;
        }
        else if(usuario[meio].RG < RG){
            *C = *C + 2;
            *M = *M + 1;
            inic = meio+1;
        }
        else{
            *C = *C + 3;
            *M = *M + 1;
            tam = meio-1;
        }
    }
    *C = *C + 1;
    if(Encontrou == 0)
        printf("Sinto muito, %d nao foi encontrado.\n\n", RG);
}

void imprimirListaE (Tcliente *cabeca)
{
    int i = 0;
    while (cabeca != NULL){
        printf("\nCliente: %s, RG: %d, Posicao: %d\n", cabeca->nome, cabeca->RG, i);
        cabeca = cabeca->proximo; //faz cabe�a apontar para o proximo n�
        i++;
    }
}

void imprimirListaS(Tcliente *usuario, int tam)
{
    for(int i = 0; i < tam; i++)
    {
        printf("Nome: %s, ", usuario[i].nome);
        printf("RG: %d e Posicao: %d\n\n", usuario[i].RG, i);
    }
}

void selectionSort(Tcliente **usuario, int tam, int *C, int *M)
{
    Tcliente elem;
    printf("tam = %d\n", tam);

    for(int i = 0; i < tam; i++){
        elem = (*usuario)[i];
        *C = *C + 2;
        *M = *M + 1;
        for(int j = i+1; j < tam; j++){
            *C = *C + 1;
            if(elem.RG > (*usuario)[j].RG){
                elem = (*usuario)[j];
                (*usuario)[j] = (*usuario)[i];
                (*usuario)[i] = elem;
                *M = *M + 3;
            }
        }
    }
}

void insertSort(Tcliente **usuario, int tam, int *C, int *M)
{
    Tcliente elem;

    for(int i = 1; i < tam; i++){
        *C = *C + 2;
        *M = *M + 1;
        int j = i-1;
        elem = (*usuario)[i];
        while(elem.RG < (*usuario)[j].RG){
            (*usuario)[j+1] = (*usuario)[j];
            (*usuario)[j] = elem;
            j--;
            *M = *M + 2;
        }
    }
}

void bubbleSort(Tcliente **usuario, int tam, int *C, int *M)
{
    Tcliente elem;

        for(int i = 0; i < tam; i++){
            *C = *C + 2;
            for(int j = 0; j < tam - i - 1; j++){
                if((*usuario)[j].RG > (*usuario)[j + 1].RG){
                    elem = (*usuario)[j];
                    (*usuario)[j] = (*usuario)[j+1];
                    (*usuario)[j+1] = elem;
                    *M = *M + 3;
                }
            }
        }
        *C = *C + 1;
}

void shellSort(Tcliente **usuario, int tam, int *C, int *M)
{
    int h = 1;
    Tcliente elem;

    while(h < tam){
        h = 3*h+1;
        *C = *C + 1;
    }
    *C = *C + 1;

    do{
        h = h/3;
        for(int i = h; i < tam; i++){
            elem = (*usuario)[i];
            int j = i - h;
            *C = *C + 1;
            *M = *M + 1;
            while((j >= 0) && (elem.RG < (*usuario)[j].RG)){
               (*usuario)[j+h] = (*usuario)[j];
               j = j - h;
               (*usuario)[j+h] = elem;
               *M = *M + 2;
            }
        }
        *C = *C + 2;
    }while(h > 1);
}

void quickSort(Tcliente **usuario, int inicio, int fim, int *C, int *M)
{
    int elemAux;
    char nomeAux[TAM];
    int pivo = (*usuario)[(inicio + fim)/2].RG;
    int i = inicio, j = fim;

    do{
        *C = *C + 1;
        while((*usuario)[i].RG < pivo){
            i++;
            *C = *C + 1;
        }
        *C = *C + 1;
        while((*usuario)[j].RG > pivo){
            j--;
            *C = *C + 1;
        }
        *C = *C + 1;
        if(i <= j){
            elemAux = (*usuario)[i].RG;
            strcpy(nomeAux, (*usuario)[i].nome);

            (*usuario)[i].RG = (*usuario)[j].RG;
            strcpy((*usuario)[i].nome, (*usuario)[j].nome);

            (*usuario)[j].RG = elemAux;
            strcpy((*usuario)[j].nome, nomeAux);

            *M = *M + 3;

            i++;
            j--;
        }
    }while(i <= j);

    *C = *C + 2;
    if(j > inicio){
        quickSort(&(*usuario), inicio, j, C, M);
    }
    if(i < fim){
        quickSort(&(*usuario), i, fim, C, M);
    }
}

void mergeSort(Tcliente **usuario, int inicio, int fim, int *C, int *M)
{
    int metade;
    if(inicio < fim){
        *C = *C + 1;
        metade = inicio + (fim - inicio)/2;
        mergeSort(&(*usuario), inicio, metade, C, M);
        mergeSort(&(*usuario), (metade + 1), fim, C, M);
        merge((*usuario), inicio, metade, fim, C, M);
    }
}

void merge(Tcliente *usuario, int inicio, int meio, int fim, int *C, int *M)
{
    int i, j, k;
    int n1 = meio - inicio +1;
    int n2 = fim - meio;
    Tcliente *L, *R;

    L = (Tcliente*) malloc (sizeof(Tcliente)*n1);
    R = (Tcliente*) malloc (sizeof(Tcliente)*n2);

    for(i = 0; i < n1; i++){
        *C = *C + 1;
        *M = *M + 1;
        L[i] = usuario[inicio + i];
    }
    for(j = 0; j < n2; j++){
        *C = *C + 1;
        *M = *M + 1;
        R[j] = usuario[meio + 1 + j];
    }
    *C = *C + 2;

    i = 0;
    j = 0;
    k = inicio;
    while(i < n1 && j < n2){
        *C = *C + 1;
        if(L[i].RG <= R[j].RG){
            *C = *C + 1;
            *M = *M + 1;
            usuario[k] = L[i];
            i++;
        }
        else{
            *C = *C + 2;
            *M = *M + 1;
            usuario[k] = R[j];
            j++;
        }
        k++;
    }
    *C = *C + 1;
    while(i < n1){
        *C = *C + 1;
        *M = *M + 1;
        usuario[k] = L[i];
        i++;
        k++;
    }
    *C = *C + 1;
    while(j < n2){
        *C = *C + 1;
        *M = *M + 1;
        usuario[k] = R[j];
        j++;
        k++;
    }
    *C = *C + 1;
    free(L);
    free(R);
}

void escreverListaArquivoE(FILE *fp, Tcliente* cabeca)
{
    char arq[TAM];
    char pasta[TAM] = "PastaDeLista/NomeRG/";

    printf("Informe o nome do arquivo a ser Escrito: \n");
    scanf("%s", arq);
    
    strcat(pasta, arq);
    fp = fopen(pasta, "w");
    while(cabeca->proximo != NULL){
        fprintf(fp, "%s,%d\n", cabeca->nome, cabeca->RG);
        cabeca = cabeca->proximo;
    }
    fprintf(fp, "%s,%d\n", cabeca->nome, cabeca->RG);
    fclose(fp);
}

void lerListaArquivoE(FILE *fp, Tcliente *cabeca)
{
    char arq[TAM];
    char pasta[TAM] = "PastaDeLista/NomeRG/";

        char c;
        printf("Informe o nome do arquivo a ser lido: \n");
        scanf("%s", arq);

        strcat(pasta, arq);
        fp = fopen(pasta, "r");

        if(NULL == fp) {
            printf("O arquivo nao pode ser aberto =(.\n");
            system("Pause");
            exit(1);
        }
        printf("\nImprimindo...\n");
        c = fgetc(fp);
        while (!feof(fp)) {
            putchar(c);
            c = fgetc(fp);
        }

        fclose(fp);
}

void escreverListaArquivoS(FILE *fp, int tam, Tcliente *usuario)
{
    char arq[TAM];
    char pasta[TAM] = "PastaDeLista/NomeRG/";

    printf("Informe o nome do arquivo a ser Escrito: \n");
    scanf("%s", arq);
    strcat(pasta, arq);
    fp = fopen(pasta, "w");

    for(int i = 0; i < tam; i++){
        fprintf(fp, "%s,%d\n", usuario[i].nome, usuario[i].RG);
    }
    fclose(fp);
}

void lerListaArquivoS(FILE *fp, int tam,Tcliente *usuario)
{
    char arq[TAM];
    char pasta[TAM] = "PastaDeLista/NomeRG/";

    char c;
    printf("Informe o nome do arquivo a ser lido: \n");
    scanf("%s", arq);

    strcat(pasta, arq);
    fp = fopen(pasta, "r");

    if(NULL == fp) {
        printf("O arquivo nao pode ser aberto =(.\n");
        system("Pause");
        exit(1);
    }
    printf("\nImprimindo...\n");
    c = fgetc(fp);
    while (!feof(fp)) {
        putchar(c);
        c = fgetc(fp);
    }
}
