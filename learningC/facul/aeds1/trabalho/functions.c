#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include <unistd.h>

// inserir no final da lista
void inserirFim(lista *lista, char *valor, char *nome){
    if(lista->tam >= MAX_LENGHT){
        puts("Lista Cheia!!! Remova algum arquivo para poder inserir um novo");
        return;
    }

    no *atual = (no*)malloc(sizeof(no)); // cria um novo nó
    strcpy(atual->conteudo, valor);
    strcpy(atual->nome_do_arquivo, nome);
    atual->prox = NULL;

    if(lista->cab == NULL) { // lista vazia
        lista->cab = atual;
        lista->ret = atual;
    } else { // lista não vazia
        lista->ret->prox = atual;
        lista->ret = atual;
    }
    lista->tam++;
}


void leitura(lista *lista){
    system("clear");

    char arq[50];
    printf("Digite o nome do arquivo que deseja inserir:\n");
    scanf("%s", arq);

    FILE *textfile;
    char texto[MAX_LINE_LENGTH];
    textfile = fopen(arq, "r");
    if(textfile == NULL){
        printf("Arquivo vazio ou Não encontrado\n");
        return;
    }
    while(fgets(texto, MAX_LINE_LENGTH, textfile)){
        inserirFim(lista, texto, arq);
    }
    fclose(textfile);

    puts("Arquivo Inserido!");
    printf("Tamanho atual da lista: %d\n", lista->tam);
    
}


conteudo_buscado *busca(lista *lista, char *arq){
    no *atual = lista->cab;
    no *inicial = NULL;
    no *anterior = NULL;
    conteudo_buscado * conteudo = (conteudo_buscado *)malloc(sizeof(conteudo_buscado));

    if(atual == NULL){ // lista vazia
        puts("Lista Vazia! Insira algum arquivo para poder busca-lo");
        return conteudo;
    }

    while(strcmp(atual->nome_do_arquivo,arq) != 0){//while que verifica se chegou no nome do arquivo.
        if(atual->prox == NULL ){
            puts("Arquivo ainda não foi inserido na lista!");
            return conteudo;
        }
        anterior = atual;
        atual = atual->prox;
    }


    inicial = atual;

    conteudo->inicial = inicial;
    conteudo->anterior = anterior;
    return conteudo;
}


void imprimir_arq(lista *lista){
    system("clear");
    
    char arq[50];
    printf("Digite o nome do arquivo que deseja buscar: ");
    scanf("%s", arq);

    conteudo_buscado *arquivo = busca(lista, arq);
    no *atual = arquivo->inicial;

    if(atual == NULL){
        return;
    }

    if(arquivo != NULL){
        int count = 1;
        while(strcmp(atual->nome_do_arquivo,arq) == 0){//esse while percorre o arquivo desejado.
            if(atual->prox == NULL){
                printf("%d - %p\n", count, atual);
                break;
            }else{
                printf("%d - %p\n", count, atual);
                count++;
                atual = atual->prox;
            }
        }
        puts("");
    }
}

void buscar_termo(lista *lista){
    system("clear");

    char arq[20];
    printf("Digite o termo que deseja procurar: \n");
    scanf("%s", arq);
    
    no *atual = lista->cab;
    no *anterior = lista->cab;
    int contador = 0, indice = 0;

    if(atual == NULL){
        printf("Parece que a lista ainda está vazia!\nInsira algum arquivo antes de procurar algum termo!\n");
        return;
    }

    while(atual != NULL){
        
        if(strcmp(atual->nome_do_arquivo, anterior->nome_do_arquivo) != 0){ //aqui verifica se ta transicionando de arquivo... tem que printar o nome do anterior e o contador, mas nao pode esquecer de zerar o contador depois do print
            printf("%s - %d\n", anterior->nome_do_arquivo, contador);
            contador = 0;
        }

        do{
            indice = existe(atual->conteudo, arq, indice);
            printf("%d\n", indice);
            if(indice != -1)
                contador++;
        }while(indice != -1);

        if(atual->prox == NULL) //Esse if serve pra caso seja o ultimo arquivo da lista, ainda assim imprima!
            printf("%s - %d\n", anterior->nome_do_arquivo, contador);

        indice = 0;

        anterior = atual;
        atual = atual->prox;
    }

}

void remover_arq(lista *lista){
    system("clear");

    char arq[50];
    printf("Digite o nome do arquivo que deseja remover: ");
    scanf("%s", arq);

    conteudo_buscado *arquivo = busca(lista, arq);
    no *atual = arquivo->inicial;
    no *aux;
    
    if (atual == NULL){
        return;
    }
    if(arquivo->anterior){ //verificando se não é o primeiro da lista
        aux = arquivo->anterior;
        while(strcmp(atual->nome_do_arquivo,arq) == 0 && aux->prox != NULL){//esse while percorre o arquivo desejado.
            aux->prox = atual->prox;
            free(atual);
            lista->tam--;
            if(aux->prox == NULL){
                lista->ret = aux;
                break;
            }
            atual = aux->prox;
        }
    }else{
        while(strcmp(atual->nome_do_arquivo,arq) == 0 && atual != NULL){
            aux = atual;
            aux->prox = atual->prox;
            free(atual);
            atual = aux->prox;
            lista->tam--;
            if(atual == NULL){
                lista->cab = NULL;
                lista->ret = NULL;
                break;
            }
        }
        lista->cab = atual;
    }
}

void imprimir_lista(lista *lista){
    no *cab = lista->cab;
    int count = 1;
    while(cab != NULL){
        printf("Nó - %d\n", count);
        printf("  Nome do arquivo - %s\n", cab->nome_do_arquivo);
        printf("  Endereço - %p\n", cab);
        printf("  Conteudo - %s\n", cab->conteudo);
        cab = cab->prox;
        count++;
    }
    printf("Tamanho da lista: %d\n", lista->tam);
    printf("\n");
}

int existe(char *str1, char *str2, int indice){
    int i, aux = 0;

    for(i = indice; i < strlen(str1); i++){
        if(str1[i] == str2[aux])
            aux++;
        else
            aux = 0;
        if(aux == strlen(str2))
            return i;
    }
    return -1;
}