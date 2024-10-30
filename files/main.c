#include <stdio.h>
#include <stdlib.h>
#include "processing.h"
#include <time.h>

const int LEN = 8;
const int GRUPO = 4;

int main() {
    
    int firma = init_lab2(GRUPO);
    
    int *vector = (int *) malloc(sizeof(int) * LEN);

    for (int i = 0; i < LEN; i++) { vector[i] = i + 1; }

    //We calculate the processing time
    clock_t start = clock();

    process_block1(GRUPO, vector, LEN, 0, LEN-1 );
    process_block2(GRUPO, vector, LEN, 0, LEN-1 );
    process_block3(GRUPO, vector, LEN, 0, LEN-1 );
    process_block4(GRUPO, vector, LEN, 0, LEN-1 );

    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Processing time: %f\n", time_spent);
    printf ("Firma: 0x%08X\n", firma);
    free(vector);

    return 0;
}

