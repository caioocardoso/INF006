#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_MAX_LINHA 1000

// Estrutura de Node2 (Lista Duplamente Encadeada para os números 'LE')
typedef struct Node2 {
    int key;
    struct Node2* anterior;
    struct Node2* proximo;
    struct NodeC* sublista;  // Sublista circular para o número 'LE'
} Node2;

// Estrutura de NodeC (Lista Circular para os números 'LI')
typedef struct NodeC {
    float key;
    struct NodeC* proximo;
} NodeC;

// Funções para manipular as listas
Node2* criarNode2(int key);
void inserirNode2Ordenado(Node2** primeiro2, int key);
void inserirNodeCOrdenado(NodeC** primeiroC, float valor);
void inserirSublista(Node2* node, float valor);
void imprimirSaida(Node2* primeiro2, FILE* saida);

int main() {
    FILE* saida = fopen("L1Q3.out", "w");
    FILE* entrada = fopen("L1Q3.in", "r");
    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 0;
    }

    char linha[TAM_MAX_LINHA];
    while (fgets(linha, TAM_MAX_LINHA, entrada) != NULL) {
        Node2* primeiro2 = NULL;  // Inicia a lista de Node2

        char* token = strtok(linha, " ");  // Separa os tokens por espaço
        int le = 0, li = 0;
        while (token != NULL) {
            if (strcmp(token, "LE") == 0) {
                le = 1;  // Ativa o modo LE
                li = 0;  // Desativa o modo LI
            } else if (strcmp(token, "LI") == 0) {
                li = 1;  // Ativa o modo LI
                le = 0;  // Desativa o modo LE
            } else if (le == 1) {
                int valor = atoi(token);
                inserirNode2Ordenado(&primeiro2, valor);
            } else if (li == 1) {
                float valor = atof(token);
                Node2* listagem = primeiro2;
                while (listagem != NULL) {
                    // Verifica a condição LI > LE && LI < LE + 0.99
                    if (valor > listagem->key && valor < (listagem->key + 0.99)) {
                        inserirSublista(listagem, valor);
                    }
                    listagem = listagem->proximo;
                }
            }
            token = strtok(NULL, " ");
        }

        imprimirSaida(primeiro2, saida);
    }

    fclose(entrada);
    fclose(saida);
    return 0;
}

// Cria um novo Node2
Node2* criarNode2(int key) {
    Node2* novo = (Node2*)malloc(sizeof(Node2));
    novo->key = key;
    novo->anterior = NULL;
    novo->proximo = NULL;
    novo->sublista = NULL;
    return novo;
}

// Insere um novo Node2 de forma ordenada
void inserirNode2Ordenado(Node2** primeiro2, int key) {
    Node2* novo = criarNode2(key);
    if (*primeiro2 == NULL) {
        *primeiro2 = novo;
    } else {
        Node2* atual = *primeiro2;
        Node2* anterior = NULL;
        while (atual != NULL && atual->key < key) {
            anterior = atual;
            atual = atual->proximo;
        }

        if (anterior == NULL) {  // Insere no início
            novo->proximo = *primeiro2;
            (*primeiro2)->anterior = novo;
            *primeiro2 = novo;
        } else {
            anterior->proximo = novo;
            novo->anterior = anterior;
            novo->proximo = atual;
            if (atual != NULL) {
                atual->anterior = novo;
            }
        }
    }
}

// Cria um novo NodeC (para a sublista circular)
NodeC* criarNodeC(float key) {
    NodeC* novo = (NodeC*)malloc(sizeof(NodeC));
    novo->key = key;
    novo->proximo = NULL;
    return novo;
}

// Insere um NodeC na sublista de forma ordenada (circular)
void inserirNodeCOrdenado(NodeC** primeiroC, float valor) {
    NodeC* novo = criarNodeC(valor);
    if (*primeiroC == NULL) {
        *primeiroC = novo;
        novo->proximo = novo;  // Circular
    } else {
        NodeC* atual = *primeiroC;
        NodeC* anterior = NULL;
        while (atual->proximo != *primeiroC && atual->key < valor) {
            anterior = atual;
            atual = atual->proximo;
        }

        if (valor <= atual->key) {  // Insere antes do primeiro
            if (anterior != NULL) {
                anterior->proximo = novo;
            } else {
                NodeC* temp = *primeiroC;
                while (temp->proximo != *primeiroC) {
                    temp = temp->proximo;
                }
                temp->proximo = novo;
                *primeiroC = novo;
            }
            novo->proximo = atual;
        } else {  // Insere depois
            atual->proximo = novo;
            novo->proximo = *primeiroC;
        }
    }
}

// Insere um número LI na sublista circular associada ao Node2
void inserirSublista(Node2* node, float valor) {
    if (node->sublista == NULL) {
        node->sublista = criarNodeC(valor);
        node->sublista->proximo = node->sublista;  // Circular
    } else {
        inserirNodeCOrdenado(&(node->sublista), valor);
    }
}

// Função para imprimir a saída
void imprimirSaida(Node2* primeiro2, FILE* saida) {
    fprintf(saida, "[");
    Node2* listagemPai = primeiro2;
    while (listagemPai != NULL) {
        fprintf(saida, "%d", listagemPai->key);
        fprintf(saida, "(");
        if (listagemPai->sublista != NULL) {
            NodeC* listagemC = listagemPai->sublista;
            do {
                // Usando %.10g para evitar zeros extras na impressão
                fprintf(saida, "%.3g", listagemC->key);
                listagemC = listagemC->proximo;
                if (listagemC != listagemPai->sublista) {
                    fprintf(saida, "->");
                }
            } while (listagemC != listagemPai->sublista);
        }
        fprintf(saida, ")");
        if (listagemPai->proximo != NULL) {
            fprintf(saida, "->");
        }
        listagemPai = listagemPai->proximo;
    }
    fprintf(saida, "]\n");
}

