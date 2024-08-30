#include "hash.h"

#include <stdlib.h>
#include <string.h>

int hash_function(char *key) {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        sum += key[i];
    }
    return sum % TABLE_SIZE;
}

Hashtable *hash_create(void) {
    Hashtable *ht = (Hashtable *) malloc(sizeof(Hashtable));
    if (ht == NULL) {
        return NULL;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = list_create();
        if (ht->table[i] == NULL) {
            for (int j = 0; j < i; j++) {
                list_destroy(&(ht->table[j]));
            }
            free(ht);
            return NULL;
        }
    }
    return ht;
}

bool hash_put(Hashtable *ht, char *key, int val) {
    if (ht == NULL || key == NULL) {
        return false;
    }
    int index = hash_function(key);
    item i;
    strcpy(i.key, key);
    i.id = val;
    return list_add(ht->table[index], &i);
}

int *hash_get(Hashtable *ht, char *key) {
    if (ht == NULL || key == NULL) {
        return NULL;
    }
    int index = hash_function(key);
    Node *current = ht->table[index]->head;
    while (current != NULL) {
        if (strcmp(current->data.key, key) == 0) {
            return &(current->data.id);
        }
        current = current->next;
    }
    return NULL;
}

void hash_destroy(Hashtable **ht) {
    if (ht == NULL || *ht == NULL) {
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        list_destroy(&((*ht)->table[i]));
    }
    free(*ht);
    *ht = NULL;
}
