#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct record {
    char word[20];
    int count;
    struct record *next;
};

struct record *head = NULL;

int read_word(FILE *fp, char *word)
{
    fscanf(fp, "%[^A-Za-z0-9'-]s", word);
    return fscanf(fp, "%[A-Za-z0-9'-]s", word) != EOF;
}

struct record *new_word(char *word)
{
    struct record *p = malloc(sizeof(struct record));

    strcpy(p->word, word);
    p->count = 1;
    p->next = NULL;

    return p;
}

void add_word(char *word)
{
    if (head == NULL) {
        head = new_word(word);
        return;
    }

    struct record *p = head;
    while (p) {
        if (strcmp(p->word, word) == 0) {
            p->count++;
            return;
        }

        if (p->next == NULL)
            break;
        p = p->next;
    }

    p->next = new_word(word);
}

void free_word(struct record *p)
{
    if (p->next != NULL)
        free_word(p->next);
    free(p);
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char word[20];
    struct record *p;

    if (argc != 2) {
        printf("missing file argument\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("can't open %s\n", argv[1]);
        return 1;
    }

    while (read_word(fp, word)) {
        add_word(word);
    }

    fclose(fp);

    for (p = head; p != NULL; p = p->next)
        printf("%s %d\n", p->word, p->count);

    free_word(head);

    return 0;
}
