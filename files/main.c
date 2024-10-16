#include <stdio.h>
#include <stdlib.h>
#include "processing.h"

const int LEN = 100;
const int GRUPO = 1;

int main() {
    
    int firma = init_lab2(GRUPO);
    
    int *vector = (int *) malloc(sizeof(int) * LEN);

    for (int i = 0; i < LEN; i++) { vector[i] = i + 1; }

    process_block1(GRUPO, vector, LEN, 0, LEN-1 );
    process_block2(GRUPO, vector, LEN, 0, LEN-1 );
    process_block3(GRUPO, vector, LEN, 0, LEN-1 );
    process_block4(GRUPO, vector, LEN, 0, LEN-1 );
       
    printf ("Firma: 0x%08X\n", firma);
    free(vector);

    return 0;
}

