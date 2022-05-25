#include "mpi.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
    int myid, nprocs;
    double start_time, finish_time;

    int X = 2400, T = 1;

    int M = 60000, K = 50; // M ������ ����� ���������
    double h, tau; // ����
    double a; //��������� �� ���������

    int k, m;
    int i;


    MPI_Status status;

    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank (MPI_COMM_WORLD, &myid);



    int n = M / nprocs; // ���������� �����, ������� ������������ 1 �������

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

    //  �����, � ������� ������ ������� ������� ���� ����� �� ��������� ����
    double* u_procs;
    u_procs = (double*) malloc (n * sizeof (double) );

    //    ����� �������
    if (myid == 0)
    {
        start_time = MPI_Wtime();
    }

    // �� ������ ��������� ���� ���������� ������ �� ������ ���������� � ����� u_procs � ����� �� ���� ��������� �������� �� � ����� ��������� ���� u
    for (k = 1; k < K; k++)
    {

        // ��������� �� ��� �������� ���������� ����� �� �, ��������� ������������ � u_procs �� ������ ��������
        for (m = 0; m < n; m++)
        {
            if ( (m + myid * n) == M - 1)
            {
                u_procs[m] = u[ (k - 1) * M + myid * n + m] - tau / h * (u[ (k - 1) * M + myid * n + m] - u[ (k - 1) * M + myid * n + (m - 1)]) + tau * 5 * x[m + myid * n] * t[k - 1];
            }
            else
                if ( (m + myid * n) == 0)
                {
                    u_procs[m] = 0;
                }
                else
                {
                    u_procs[m] = 0.5 * (1 - tau / h) * u[ (k - 1) * M + myid * n + (m + 1)] + 0.5 * (1 + tau / h) * u[ (k - 1) * M + myid * n + (m - 1)] + tau * 5 * x[m + myid * n] * t[k - 1];
                }
        }

        //  � ������ �������� ���������� ������ ��������� ����
        MPI_Allgather (u_procs, n, MPI_DOUBLE, (u + k * M), n, MPI_DOUBLE, MPI_COMM_WORLD);
    }

    //    � ������� �������� ��������� ���������
    if (myid == 0)
    {
        finish_time = MPI_Wtime();
        /*
        for (k = 0; k < K; k++){
            for (m = 0; m < M; m++)
                printf("%f ", u[k*M + m]);
            printf("\n");
        }
        */
        printf ("u = %f \n", u[ (K - 1) *M + M - 1]);
        printf ("Time: %f \n", (float) (finish_time - start_time) );
    }


    free (u);
    free (u_procs);

    fflush (stdout);
    MPI_Finalize();

    return 0;
}
