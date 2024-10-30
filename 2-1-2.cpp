/*
To compile the file we use: mpic++ -o 2-1-2 2-1-2.cpp
To run the file we use: mpirun -np 2 ./2-1-2
*/

#include <mpi.h>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    int rank, size, N, sum = 0;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    cout << rank << endl;

    if(rank == 0) { // Node N1 (rank 0)
        const char message[] = "N2: Message from N1=> Enter vector size: ";

        //We send a message to the N2 node
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);

        // Receive the size of the vector (N) from N2 (rank 1)
        MPI_Recv(&N, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        // Calculate the sum of the first N natural numbers
        for (int i = 1; i <= N; i++) {
            sum += i;
        }

        // Send the sum back to N2 (rank 1)
        MPI_Send(&sum, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        cout << "Sum of the first " << N << " numbers sent back to node N2." << endl;
        //MPI_Finalize();
    } 
    else if (rank == 1) { // Node N2 (rank 1)
        //Rank 1 receives the first message from rank 0
        char message[100];
        MPI_Recv(message, 100, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        cout << message << endl;
        cout << "N2: Enter the size of the vector: ";

        N = 3;

        // Send the vector size to N1 (rank 0)
        MPI_Send(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);


        // Receive the sum from N1 (rank 0)
        MPI_Recv(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        cout << "The sum of the first " << N << " numbers is: " << sum << endl;
        MPI_Finalize();
    }
    else 

    // Finalize the MPI environment
    MPI_Finalize();
    return 0;
}
