# Lista de Clientes
***
 Esse é um programa em linguagem C, que é capaz de aramzenar uma lista de clientes e modificá-la como desejar, utilizando conhecimentos de Estrutura de Dados.
 
 As listas de clientes estão contidas na pasta `PastaDeLista\NomeRG` e cada lista contém um nome seguido de um RG.
 
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
No Menu é possível editar a lista, incluindo novos clientes ou excluindo-os, também existe busca por um cliente da lista através de seu RG, ordenar a lista em ordem crescente (__Disponível apenas na lista Sequencial__), impressão da lista completa e criação de um arquivo da lista modificada pelo usuário, além de ser possível acessar qualquer arquivo dentro da pasta `PastaDeLista\NomeRG` e imprimir no próprio terminal.
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
### Inserção e Remoção de clientes :pushpin: :scissors:
Foram criados 3 opções de inserção e 3 opções de remoção:
 1. __inserir novo cliente no inicio da lista;__
 0. __inserir um novo cliente no final da lista;__
 0. __inserir novo cliente em alguma posicao especifica;__
 0. __retirar o primeiro cliente da lista;__
 0. __retirar o ultimo cliente da lista;__
 0. __retirar um cliente especifico.__
 
Cada uma dessas opções são feitas em funções diferentes. A __primeira__ e a __quarta__ opção insere/remove um cliente na primeira posição, a __segunda__ e a __quinta__ opção insere/remove um cliente no final da lista e a __terceira__ e __sexta__ opção insere/remove um cliente em qualquer posição que o usuário desejar, incluindo a primeira e última posiução.
### Busca de cliente :mag:
Pelo fato de poder existir mais de uma pessoa com o mesmo nome, existe uma grande possibilidade de haver conflitos ao procurar um cliente, por isso, a busca é feita através de seu RG, pois cada um tem seu próprio RG.

Existem duas formas de busca na **lista sequencial**, a primeira que busca observando todos os clientes do primeiro ao último e a [Busca Binária](https://www.youtube.com/watch?v=iP897Z5Nerk&t=39s) que funciona apenas caso a lista esteja ordenada.
### Ordenação :card_file_box:
Eis aqui as 6 ordenações, disponíveis apenas na lista sequencial, com um link explicando o funcionamento de cada uma:
 1. [Selection-sort;](https://www.youtube.com/watch?v=Ns4TPTC8whw&t=5s)
 2. [Insert-sort;](https://www.youtube.com/watch?v=ROalU379l3U)
 3. [Bubble-sort;](https://www.youtube.com/watch?v=lyZQPjUT5B4)
 4. [Shell-sort;](https://www.youtube.com/watch?v=CmPA7zE8mx0&t=12s)
 5. [Quick-sort;](https://www.youtube.com/watch?v=lyZQPjUT5B4)
 6. [Merge-sort.](https://www.youtube.com/watch?v=XaqR3G_NVoo)
 ### Impressão :printer:
 Será impresso a lista, com o nome, RG e Posição, sempre atualizada com as modificações feitas pelo usuário.
 ### Manipulação de arquivos :file_folder:
 Por fim, é possível salvar a lista modificada em um arquivo, que será salva dentro da pasta `PastaDeLista\NomeRG`, e também existe a opção de imprimir no terminal qualquer arquivo que esteja dentro dessa pasta. 
