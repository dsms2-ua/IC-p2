#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int main(int argc, char *argv[]) {
    int rank, size, N = 1000;
    double *vector = NULL;
    double local_max = -DBL_MAX, local_min = DBL_MAX, local_sum = 0.0;
    double global_max, global_min, global_sum;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int elements_per_proc = N / size;

    // Cada proceso asigna memoria para su porción
    double *sub_vector = (double *)malloc(elements_per_proc * sizeof(double));

    if (rank == 0) {
        // Inicializa el vector solo en el proceso 0
        vector = (double *)malloc(N * sizeof(double));
        for (int i = 0; i < N; i++) {
            vector[i] = (double)rand() / RAND_MAX * 100.0; // Valores aleatorios de 0 a 100
        }
    }

    // Divide el vector entre los procesos
    MPI_Scatter(vector, elements_per_proc, MPI_DOUBLE, sub_vector, elements_per_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Cada proceso calcula su máximo, mínimo y suma locales
    for (int i = 0; i < elements_per_proc; i++) {
        if (sub_vector[i] > local_max) local_max = sub_vector[i];
        if (sub_vector[i] < local_min) local_min = sub_vector[i];
        local_sum += sub_vector[i];
    }

    // Reducción para encontrar el máximo, mínimo y suma globales
    MPI_Reduce(&local_max, &global_max, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_min, &global_min, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Máximo global: %f\n", global_max);
        printf("Mínimo global: %f\n", global_min);
        printf("Promedio global: %f\n", global_sum / N);
    }

    // Liberar memoria
    free(sub_vector);
    if (rank == 0) free(vector);

    MPI_Finalize();
    return 0;
}
