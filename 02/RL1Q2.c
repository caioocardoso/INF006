#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define STR_MAX 50

typedef struct
{
    char elementos[MAX][STR_MAX];
    int topo;
} Pilha;

int main()
{
    FILE *fp_in = fopen("C:\\Users\\caioo\\Projects\\INF006\\02\\L1Q2.in", "r");
    FILE *fp_out = fopen("C:\\Users\\caioo\\Projects\\INF006\\02\\L1Q2.out", "w");

    if (fp_in == NULL || fp_out == NULL)
    {
        printf("Erro ao abrir os arquivos.\n");
        return EXIT_FAILURE;
    }


    char linha[1000];
    while (fgets(linha, sizeof(linha), fp_in))
    {
        char *novoElemento = strtok(linha, " \n");
        Pilha pilha;
        pilha.topo = 0;
        while (novoElemento)
        {
            insercaoOrdenada(&pilha, novoElemento, fp_out);
            novoElemento = strtok(NULL, " \n");
        }
        fprintf(fp_out, "\n");
    }
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}

int isEmpty(Pilha *pilha)
{
    return pilha->topo == 0;
}

int isFull(Pilha *pilha)
{
    return pilha->topo == MAX;
}

void insercaoOrdenada(Pilha *pilha, char *novoElemento, FILE *fp_out)
{
    Pilha temp;
    temp.topo = 0;
    char elemento[STR_MAX];
    int popCount = 0;

    while (!isEmpty(pilha) && strcmp(pilha->elementos[pilha->topo - 1], novoElemento) > 0)
    {
        pop(pilha, elemento);
        popCount++;
        push(&temp, elemento);
    }
    if (popCount > 0)
    {
        fprintf(fp_out, "%dx-pop ", popCount);
    }

    push(pilha, novoElemento);
    fprintf(fp_out, "push-%s ", novoElemento);

    while (!isEmpty(&temp))
    {
        pop(&temp, elemento);
        push(pilha, elemento);

        fprintf(fp_out, "push-%s ", elemento);
    }
}

void push(Pilha *pilha, char *elemento)
{
    if (isFull(pilha))
    {
        printf("pilha cheia.\n");
        return;
    }
    strcpy(pilha->elementos[pilha->topo++], elemento);
}

void pop(Pilha *pilha, char *elemento)
{
    if (isEmpty(pilha))
    {
        printf("pilha vazia.\n");
        return;
    }
    strcpy(elemento, pilha->elementos[--pilha->topo]);
}