/*
To compile: mpicc -o 2-1-2 2-1-2.c
To run: mpirun -np 2 ./2-1-2
*/

#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int rank, size, N, sum = 0;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) { // Node N1 (rank 0)
        // Prompt the user for the vector size
        printf("Enter the size of the vector: ");
        fflush(stdout);
        scanf("%d", &N);

        // Send the vector size to N2 (rank 1)
        MPI_Send(&N, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

        // Calculate the sum of the first N natural numbers
        for (int i = 1; i <= N; i++) {
            sum += i;
        }

        // Send the sum back to N2 (rank 1)
        MPI_Send(&sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Sum of the first %d numbers sent back to node N2.\n", N);
    } 
    else if (rank == 1) { // Node N2 (rank 1)
        // Receive the vector size from N1 (rank 0)
        MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Receive the sum from N1 (rank 0)
        MPI_Recv(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("The sum of the first %d numbers is: %d\n", N, sum);
    }

    // Finalize the MPI environment for all ranks
    MPI_Finalize();

    return 0;
}