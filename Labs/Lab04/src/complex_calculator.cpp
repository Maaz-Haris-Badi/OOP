#include <iostream>

double add(double *a, double *b)
{
    double result[2];

    result[0] = *(a + 0) + *(b + 0);
    result[1] = *(a + 1) + *(b + 1);

    return *result;
}

int main()
{
    return 0;
}