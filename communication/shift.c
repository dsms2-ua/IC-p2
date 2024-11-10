#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, size, send_data, recv_data;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    send_data = rank + 1;
    int dest = (rank + 1) % size;
    int source = (rank - 1 + size) % size;

    MPI_Sendrecv(&send_data, 1, MPI_INT, dest, 0, &recv_data, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status);

    printf("Proceso %d envió %d y recibió %d\n", rank, send_data, recv_data);
    MPI_Finalize();
    return 0;
}
