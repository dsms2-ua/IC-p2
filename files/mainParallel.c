/*
To compile: mpicc -o mainParallel mainParallel.c -L. -lprocessing
To run: mpirun -np 4 ./mainParallel

To calculate speed gain: Sp = Tseq/Tpar
To calculate efficiency: Ep = Sp/P
Where: P is the number of processors
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "processing.h"

const int LEN = 100;
const int GRUPO = 4;

int main(int argc, char *argv[]) {
    int rank, size;
    int firma;
    int *vector = (int *) malloc(sizeof(int) * LEN);

    // Inicializar MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Proceso principal inicializa el vector
    if (rank == 0) {
        for (int i = 0; i < LEN; i++) {
            vector[i] = i + 1;
        }
        firma = init_lab2(GRUPO);  // Inicializar una vez en el proceso principal
    }

    // Compartir el vector con todos los procesos
    MPI_Bcast(vector, LEN, MPI_INT, 0, MPI_COMM_WORLD);

    // Medir el tiempo paralelo
    double start_time = MPI_Wtime();

    // Cada proceso ejecuta su función en paralelo
    if (rank == 0) process_block1(GRUPO, vector, LEN, 0, LEN - 1);
    if (rank == 1) process_block2(GRUPO, vector, LEN, 0, LEN - 1);
    if (rank == 2) process_block3(GRUPO, vector, LEN, 0, LEN - 1);
    if (rank == 3) process_block4(GRUPO, vector, LEN, 0, LEN - 1);

    // Finalizar el tiempo paralelo
    double end_time = MPI_Wtime();
    double parallel_time = end_time - start_time;

    // El proceso 0 muestra los resultados
    if (rank == 0) {
        printf("Parallel processing time: %f seconds\n", parallel_time);
        printf("Firma: 0x%08X\n", firma);
    }

    free(vector);

    // Finalizar MPI
    MPI_Finalize();
    return 0;
}
