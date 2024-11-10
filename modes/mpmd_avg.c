#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, N = 1000;
    double local_sum = 0.0, global_sum;
    int elements_per_proc;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    elements_per_proc = N / size;
    double *sub_vector = (double *)malloc(elements_per_proc * sizeof(double));

    for (int i = 0; i < elements_per_proc; i++) {
        sub_vector[i] = (double)rand() / RAND_MAX * 100.0;
        local_sum += sub_vector[i];
    }

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) printf("Promedio global: %f\n", global_sum / N);

    free(sub_vector);
    MPI_Finalize();
    return 0;
}
