#include <stdio.h>
#include <string.h>

int main(void)
{
    int i;
    char str[100];

    // input only digits
    printf("input number: ");
    scanf("%[0123456789]", str);

    // reverse string
    printf("output number: ");
    for (i = 1; i <= strlen(str); i++)
        putc(str[strlen(str) - i], stdout);
    puts("");

    return 0;
} 
