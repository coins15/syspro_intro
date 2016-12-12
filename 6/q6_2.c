#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trie {
    struct trie *child;
    struct trie *next;
    char c;
} trie_t;

trie_t *new_trie(char c) {
    trie_t *ptr = malloc(sizeof(trie_t));
    if (ptr == NULL)
        exit(1);

    ptr->child = NULL;
    ptr->next = NULL;
    ptr->c = c;

    return ptr;
}

trie_t *add_to_trie(char *str, trie_t *ptr) {
    if (ptr->c == *str) {
        if (*str == '\0')
            return ptr;
        if (ptr->child == NULL)
            ptr->child = new_trie(*(str + 1));
        return add_to_trie(str + 1, ptr->child);
    }

    if (ptr->next == NULL) {
        ptr->next = new_trie(*str);
        return add_to_trie(str, ptr->next);
    }

    return add_to_trie(str, ptr->next);
}

trie_t *find_in_trie(char *str, trie_t *ptr) {
    if (ptr == NULL)
        return NULL;

    if (ptr->c == *str) {
        if (*str == '\0')
            return ptr;
        return find_in_trie(str + 1, ptr->child);
    }

    return find_in_trie(str, ptr->next);
}

int main(int argc, char *argv[]) {
    FILE *f;
    char str[512];
    trie_t *root;

    if ((f = fopen(argv[1], "r")) == NULL)
        exit(1);

    root = new_trie('\0');

    while (fgets(str, 512, f)) {
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';
        add_to_trie(str, root);
    }

    fclose(f);

    if (find_in_trie(argv[2], root) != NULL)
        printf("%s: FOUND in %s\n", argv[0], argv[1]);
    else
        printf("%s: not found in %s\n", argv[0], argv[1]);

    return 0;
}
