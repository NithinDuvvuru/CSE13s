#ifndef _HASH

#define _HASH

#include "ll.h"
#define TABLE_SIZE 1000

typedef struct Hashtable Hashtable;

struct Hashtable {
    LL *table[TABLE_SIZE];
};

Hashtable *hash_create(void);

bool hash_put(Hashtable *, char *key, int val);

int *hash_get(Hashtable *, char *key);

void hash_destroy(Hashtable **);

int hash_function(char *key);

#endif
