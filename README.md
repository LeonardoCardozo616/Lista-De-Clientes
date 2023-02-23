# Lista de Clientes
***
 Trata-se de um programa em linguagem C, que é capaz de listar uma quantidade de clientes e seus respectivos RGs.
 
 As listas de clientes estão contidas na pasta `PastaDeLista\\NomeRG`, cada lista contém um nome seguido de um RG.
 Exemplo: **NomeRG10.txt**
```
Paulo,82475249
Ricardo,84943658
Luiza,70211272
Carla,57850878
Paula,7237709
Luiza,15438165
Ana,74243042
Paulo,37522503
Ricardo,16531729
Claudia,43542612
```
Arquivos como esse são inseridos no programa e cada cliente faz parte de uma struct chamada **Tcliente**.
```
typedef struct tipo_cliente
{
    char nome[TAM];
    int RG;
    struct tipo_cliente *proximo;
}Tcliente;
```
A lista dentro do programa pode funcionar como uma ***lista encadeada*** ou uma ***lista sequencial***.
## Lista Encadeada
Essa lista se utiliza da struct **Tcliente**, criando um nó que possui o nome do cliente e seu RG, o ponteiro **\*proximo** aponta para o próximo nó e será encerrado somente quando todos os nomes forem armazenados.
```
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
```
## Lista Sequencial
Apesar de utilizar a struct **Tcliente**, ela não utiliza o ponteiro **\*proximo**, ao invés disso, ela é iniciada como um __array__ e ao contrário da lista encadeada, esta possui posições definidas.
```
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
```
## Menu Principal
No Menu é possível editar a lista, incluindo novos clientes ou excluindo-os, também existe busca por um cliente da lista através de seu RG, ordenar a lista em ordem crescente (__Disponível apenas na lista Sequencial__), impressão da lista completa e criação de um arquivo da lista modificada pelo usuário, além de ser possível acessar qualquer arquivo dentro da pasta `PastaDeLista\\NomeRG` e imprimir no próprio terminal.
```
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
```
