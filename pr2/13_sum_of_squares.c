#include <stdio.h>
#include <math.h>

int main()
{
    int n;
    double sum = 0, input;
    (void)scanf("%d", &n);
    int  i;
    for (i = 0; i < n; i++) {
        (void)scanf("%lf", &input);
        sum += pow(input, 2);
    }
    printf("%lf", sum);
    return 0;
}

