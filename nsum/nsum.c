#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{

    MPI_Init (&argc, &argv);

    double msg = 0;
    int i = 0;
    int N = atoi (argv[1]);

    int world_comm_size;
    MPI_Comm_size (MPI_COMM_WORLD, &world_comm_size);
    double mass[world_comm_size];


    int world_comm_rank;
    MPI_Comm_rank (MPI_COMM_WORLD, &world_comm_rank);

    mass[world_comm_rank] = 0.0;



    for ( i = world_comm_rank + 1; i < N - (world_comm_size - world_comm_rank - 1); i += world_comm_size )
    {
        mass[world_comm_rank] += (1.0 / i);
    }

    if (world_comm_rank == 0)
    {
        msg = mass[world_comm_rank];
        MPI_Send (&msg, 1, MPI_DOUBLE, (world_comm_rank + 1), 0, MPI_COMM_WORLD);
        MPI_Recv (&msg, 1, MPI_DOUBLE, (world_comm_size - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        printf ("Sum for N = %d is %f \n", N, msg);
    }
    else
    {
        MPI_Recv (&msg, 1, MPI_DOUBLE, (world_comm_rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        msg = msg + mass[world_comm_rank];
        MPI_Send (&msg, 1, MPI_DOUBLE, (world_comm_rank + 1) % world_comm_size, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
