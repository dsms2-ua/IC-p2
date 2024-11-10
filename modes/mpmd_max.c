#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(int argc, char *argv[]) {
    int rank, size, N = 1000;
    double local_max = -DBL_MAX, global_max;
    int elements_per_proc;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    elements_per_proc = N / size;
    double *sub_vector = (double *)malloc(elements_per_proc * sizeof(double));

    // Inicializar sub_vector con valores aleatorios (este paso varía según la implementación real)
    for (int i = 0; i < elements_per_proc; i++) {
        sub_vector[i] = (double)rand() / RAND_MAX * 100.0;
        if (sub_vector[i] > local_max) local_max = sub_vector[i];
    }

    MPI_Reduce(&local_max, &global_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) printf("Máximo global: %f\n", global_max);

    free(sub_vector);
    MPI_Finalize();
    return 0;
}
