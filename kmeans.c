#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*---Global Variables---*/
int n = 0;
int k = 0;
int d = 0;
int iter = 200; /* defult maximum iteration */

enum boolean {
    FALSE,    /* 0*/
    TRUE  /* 1*/
};

enum errmsg {
    NO_ERROR,       /* 0*/
    GEN_ERR,        /* 1*/
    INVAL_CLUST,    /* 2*/
    INVAL_ITER      /* 3*/
};

/*---------------func prototype:--------------------*/
int isNaturalNumber(char* str);
int readInput(int *n,int *d, double ***points);
int initCentroids(int k, int d, double ***centroids, double **points);
int initPointsCentroidsIndex(int n, int k, int **pointsCentroidsIndex);
void assign(double **points, double **centroides, int **pointsCentroidsIndex);
int update_centroids(double **points, double ***centroides, double ***prevCentroids, int *pointsCentroidsIndex);
double convergence(double **centroides, double **prevCentroids);
double distance_pp(double *p1, double *p2);
int argmin_distance(double *point, double **centroids);
void vec_sum(double *v1, double *v2);
void print_matrix_2d(int n, int m, double **matrix_2d);
double max(double num1, double num2);


int main(int argc, char *argv[])
{
    double epsilon = 0.001;
    int i = 0;
    enum errmsg err = NO_ERROR;
    /*--- define pointers for multidimensional arrays ----*/
    double **points = NULL;
    double **centroids = NULL;
    double **prevCentroids = NULL;
    int *pointsCentroidsIndex = NULL;
    
    /*--- read input from argv ---*/
    /* check if no arguments have been passed to main*/
    if(argc == 1){
        printf("An Error Has Occurred");
        return 1;
    }
    /*check if argv[1] not natural number*/
    if(isNaturalNumber(argv[1]) == FALSE){
        printf("Invalid number of clusters!");
        return 1;
    }
    k = atoi(argv[1]); /* number of clusters (centroids) */
    if(argc > 2){ /* at least 2 arguments have been passed to main */
        /*check if argv[2] is not natural number*/
        if(isNaturalNumber(argv[2]) == FALSE){
            printf("Invalid maximum iteration!");
            return 1;
        }
        iter = atoi(argv[2]);/* maximum iteration */
    }

    /*--- input check: ---*/
    if(k <= 1){
        printf("Invalid number of clusters!");
        return 1;
    }
    if(iter <= 1 || 1000 <= iter){
        printf("Invalid maximum iteration!");
        return 1;
    }

    /*--- init routine: ---*/
    err = readInput(&n, &d, &points);

    if(err == NO_ERROR && n <= k)
        err = INVAL_CLUST;
    
    if(err == NO_ERROR)
        err = initCentroids(k, d, &centroids, points);

    if(err == NO_ERROR)
        err = initCentroids(k, d, &prevCentroids, points);

    if(err == NO_ERROR)
        err = initPointsCentroidsIndex(n, k, &pointsCentroidsIndex);
    
    if(err == NO_ERROR){
    /*--- kmeans algo: ---*/
        for(i = 0; i < iter; i++)
        {
            assign(points, centroids, &pointsCentroidsIndex);

            err = update_centroids(points, &centroids, &prevCentroids, pointsCentroidsIndex);
        
            if(err != NO_ERROR || convergence(centroids, prevCentroids) < epsilon){
                break;
            }
        }
    }
    if(err == NO_ERROR){
        print_matrix_2d(k, d, centroids);
        free(*points);
        free(*centroids);
        free(*prevCentroids);
    }
    if(err == GEN_ERR)
        printf("An Error Has Occurred\n");
    if(err == INVAL_CLUST){
        printf("Invalid number of clusters!");
        free(*points);
    }

    /*--- deallocate memory ---*/
    
    free(points);
    free(centroids);
    free(prevCentroids);
    free(pointsCentroidsIndex);
    if(err == NO_ERROR)
        return 0;
    return 1;
}

int isNaturalNumber(char *str) {
    if (str == NULL || *str == '\0') {
        return FALSE; /* empty string*/
    }
    while (*str) {
        if ((*str) < '0' || '9' < (*str) ) {
            return FALSE; /* Not a natural number*/
        }
        str++;
    }
    return TRUE; /* Valid natural number*/
}

int readInput(int* n,int* d, double*** points)
{
    int indexOfPoints_nxd = 0;
    int i = 0;
    char str[200] = {0};
    enum boolean isFirstLine = TRUE;
    /*--------for daynamic allocation--------*/
    size_t sizeOfPoints_nxd = 100;
    size_t sizeOfpoints = 100;  
    double* points_nxd = (double*) calloc(sizeOfPoints_nxd, sizeof(double));
    *points = (double**) calloc(sizeOfpoints, sizeof(double*));
    /*--------------------------------------- */
    if(points_nxd == NULL || (*points) == NULL){
        free(points_nxd);
        free(*points);
        return 1;
    }
    /* get data from stdin and write it daynamicly to points_nxd*/
    str[i] = getchar();
        do{
        if(str[i] == ',' || str[i] == '\n'){
            if(isFirstLine == TRUE && str[i] == '\n'){
                *d = indexOfPoints_nxd + 1;
                isFirstLine = FALSE;
            }
            str[i] = '\0';
            points_nxd[indexOfPoints_nxd] = strtod(str, NULL); /* str to double*/
            indexOfPoints_nxd++;
            i = 0;
        }
        else
            i++;
        if(indexOfPoints_nxd == (int) sizeOfPoints_nxd){
            sizeOfPoints_nxd *= 2;
            points_nxd = (double*)realloc(points_nxd, sizeof(double) *  sizeOfPoints_nxd);
            if(points_nxd == NULL){
                free(*points);
                return 1; /* alloc problem running*/
            }
        }
    str[i] = getchar();
    /* end while condition: (str[i] != 'z') use to demonstrate end of file when debuging*/
    } while(str[i] != EOF && (str[i] != 'z'));

    /* arrange the data in points as an 2 dim array, write daynamicly*/
    *n = indexOfPoints_nxd/(*d);
    *points[0] = points_nxd;
    for(i=0;i<(*n);i++){
        if(i==(int) sizeOfpoints){
            sizeOfpoints *= 2;
            *points = (double**)realloc(*points, sizeof(double*) *  sizeOfpoints);
            if((*points) == NULL){
                free(points_nxd);
                return 1;
            }
        }
        (*points)[i] = points_nxd +i*(*d);
    }
    return 0; /* successful running*/
}

int initCentroids(int k, int d, double*** centroids, double** points){
    int i = 0;
    double* centroides_kxd = (double*) calloc(k*d, sizeof(double));
    *centroids = (double**) calloc(k, sizeof(double*));
    if(centroides_kxd == NULL || (*centroids) == NULL)
        return 1;
    for(i=0;i<k*d;i++){
        centroides_kxd[i] = (*points)[i];
    }
    for(i=0;i<k;i++){
        (*centroids)[i] = centroides_kxd +i*d;
    }
    return 0; /* successful running*/
}

int initPointsCentroidsIndex(int n, int k, int** pointsCentroidsIndex){
    int i = 0;
    *pointsCentroidsIndex = (int*) calloc(n, sizeof(int));
    if((*pointsCentroidsIndex) == NULL)
        return 1;
    for(i = 0; i < k; i++){
        (*pointsCentroidsIndex)[i] = i;
    }
    return 0; /* successful running*/
}

/*Assign every point to the closest cluster*/
void assign(double **points, double **centroides, int **pointsCentroidsIndex)
{
    int i = 0;
    int min_index = 0;
    for(i = 0; i < n; i++){
        min_index = argmin_distance(points[i], centroides);
        (*pointsCentroidsIndex)[i] = min_index;
    }
}

int update_centroids(double **points, double ***centroides, double ***prevCentroids, int *pointsCentroidsIndex)
{
    int i = 0;
    int j = 0;
    int min_index = 0;
    double **temp = NULL;
    int *c_size_arr = (int*) calloc(k, sizeof(int)); /* counts the number of points in every cluster*/
    if(c_size_arr == NULL)
        return 1;

    /*--- swap operation: centroides & prevCentroids ---*/
    temp = *prevCentroids;
    *prevCentroids = *centroides;
    *centroides = temp;

    /*--- set centroides to zeros ---*/
    for(i = 0; i < k; i++)
        for(j = 0; j < d; j++)
            (*centroides)[i][j] = 0.0;

    /*--- sum up every cooordinate in every centroid ---*/
    for(i = 0; i < n; i++)
    {
        min_index = pointsCentroidsIndex[i];
        vec_sum((*centroides)[min_index], points[i]);
        c_size_arr[min_index] += 1;
    }

    /*--- calculate the new C.G for every centroid ---*/
    for(i = 0; i < k; i++)
    {
        for(j = 0; j < d; j++)
        {
            (*centroides)[i][j] = (*centroides)[i][j] / c_size_arr[i];
        }
    }
    
    free(c_size_arr);
    return 0;
}


double convergence(double **centroides, double **prevCentroids)
{
    double delta_c = 0;
    int i = 0;
    /*Check if the condition for convergence is met*/
    for(i = 0; i < k; i++)
        delta_c = max(distance_pp(centroides[i],prevCentroids[i]),delta_c);
    return delta_c;
}



double distance_pp(double *p1, double *p2)
{
    /*Calculate the euclidean distance between two points in R^d*/
    int i = 0;
    double dist= 0.0;
    for(i = 0; i < d; i++)
    {
        dist += pow((p1[i] - p2[i]) , 2);
    }
    dist = sqrt(dist);
    return dist;
}


int argmin_distance(double *point, double **centroids)
{
    /*Input: c_arr-list of centroids [k*d], p-point in R^d. 
    Maintaining the minimum index from p to the centroids*/
    int i = 0;
    int min_index = 0;
    double dist_min = distance_pp(centroids[0], point);
    double dist_cur = 0;
    for(i = 0; i < k; i++)
    {
        dist_cur = distance_pp(centroids[i], point);
        if (dist_cur < dist_min)
        {
            min_index = i;
            dist_min = dist_cur;
        }
    }
    return min_index;
}


void vec_sum(double *v1, double *v2)
{
    int i = 0;
    /*Sum v2 into v1, each component seperately*/
    for(i = 0; i < d; i++)
    {
        v1[i] += v2[i];
    }
}

void print_matrix_2d(int n, int m, double **matrix_2d)
{
    int i = 0;
    int j = 0;
    for( i=0;i<n;i++){
        for(j=0;j<m;j++){
            printf("%.4f", matrix_2d[i][j]);
            if(j<m-1)
                printf(",");
        }
        printf("\n");
    }
}

double max(double num1, double num2){
    if(num1 < num2)
        return num2;
    return num1;
}