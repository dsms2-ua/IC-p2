#include <math.h> 
#include "mpi.h"   // Biblioteca de MPI
#include <cstdlib> // Incluido para el uso de atoi
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) 
{ 
    int n, // Número de iteraciones
        rank, // Identificador de proceso
        size; // Número de procesos
    double PI25DT = 3.141592653589793238462643;
    double mypi, // Valor local de PI
        pi,   // Valor global de PI
        h,   // Aproximación del área para el cálculo de PI
        sum;  // Acumulador para la suma del área de PI

    MPI_Init(&argc, &argv); // Inicializamos los procesos
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el número total de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador

    // Solo el proceso 0 conoce el número de iteraciones que vamos a ejecutar para la aproximación de PI
    if (rank == 0) {
        cout << "Introduce la precisión del cálculo (n > 0): ";
        cin >> n;
    }

    // El proceso 0 reparte el número de iteraciones a los demás procesos
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (n <= 0) {
        MPI_Finalize();
        exit(0);
    } else {
        // Cálculo de PI
        h = 1.0 / (double) n;
        sum = 0.0;

        // Cada proceso calcula una parte de la integral
        for (int i = rank + 1; i <= n; i += size) {
            double x = h * ((double)i - 0.5);
            sum += (4.0 / (1.0 + x * x));
        }
        mypi = h * sum;

        // Reducimos los valores locales de PI a un valor global en el proceso 0
        MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        // Solo el proceso 0 imprime el resultado
        if (rank == 0)
            cout << "El valor aproximado de PI es: " << pi
                 << ", con un error de " << fabs(pi - PI25DT) << endl;
    }

    MPI_Finalize(); 
    return 0; 
}