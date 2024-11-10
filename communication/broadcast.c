#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, data = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        data = 100; // El proceso 0 inicializa el valor
    }
    
    MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD); // El proceso 0 envía 'data' a todos los demás
    
    printf("Process %d recived data = %d\n", rank, data);
    MPI_Finalize();
    return 0;
}
