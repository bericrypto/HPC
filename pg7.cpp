#include <iostream>
#include <cstdlib>
#include <mpi.h>

int main(int argc, char* argv[]) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    float recvbuf, sendbuf[100];
    if (rank == 0) {
        std::cout << "Before Scatter: sendbuf of rank 0: ";
        for (int i = 0; i < size; i++) {
            srand(i);
            sendbuf[i] = static_cast<float>(rand() % 1000) / 10;
            std::cout << sendbuf[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "After Scatter:" << std::endl;
    }
    
    MPI_Scatter(sendbuf, 1, MPI_FLOAT, &recvbuf, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
    std::cout << "rank= " << rank << " Recvbuf: " << recvbuf << std::endl;
    
    MPI_Finalize();
    return 0;
}
