#include <iostream>
#include <cstdlib>
#include <mpi.h>

int main(int argc, char** argv){
    int rank, numproc;
    int sum = 0;
    int total_sum = 0;
  
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numproc);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    double start_time = MPI_Wtime();

    srand(rank);
    sum = rand() % 100;
    std::cout << "Robot " << rank << " picked " << sum << " mangoes." << std::endl;

    MPI_Reduce(&sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	double end_time = MPI_Wtime();
	
    if (rank == 0){
        std::cout << "Total Mangoes picked by " << numproc << " Robots = " << total_sum << std::endl;
        std::cout << "Execution Time: " << (end_time - start_time) << " seconds" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
