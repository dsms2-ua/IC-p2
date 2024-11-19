#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

double local_integral(long long start, long long end, double step) {
    double sum = 0.0;

    for (long long i = start; i < end; i++) {
        double x = (i + 0.5) * step; // Punto medio del bloque
        sum += 1.0 / (1.0 + x * x);
    }

    return sum * step; // Multiplica por el ancho del bloque
}

int main(int argc, char *argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv); // Inicializa MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtiene el ID del proceso
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtiene el número de procesos

    if (argc != 2) {
        if (rank == 0) printf("Uso: %s <número de bloques>\n", argv[0]);
        MPI_Finalize();
        return 1;
    }

    long long n = atoll(argv[1]); // Convierte el argumento a long long int
    if (n <= 0) {
        if (rank == 0) printf("El número de bloques debe ser un entero positivo.\n");
        MPI_Finalize();
        return 1;
    }

    double step = 1.0 / n; // Ancho de cada bloque

    // Dividir los bloques entre los procesos
    long long local_start = rank * (n / size); // Índice inicial del proceso actual
    long long local_end = (rank + 1) * (n / size); // Índice final del proceso actual

    // Si n no es divisible entre el número de procesos, el último proceso asume el resto
    if (rank == size - 1) {
        local_end = n;
    }

    //Empezamos a contar el tiempo
    double start = MPI_Wtime();

    // Cada proceso calcula su parte de la integral
    double local_sum = local_integral(local_start, local_end, step);

    // Reducir las sumas locales para obtener la suma global
    double global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    //Empezamos a contar el tiempo
    double end = MPI_Wtime();

    if (rank == 0) {
        double pi = 4.0 * global_sum; // Multiplica por 4 para obtener π
        printf("Aproximación de π con %lld bloques: %.15f\n", n, pi);
        printf("Execution time in seconds: %f\n", end - start);
    }

    MPI_Finalize(); // Finaliza MPI
    return 0;
}
