//#define  _GNU_SOURCE
#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>

// int init(int k, char *fileName)
// {
    
//     return 0;
// }

void test(int** ptr){
    int numbers[] = {5,5,5, 5};
    *ptr = numbers;
    return;

}


int main(int argc, char *argv[])
{
    // int k = atoi(argv[1]); // number of clusters (centroids)
    // int iter = atoi(argv[2]);// maximum iteration
    int numbers[] = {1, 2, 3, 4, 5};
    int *ptr = numbers;  // Assign the address of the array to the pointer

    // Access array elements through the pointer
    printf("befor First element: %d\n", ptr[0]);     // Output: 1
    test(&ptr);
    printf("after First element: %d\n", ptr[0]);     // Output: 1

    return 0;
}