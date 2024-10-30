/*
To compile: mpicc -o MonteCarloParallel MonteCarloParallel.c
To run: mpirun -np x ./MonteCarloParallel
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
    int rank, size;
    int num_points, points_per_process, inside_circle = 0, total_inside_circle = 0;

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Solo el proceso 0 pide el número de puntos y lo distribuye
        printf("Enter the number of points: ");
        fflush(stdout); //Limpiamos el buffer para que salga el mensaje del printf
        scanf("%d", &num_points);
    }

    // Compartir el número total de puntos a todos los procesos
    MPI_Bcast(&num_points, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //Empezamos a contar el tiempo
    double start = MPI_Wtime();

    // Cada proceso calcula su cantidad de puntos
    points_per_process = num_points / size;

    // Inicializar semilla para números aleatorios diferente para cada proceso
    srand(time(0) + rank);

    // Cada proceso cuenta sus puntos dentro del círculo
    for (int i = 0; i < points_per_process; i++) {
        double x = (double)rand() / RAND_MAX * 2.0 - 1.0;
        double y = (double)rand() / RAND_MAX * 2.0 - 1.0;

        if (x * x + y * y <= 1) {
            inside_circle++;
        }
    }

    // Recopilar todos los resultados en el proceso 0
    MPI_Reduce(&inside_circle, &total_inside_circle, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    double end = MPI_Wtime();   

    // El proceso 0 calcula el valor final de Pi
    if (rank == 0) {
        double pi = 4.0 * total_inside_circle / num_points;
        printf("Estimated value of Pi (parallel): %f\n", pi);
        printf("Execution time in seconds: %f\n", end - start);
    }

    // Finalizar MPI
    MPI_Finalize();
    return 0;
}
