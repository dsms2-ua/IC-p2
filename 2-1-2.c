/*
To compile: mpicc -o 2-1-2 2-1-2.c
To run: mpirun -np 2 ./2-1-2
*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    int rank, size, N, sum = 0;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) { // Node N1 (rank 0)
        bool valid = false;
        // Request the user for a number greater than 0
        while (!valid) {
            printf("N1: Enter a number greater than 0: ");
            fflush(stdout);
            scanf("%d", &N);
            if (N > 0) {
                valid = true;
            }
        }

        // Send the number to N2 (rank 1)
        MPI_Send(&N, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Receives the sum from N2(rank 1) and prints the result
        MPI_Recv(&sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("N1: Sum of the first %d numbers is %d.\n", N, sum);
    } 
    else if (rank == 1) { // Node N2 (rank 1)
        // Receive the vector size from N1 (rank 0)
        MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for(int i = 1; i <= N; i++) {
            sum += i;
        }

        // Sends the sum to N1 (rank 0)
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("N2: The sum of the first %d numbers sent to N1\n", N);
    }

    // Finalize the MPI environment for all ranks
    MPI_Finalize();

    return 0;
}