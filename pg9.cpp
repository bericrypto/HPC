#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int numtasks, rank, rc, next, prev, inmsg;
    MPI_Status Stat;
    double st, et;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (numtasks != 2) {
        if (rank == 0) {
            printf("This program is designed to run with exactly 2 processes.\n");
        }
        MPI_Finalize();
        return 0;
    }

    if (rank == 0) {
        prev = numtasks - 1;
        next = rank + 1;
    } else {
        prev = rank - 1;
        next = 0;
    }

    st = MPI_Wtime();

    rc = MPI_Send(&rank, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    rc = MPI_Recv(&inmsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &Stat);

    MPI_Barrier(MPI_COMM_WORLD);

    et = MPI_Wtime();
    if (rank == 0) 
        printf("Time taken by Blocking send/receive: %lf seconds\n", et - st);

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Request req;
    MPI_Status status;

    st = MPI_Wtime();

    MPI_Irecv(&inmsg, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &req);
    MPI_Isend(&rank, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &req);
    
    MPI_Wait(&req, &status);

    MPI_Barrier(MPI_COMM_WORLD);

    et = MPI_Wtime();
    if (rank == 0) 
        printf("Time taken by NonBlocking send/receive: %lf seconds\n", et - st);

    MPI_Finalize();
}
