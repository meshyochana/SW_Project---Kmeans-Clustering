#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum boolean {
    FALSE,    // 0
    TRUE,  // 1
};

//---------------func prototype:--------------------
int readInput(int* n,int* d, double*** points);
int initCentroids(int k, int d, double*** centroids, double** points);
int initPointsCentroidsIndex(int n, int k, int** pointsCentroidsIndex);
void kmeans();
void assign();
void update();
char convergence();
double distance_pp(double*, double*);
int argmin_distance(double**, double*);
void vec_sum(double*, double*);
double* vec_div(double*, int);

int main(int argc, char *argv[])
{
    // int k = 100; // for debuging mode
    if(argc == 1){ // no arguments have been passed to main
        printf("An Error Has Occurred");
        return 0;
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
    c_size_arr = (int*)calloc(K, sizeof(int));
    c_sum_arr = (double**)calloc(K, sizeof(double*));

    /*...*/

    /*example:*/
    double p_arr[3][2] = {{1,0}, {3,0}, {5,0}};
    double c_arr[2][2] = {{0,0},{1,1}};
    d=2;
    N=3;
    K=2;

    for(int i=0; i<iterations; i++)
    {
        assign(); /*a_i_dict := {cluster index : [point indices]}*/
        update(); /*delta_c := maximum distance between the prev. and cur. centroids*/ 
        if (convergence())
        {
           break; 
        }
            
    }

    free(c_size_arr);
    free(c_sum_arr);

    //---------------free memory---------------------
    free(*points);
    free(points);
    free(*centroids);
    free(centroids);
    free(*prevCentroids);
    free(prevCentroids);
    free(pointsCentroidsIndex);
    return 0;
}

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

/*---Global Variables---*/
double epsilon = 0.001;
int iterations = 200;
double delta_c = 0;
int K;
long N;
int d;
double **p_arr; /*points array [N*d]*/
double **c_arr; /*centroinds array [k*d]*/ 
double **c_sum_arr; /*centroinds sum array [k*d]*/
int *c_size_arr; /*size of each cluster array [k*1]*/

// meshi part:

void assign()
{
    /*Assign every point to the closest cluster*/

    int i;
    int min_index;
    
    memset(c_sum_arr, 0, sizeof(c_sum_arr));
    memset(c_size_arr, 0, sizeof(c_size_arr));
   
    for(i = 0; i < N; i++)
    {
        min_index = argmin_distance(c_arr,p_arr[i]);
        vec_sum(c_sum_arr[min_index], p_arr[i]);
        c_size_arr[min_index] += 1;
    }
}


void update()
{
    /*Update the centroids coordinates to be 
    the center of mass of their associated points*/
    
    delta_c = 0;
    int length;
    int i;
    double* new_c = calloc(d, sizeof(int));

    for(i = 0; i < K; i++)
    {
        length = c_size_arr[i];
        if (length!=0)
        {
            new_c = vec_div(c_sum_arr[i],length);
            delta_c = fmax(distance_pp(new_c,c_arr[i]),delta_c);
            c_arr[i] = new_c;   
        }
    }
    free(new_c);
}


char convergence()
{
    /*Check if the condition for convergence is met*/
    if (delta_c < epsilon)
    {
        return 1;
    }  
    return 0;
}



double distance_pp(double *p1, double *p2)
{
    /*Calculate the euclidean distance between two points in R^d*/
    int i;
    double dist= 0.0;
    for(i = 0; i < d; i++)
    {
        dist += pow((p1[i] - p2[i]) , 2);
    }
    dist = sqrt(dist);
    return dist;
}


int argmin_distance(double **a, double *p)
{
    /*Input: c_arr-list of centroids [k*d], p-point in R^d. 
    Maintaining the minimum index from p to the centroids*/
    int i;
    int min_index = 0;
    double d_min = distance_pp(a[0],p);
    double d_cur;
    for(i = 0; i < K; i++)
    {
        d_cur = distance_pp(a[i],p);
        if (d_cur<d_min)
        {
            min_index = i;
            d_min = d_cur;
        }
    }
    return min_index;
}


void vec_sum(double *v1, double *v2)
{
    /*Sum v2 into v1, each component seperately*/

    int i;
    for(i = 0; i < d; i++)
    {
        v1[i] += v2[i];
    }
}


double *vec_div(double *v1, int l)
{
    /*Divide v1 by l, each component seperately*/

    int i;
    for (i = 0; i < d; i++)
    {
        v1[i] = (double)(v1[i] / l);
    }
    return v1;
}


