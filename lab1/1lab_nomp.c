#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


double f (x, t)
{
    return 5 * x * t;
}

double fi (x)
{
    return x;
}

double ksi (t)
{
    return t;
}


int main (int argc, char* argv[])
{
    clock_t start_time, finish_time;

    int X = 2400, T = 1;

    int M = 60000, K = 50; //  M ������ ����� ���������
    double h, tau; // ����

    int k, m;

//    ������ �����
    h = (double) X / M;
    tau = (double) T / K;

    double* u; // ��������� ������ �� ���������� ����� � ������ ����
    double* x;
    double* t;

    u = (double*) malloc ( (M * K) * sizeof (double) );
    x = (double*) malloc (M * sizeof (double) );
    t = (double*) malloc (K * sizeof (double) );

//    ������� �����
    for (m = 0; m < M; m++)
    {
        x[m] = m * h;
    }
    for (k = 0; k < K; k++)
    {
        t[k] = k * tau;
    }

//    ������� ��������� �������
    for (m = 0; m < M; m++)
    {
        u[m] = x[m];
    }
    for (k = 0; k < K; k++)
    {
        u[k * M] = t[k];
    }

//    ����� �������
    start_time = clock();


    for (k = 1; k < K; k++)
    {
        for (m = 0; m < M; m++)
        {
            if (m == M - 1)
            {
                u[k * M + m] = u[ (k - 1) * M + m] - tau / h * (u[ (k - 1) * M + m] - u[ (k - 1) * M + (m - 1)]) + tau * 5 * x[m] * t[k - 1];
            }
            else
                if (m == 0)
                {
                    u[k * M + m] = 0;
                }
                else
                {
                    u[k * M + m] = 0.5 * (1 - tau / h) * u[ (k - 1) * M + (m + 1)] + 0.5 * (1 + tau / h) * u[ (k - 1) * M + (m - 1)] + tau * 5 * x[m] * t[k - 1];
                }
        }
    }

//  ��������� ���������
    finish_time = clock();
    printf ("%f \n", u[M * (K - 1) + M - 1]);

    double time;
    time = (double) (finish_time - start_time) / CLOCKS_PER_SEC;
    printf ("%lf \n", time);


    free (u);

    return 0;
}