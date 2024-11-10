#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size;
    int data[4], recv_data;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        data[0] = 10;
        data[1] = 20;
        data[2] = 30;
        data[3] = 40; // El root inicializa el array
    }

    MPI_Scatter(data, 1, MPI_INT, &recv_data, 1, MPI_INT, 0, MPI_COMM_WORLD); // Distribuye cada valor a los procesos
    
    printf("Process %d received recv_data = %d\n", rank, recv_data);
    MPI_Finalize();
    return 0;
}
