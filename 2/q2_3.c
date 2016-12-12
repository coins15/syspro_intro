#include <stdio.h>
#include <stdlib.h>

#define NAMELEN 100

typedef struct {
    char name[NAMELEN];
    int point;
} person;

int comp(const void *p1, const void *p2)
{
    return ((person *)p1)->point - ((person *)p2)->point;
}

int main(int argc, char *argv[])
{
    int count = 0;
    person *people;
    FILE *fp;

    if (argc != 2) {
        puts("missing file argument");
        return 1;
    }

    if ((fp = freopen(argv[1], "r", stdin)) == NULL) {
        printf("can't open %s\n", argv[1]);
        return 1;
    }

    do
        people = realloc(people, sizeof(person) * (++count));
    while (scanf("%s\t%d\n", people[count - 1].name, &people[count - 1].point) != EOF);

    qsort(people, count, sizeof(person), comp);

    while (--count)
        printf("%s\t%d\n", people[count].name, people[count].point);

    free(people);
    fclose(fp);

    return 0;
}


