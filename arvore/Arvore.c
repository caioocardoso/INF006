#include <stdio.h>
#include <stdlib.h>

typedef struct No No;

typedef struct No {
    int valor;
    No *esquerda;
    No *direita;
} No;

No *inserir(No *raiz, int valor){
    if(raiz == NULL){
        No *novo = (No*)malloc(sizeof(No));
        novo->valor = valor;
        novo->esquerda = NULL;
        novo->direita = NULL;
        return novo;
    }
    else{
        if(valor < raiz->valor)
            raiz->esquerda = inserir(raiz->esquerda, valor);
        if(valor > raiz->valor)
            raiz->direita = inserir(raiz->direita, valor);
    }
    return raiz;
}


No *minValorNo(No *raiz){
    No *atual = raiz;
    while(atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

No *remover(No *raiz, int valor){
    if(raiz == NULL)
        return raiz;
    if(valor < raiz->valor)
        raiz->esquerda = remover(raiz->esquerda, valor);
    else if(valor > raiz->valor)
        raiz->direita = remover(raiz->direita, valor);
    else {
        if(raiz->esquerda == NULL) {
            No *temp = raiz->direita;
            free(raiz);
            return temp;
        }
        else if (raiz->direita == NULL){
            No *temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        No *temp = minValorNo(raiz->direita);
        raiz->valor = temp->valor;
        raiz->direita = remover(raiz->direita, temp->valor);
    }
    return raiz;
}


void listar(No *raiz){
    if(raiz != NULL){
        listar(raiz->esquerda);
        printf("%d ", raiz->valor);
        listar(raiz->direita);
    }
}

void main()
{
    No *raiz = NULL;
    int escolha = 1;
    int valor;

    while(escolha != 0){
        printf("------------- MENU ------------\n");
        printf("1 - Inserir\n");
        printf("2 - Listar\n");
        printf("3 - Remover\n");
        printf("-------------------------------\n");
        printf("\n");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
        {
            scanf("%d", &valor);
            raiz = inserir(raiz, valor);
            break;
        }
        case 2:
        {
            listar(raiz);
            printf("\n");
            break;
        }
        case 3:
        {
            scanf("%d", &valor);
            raiz = remover(raiz, valor);
            break;
        }
        case 4:
        {
            break;
        }
        default:
        {
            printf("Errou");
            break;
        }
        }
    }
}