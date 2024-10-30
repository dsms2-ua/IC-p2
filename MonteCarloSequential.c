//Sequential version of the Monte-Carlo method
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//We build the Monte-Carlo function
double monteCarlo(int numPoints){
    int circle = 0; //In this variable we're storing the number of points that are inside the circle

    for(int i = 0; i < numPoints; i++){
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if(x*x + y*y <= 1){
            circle++; //If the point is inside the circle, we increment the circle variable
        }
    }

    return 4.0 * circle/numPoints; //We return the value of PI
}

int main(int argc, char *argv[]){
    //We initialise the random seed
    srand(time(0));

    int numPoints;
    printf("Enter the number of points: ");
    scanf("%d", &numPoints);

    //We calculate the time
    clock_t start = clock();
    double pi = monteCarlo(numPoints);
    clock_t end = clock();

    printf("The value of PI is: %f\n", pi);
    printf("Time: %f (ms)\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}