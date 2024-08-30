#include "ll.h"

#include <stdio.h>
#include <string.h>

#define MAGICN 457

int main() {
    LL *l = list_create();

    for (int i = 0; i < 1000; i++) {
        item j;
        strcpy(j.key, "key");
        j.id = i;
        list_add(l, &j);
    }

    item i;
    strcpy(i.key, "key");
    i.id = MAGICN;
    list_remove(l, cmp, &i);

    item j;
    for (int i = 0; i < 1000; i++) {
        if (i != MAGICN) {
            strcpy(j.key, "key");
            j.id = i;
            item *ret = list_find(l, cmp, &j);
            if (ret == NULL) {
                printf("something went wrong. I inserted %d into the list but then could not find "
                       "it.\n",
                    i);
                return 1;
            }
        }
    }

    list_destroy(&l);
    return 0;
}
