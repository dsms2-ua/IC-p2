#include <stdio.h>
#include <stdlib.h>
#include "processing.h"
#include <sys/time.h>

const int LEN = 1600;
const int GRUPO = 4;

int main() {
    
    int firma = init_lab2(GRUPO);
    
    int *vector = (int *) malloc(sizeof(int) * LEN);

    for (int i = 0; i < LEN; i++) { vector[i] = i + 1; }

    //We calculate the processing time
    struct timeval start, end;
    gettimeofday(&start, NULL);

    process_block1(GRUPO, vector, LEN, 0, LEN-1 );
    process_block2(GRUPO, vector, LEN, 0, LEN-1 );
    process_block3(GRUPO, vector, LEN, 0, LEN-1 );
    process_block4(GRUPO, vector, LEN, 0, LEN-1 );

    gettimeofday(&end, NULL);

    double time_spent = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    
    printf("Processing time: %f seconds for %d components\n", time_spent, LEN);
    printf ("Firma: 0x%08X\n", firma);
    free(vector);

    return 0;
}

