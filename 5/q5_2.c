#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

struct node *insert_data(int x, struct node *p);
void print_tree(struct node *p);
int sum_tree(struct node *p);

int main(int argc, char *argv[])
{
    FILE *fp;
    int i, x;
    struct node *root;

    if (argc != 2) {
        printf("missing file argument\n");
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("can't open %s\n", argv[1]);
        return 1;
    }

    root = NULL;

    for (i = 0; i < 20; i++) {
        fscanf(fp, "%d", &x);
        root = insert_data(x, root);
    }

    print_tree(root);

    printf("Sum: %d\n", sum_tree(root));

    fclose(fp);

    return 0;
}

struct node *insert_data(int x, struct node *p)
{
    if (p == NULL) {
        p = (struct node *) malloc(sizeof(struct node));
        if (p == NULL) {
            printf("Out of memory\n");
            exit(1);
        }
        p->data = x;
        p->left = NULL;
        p->right = NULL;

        return p;
    }

    if (x == p->data)
        return p;

    if (x < p->data)
        p->left = insert_data(x, p->left);
    else
        p->right = insert_data(x, p->right);

    return p;
}

void print_tree(struct node *p)
{
    if (p == NULL)
        return;

    print_tree(p->left);
    printf("%d\n", p->data);
    print_tree(p->right);
}

int sum_tree(struct node *p)
{
    if (p == NULL)
        return 0;
    return p->data + sum_tree(p->left) + sum_tree(p->right);
}
