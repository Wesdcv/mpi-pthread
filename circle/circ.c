#include <stdio.h>
#include <mpi.h>


int main(int argc, char *argv[])
{
	MPI_Init(&argc, &argv);

	int world_comm_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_comm_size);

	int world_comm_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_comm_rank);

	int msg = 1;

	int circle_count = 0;

    if(world_comm_rank == 0){
        MPI_Send(&msg, 1, MPI_INT, (world_comm_rank + 1), 0, MPI_COMM_WORLD);
        printf("Process %d sent message %d to process %d\n", world_comm_rank, msg, (world_comm_rank + 1) % world_comm_size);
        MPI_Recv(&msg, 1, MPI_INT, (world_comm_size - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received message %d from process %d\n", world_comm_rank, msg, world_comm_size - 1);
    } else {
        MPI_Recv(&msg, 1, MPI_INT, (world_comm_rank - 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received message %d from process %d\n", world_comm_rank, msg, world_comm_rank - 1);
        msg *= 2;
        MPI_Send(&msg, 1, MPI_INT, (world_comm_rank + 1) % world_comm_size, 0, MPI_COMM_WORLD);
        printf("Process %d sent message %d to process %d\n", world_comm_rank, msg, (world_comm_rank + 1) % world_comm_size);

    }


	MPI_Finalize();

	return 0;
}
