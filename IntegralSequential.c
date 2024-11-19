#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double calculate_pi(int n) {
    double step = 1.0 / n; // Ancho de cada bloque
    double sum = 0.0;

    for (int i = 0; i < n; i++) {
        double x = (i + 0.5) * step; // Punto medio del bloque
        sum += 1.0 / (1.0 + x * x);
    }

    return 4.0 * sum * step; // Multiplica por 4 y el ancho del bloque
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <número de bloques>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]); // Número de bloques ingresado por el usuario
    if (n <= 0) {
        printf("El número de bloques debe ser un entero positivo.\n");
        return 1;
    }

    clock_t start = clock();
    double pi = calculate_pi(n);
    clock_t end = clock();
    printf("Aproximation of π with %d divissions: %.15f\n", n, pi);
    printf("Time: %f (s)\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
