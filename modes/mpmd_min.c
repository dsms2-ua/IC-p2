#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(int argc, char *argv[]) {
    int rank, size, N = 1000;
    double local_min = DBL_MAX, global_min;
    int elements_per_proc;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    elements_per_proc = N / size;
    double *sub_vector = (double *)malloc(elements_per_proc * sizeof(double));

    for (int i = 0; i < elements_per_proc; i++) {
        sub_vector[i] = (double)rand() / RAND_MAX * 100.0;
        if (sub_vector[i] < local_min) local_min = sub_vector[i];
    }

    MPI_Reduce(&local_min, &global_min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);

    if (rank == 0) printf("Mínimo global: %f\n", global_min);

    free(sub_vector);
    MPI_Finalize();
    return 0;
}
