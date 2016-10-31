#include <stdio.h>

#define N 100

int main(void)
{
    double a[N][N], b[N][N], c[N], d[N], tmp;
    int i, j, k, n;

    scanf("%d", &n);

    // store input matrix to a[][], initialize b[][],
    // and store answer vector to c[][]
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%lf", &a[i][j]);
            b[i][j] = (double)(i == j);
        }
        scanf("%lf", &c[i]);
    }

    // Gauss-Jordan
    for (k = 0; k < n; k++) {
        tmp = a[k][k];

        for (i = 0; i < n; i++) {
            a[k][i] /= tmp;
            b[k][i] /= tmp;
        }

        for (j = 0; j < n; j++) {
            if (j != k) {
                tmp = a[j][k];
                for (i = 0; i < n; i++) {
                    a[j][i] -= a[k][i] * tmp;
                    b[j][i] -= b[k][i] * tmp;
                }
            }
        }
    }

    // calculate the product of inverse matrix and answer vector
    for (i = 0; i < n; i++) {
        d[i] = 0;
        for (j = 0; j < n; j++)
            d[i] += b[i][j] * c[j];
    }

    // output the results
    for (i = 0; i < n; i++)
        printf("%f ", d[i]);
    printf("\n");

    return 0;
}
