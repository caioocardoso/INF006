#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da lista
typedef struct Node
{
    int *values;       // Vetor de inteiros
    int size;          // Tamanho do vetor
    int sum;           // Soma dos valores do vetor
    struct Node *next; // Ponteiro para o próximo nó
} Node;

// Função para criar um novo nó
Node *create_node()
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->values = NULL;
    new_node->size = 0;
    new_node->sum = 0;
    new_node->next = NULL;
    return new_node;
}

// Função para inserir um nó na lista em ordem crescente da soma
void insert_node_sorted(Node **head, Node *new_node)
{
    if (*head == NULL || (*head)->sum > new_node->sum)
    {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    Node *current = *head;
    while (current->next != NULL && current->next->sum <= new_node->sum)
    {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;
}

void sort_nodes_by_sum(Node **head) {
    if (*head == NULL || (*head)->next == NULL) {
        // Lista vazia ou com apenas um nó, já está ordenada
        return;
    }

    int swapped;
    Node **current;

    do {
        swapped = 0;
        current = head;

        while ((*current)->next != NULL) {
            if ((*current)->sum > (*current)->next->sum) {
                // Trocar os nós
                Node *temp = *current;
                *current = (*current)->next;
                temp->next = (*current)->next;
                (*current)->next = temp;

                swapped = 1;
            }
            current = &(*current)->next;
        }
    } while (swapped);
}

// Função para adicionar um valor ao vetor de um nó
void add_value_to_node(Node *node, int value)
{
    node->values = (int *)realloc(node->values, (node->size + 1) * sizeof(int));
    node->values[node->size] = value;
    node->sum += value;
    node->size++;
}

// Função para ordenar o vetor dentro de um nó
void sort_node_values(Node *node)
{
    for (int i = 0; i < node->size - 1; i++)
    {
        for (int j = 0; j < node->size - i - 1; j++)
        {
            if (node->values[j] > node->values[j + 1])
            {
                int temp = node->values[j];
                node->values[j] = node->values[j + 1];
                node->values[j + 1] = temp;
            }
        }
    }
}

// Função para liberar a memória da lista
void free_list(Node *head)
{
    while (head != NULL)
    {
        Node *temp = head;
        head = head->next;
        free(temp->values);
        free(temp);
    }
}

// Função para imprimir a lista no formato desejado
void print_list(Node *head, FILE* saida)
{
    while (head != NULL)
    {
        fprintf(saida, "start ");
        for (int i = 0; i < head->size; i++)
        {
            fprintf(saida, "%d ", head->values[i]);
        }
        head = head->next;
    }
        fprintf(saida, "\n");
}

int main()
{
    FILE *fp_in = fopen("L1Q1.in", "r");
    FILE *fp_out = fopen("L1Q1.out", "w");

    if (fp_in == NULL || fp_out == NULL)
    {
        printf("Erro ao abrir os arquivos.\n");
        return EXIT_FAILURE;
    }

    char linha[1000];
    while (fgets(linha, sizeof(linha), fp_in))
    {
        char *token = strtok(linha, " ");

        Node *head = NULL;
        Node *current_node = NULL;

        while (token != NULL)
        {
            if (strcmp(token, "start") == 0)
            {
                current_node = create_node();
                insert_node_sorted(&head, current_node);
                token = strtok(NULL, " ");
                continue;
            }
            else
            {
                // Converter a string para inteiro e adicionar ao nó atual
                int value = atoi(token);
                add_value_to_node(current_node, value);
            }

            if (current_node != NULL)
            {
                Node** PHead = &head;
                sort_node_values(current_node);
                sort_nodes_by_sum(PHead);
            }

            token = strtok(NULL, " ");
        }

        // Imprimir a lista ordenada
        print_list(head, fp_out);

        // Liberar a memória
        free_list(head);
    }
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}