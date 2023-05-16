#include <stdio.h>
#include <stdlib.h>
//#include <math.h>

enum boolean {
    FALSE,    // 0
    TRUE,  // 1
};

int readInput(int* n,int* d, double*** points)
{
    char str[200] = {0};
    enum boolean isFirstLine = TRUE;
    //--------for daynamic allocation--------
    size_t sizeOfPoints_nxd = 100;
    size_t sizeOfpoints = 100;  
    double* points_nxd = (double*) calloc(sizeOfPoints_nxd, sizeof(double));
    *points = (double**) calloc(sizeOfpoints, sizeof(double*));
    //--------------------------------------- 
    if(points_nxd == NULL || (*points) == NULL)
        return 1;
    int indexOfPoints_nxd = 0;
    int i = 0;
    // get data from stdin and write it daynamicly to points_nxd
    str[i] = getchar();
        do{
        if(str[i] == ',' || str[i] == '\n'){
            if(isFirstLine == TRUE && str[i] == '\n'){
                *d = indexOfPoints_nxd + 1;
                isFirstLine = FALSE;
            }
            str[i] = '\0';
            points_nxd[indexOfPoints_nxd] = strtod(str, NULL); // str to double
            indexOfPoints_nxd++;
            i = 0;
        }
        else
            i++;
        if(indexOfPoints_nxd == sizeOfPoints_nxd){
            sizeOfPoints_nxd *= 2;
            points_nxd = (double*)realloc(points_nxd, sizeof(double) *  sizeOfPoints_nxd);
            if(points_nxd == NULL)
                return 1;
        }
    // end while condition: (str[i] != 'z') use to demonstrate end of file when debuging
    } while((str[i] = getchar()) && (str[i] != 'z'));

    // arrange the data in points as an 2 dim array, write daynamicly
    *n = indexOfPoints_nxd/(*d);
    *points[0] = points_nxd;
    int indexOfpoints = 1;
    for(i=0;i<(*n);i++){
        if(i==sizeOfpoints){
            sizeOfpoints *= 2;
            *points = (double**)realloc(*points, sizeof(double*) *  sizeOfpoints);
            if((*points) == NULL)
                return 1;
        }
        (*points)[i] = points_nxd +i*(*d);
    }
    return 0; // successful running
}

int initCentroids(int k, int d, double*** centroids, double** points){
    double* centroides_kxd = (double*) calloc(k*d, sizeof(double));
    *centroids = (double**) calloc(k, sizeof(double*));
    if(centroides_kxd == NULL || (*centroids) == NULL)
        return 1;
    for(int i=0;i<k*d;i++){
        centroides_kxd[i] = (*points)[i];
    }
    for(int i=0;i<k;i++){
        (*centroids)[i] = centroides_kxd +i*d;
    }
    return 0; // successful running
}

int initPointsCentroidsIndex(int n, int k, int** pointsCentroidsIndex){
    *pointsCentroidsIndex = (int*) calloc(n, sizeof(int));
    if((*pointsCentroidsIndex) == NULL)
        return 1;
    for(int i = 0;i < k; i++){
        (*pointsCentroidsIndex)[i] = i;
    }
    return 0; // successful running
}



int main(int argc, char *argv[])
{
    printf("%d", argc);
    // int k = 100; // for debuging mode
    if(argc == 1){ // no arguments have been passed to main
        printf("An Error Has Occurred");
        return 1;
    }
    int k = atoi(argv[1]); // number of clusters (centroids)
    int iter = 0;// maximum iteration
    if(argc == 2) // 1 argument have been passed to main
        iter = 200;
    else // at least 2 arguments have been passed to main
        iter = atoi(argv[2]);// maximum iteration
    int n = 0;
    int d = 0;
    double** points = NULL;
    double** centroids = NULL;
    double** prevCentroids = NULL;
    int* pointsCentroidsIndex = NULL;
    //---------------input check:----------------
    if(k <= 1){
        printf("Invalid number of clusters!");
        return 1;
    }
    if(iter <= 1 || 1000 <= iter){
        printf("Invalid maximum iteration!");
        return 1;
    }
    //---------------init routine:---------------
    int initStatus = 0;
    initStatus = readInput(&n, &d, &points);

    if(n <= k){
        printf("Invalid number of clusters!");
        return 1;
    }

    if(initStatus){
        printf("An Error Has Occurred");
        return 1;
    }
    initStatus = initCentroids(k, d, &centroids, points);

    if(initStatus){
        printf("An Error Has Occurred");
        return 1;
    }

    initStatus = initCentroids(k, d, &prevCentroids, points);

    if(initStatus){
        printf("An Error Has Occurred");
        return 1;
    }

    initStatus = initPointsCentroidsIndex(n, k, &pointsCentroidsIndex);
    
    if(initStatus){
        printf("An Error Has Occurred");
        return 1;
    }
    
    //-----------end init routine----------------

    //---------------print matrix[n][k]:--------------
    // printf("centroids matrix:");
    // for(int i=0;i<n;i++){
    //     printf("\n");
    //     for(int j=0;j<k;j++){
    //         printf("%.4f", centroids[i][j]);
    //         if(j<d-1)
    //             printf(",");
    //     }
    // }
    //---------------end print points:----------------

    //---------------print matrix[n]:--------------
    // printf("centroids indexes:\n");
    // for(int i=0;i<n;i++){
    //     printf("%d,",pointsCentroidsIndex[i]);
    // }
    //---------------end print matrix----------------

    //---------------free memory---------------------

    return 0;
}