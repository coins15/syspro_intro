#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie {
    struct trie *array[256];
} trie_t;

void init_trie(trie_t *ptr) {
    int i;

    for (i = 0; i < 256; ++i) {
        ptr->array[i] = NULL;
    }

    return;
}

trie_t *new_trie() {
    trie_t *ptr;

    ptr = malloc(sizeof(trie_t));
    if (ptr == NULL) exit(1);
    init_trie(ptr);

    return ptr;
}

trie_t *add_to_trie(char *str, trie_t *ptr) {
    if (strlen(str) == 0) {
        ptr->array['.'] = new_trie();
        return ptr->array['.'];
    } 

    if (ptr->array[*str] == NULL) {
        ptr->array[*str] = new_trie();
    } 

    return add_to_trie(str + 1, ptr->array[*str]);
}

trie_t *find_in_trie(char *str, trie_t *ptr) {
    if (ptr == NULL)
        return NULL;

    if (strlen(str) == 0)
        return ptr->array['.'];

    return find_in_trie(str + 1, ptr->array[*str]);
}

int main(int argc, char *argv[]) {
    FILE *f;
    char str[512];
    trie_t root;

    if ((f = fopen(argv[1], "r")) == NULL) exit(1);

    init_trie(&root);
    while (fgets(str, 512, f)) {
        if (str[strlen(str) - 1] == '\n') str[strlen(str) - 1] = '\0';
        add_to_trie(str, &root);
    }

    fclose(f);

    if (find_in_trie(argv[2], &root) != NULL) {
        printf("%s: FOUND in %s\n", argv[0], argv[1]);
    } else {
        printf("%s: not found in %s\n", argv[0], argv[1]);
    }

    return 0;
}
