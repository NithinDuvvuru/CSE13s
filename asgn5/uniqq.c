#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256

int main(int argc, char *argv[]) {
    FILE *file;
    if (argc == 1) {
        file = stdin;
    } else if (argc == 2) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            return 2;
        }
    } else {
        return 5;
    }

    Hashtable *ht = hash_create();
    if (ht == NULL) {
        fclose(file);
        return 4;
    }

    char line[SIZE];
    int index = 0;
    while (fgets(line, SIZE, file) != NULL) {
        size_t len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        int *count = hash_get(ht, line);
        if (count == NULL) {
            hash_put(ht, line, index);
            index++;
        }
    }

    int unique_count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = ht->table[i]->head;
        while (current != NULL) {
            unique_count++;
            current = current->next;
        }
    }

    printf("%d\n", unique_count);

    hash_destroy(&ht);
    fclose(file);

    return 0;
}
