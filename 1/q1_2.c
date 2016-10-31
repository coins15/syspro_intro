#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[100], str2[100];
    int i, j;

    // store str1, str2
    printf("input str1: ");
    scanf("%s", str1);
    printf("input str2: ");
    scanf("%s", str2);

    printf("output string: ");

    // check whether str1[i] is contained in str2
    for (i = 0; i < strlen(str1); i++)
        if (strchr(str2, str1[i]) != NULL)
            putc(str1[i], stdout);

    puts("");

    return 0;
}
