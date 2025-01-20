#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LISTS 100
#define MAX_NUMBERS 100

typedef struct {
    int numbers[MAX_NUMBERS];
    int size;
    int sum;
} List;

void read_input(const char *L1Q1, List lists[], int *list_count) {
    FILE *file = fopen(L1Q1, "r");
    if (!file) {
        perror("Erro ao abrir o arquivo de entrada");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int current_list = -1;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, " ");
        while (token) {
            if (strcmp(token, "start") == 0) {
                current_list++;
                lists[current_list].size = 0;
                lists[current_list].sum = 0;
            } else {
                int num = atoi(token);
                lists[current_list].numbers[lists[current_list].size++] = num;
                lists[current_list].sum += num;
            }
            token = strtok(NULL, " ");
        }
    }

    *list_count = current_list + 1;
    fclose(file);
}

int compare_lists(const void *a, const void *b) {
    List *listA = (List *)a;
    List *listB = (List *)b;
    return listA->sum - listB->sum;
}

void sort_lists(List lists[], int list_count) {
    for (int i = 0; i < list_count; i++) {
        qsort(lists[i].numbers, lists[i].size, sizeof(int), (int (*)(const void *, const void *))strcmp);
    }
    qsort(lists, list_count, sizeof(List), compare_lists);
}

void write_output(const char *L1Q1, List lists[], int list_count) {
    FILE *file = fopen(L1Q1, "w");
    if (!file) {
        perror("Erro ao abrir o arquivo de saída");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < list_count; i++) {
        fprintf(file, "start");
        for (int j = 0; j < lists[i].size; j++) {
            fprintf(file, " %d", lists[i].numbers[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    const char *input_file = "L1Q1.in";
    const char *output_file = "L1Q1.out";
    List lists[MAX_LISTS];
    int list_count;

    read_input(input_file, lists, &list_count);
    sort_lists(lists, list_count);
    write_output(output_file, lists, list_count);

    return 0;
}
