/*
To compile: mpicc -o mainParallel mainParallel.c -L. -lprocessing
To run: mpirun -np 4 ./mainParallel

To calculate speed gain: Sp = Tseq/Tpar
To calculate efficiency: Ep = Sp/P
Where: P is the number of processors
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "processing.h"
#include <sys/time.h>

const int LEN = 100;
const int GRUPO = 4;

void process_blocks(int grupo, int* vector, int len, int start, int end) {
    process_block1(grupo, vector, len, start, end);
    process_block2(grupo, vector, len, start, end);
    process_block3(grupo, vector, len, start, end);
    process_block4(grupo, vector, len, start, end);
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int firma = 0;
    if (rank == 0) firma = init_lab2(GRUPO);

    // Broadcast the signature to all processes
    MPI_Bcast(&firma, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Allocate the vector and distribute work
    int* vector = NULL;
    if (rank == 0) {
        vector = (int*)malloc(sizeof(int) * LEN);
        for (int i = 0; i < LEN; i++) vector[i] = i + 1;
    }

    // Broadcast the vector to all processes
    if (rank != 0) vector = (int*)malloc(sizeof(int) * LEN);
    MPI_Bcast(vector, LEN, MPI_INT, 0, MPI_COMM_WORLD);

    // Calculate the work per process
    int chunk_size = LEN / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? LEN - 1 : start + chunk_size - 1;

    // Measure the parallel execution time
    struct timeval start_time, end_time;
    MPI_Barrier(MPI_COMM_WORLD); // Synchronize before timing
    gettimeofday(&start_time, NULL);

    // Each process handles its chunk
    process_blocks(GRUPO, vector, LEN, start, end);

    MPI_Barrier(MPI_COMM_WORLD); // Synchronize after processing
    gettimeofday(&end_time, NULL);

    double local_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    // Gather the times at process 0
    double max_time;
    MPI_Reduce(&local_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Processing time (parallel): %f seconds for %d components\n", max_time, LEN);
        printf("Firma: 0x%08X\n", firma);
    }

    free(vector);
    MPI_Finalize();
    return 0;
}
