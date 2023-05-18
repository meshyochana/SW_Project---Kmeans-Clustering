#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

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

int main();
void kmeans();
void assign();
void update();
char convergence();
double distance_pp(double*, double*);
int argmin_distance(double**, double*);
void vec_sum(double*, double*);
double* vec_div(double*, int);

int main()
{
    /*to do*/
    kmeans();
    return 0;
}

void kmeans()
{
    c_size_arr = (int*)calloc(K, sizeof(int));
    c_sum_arr = (double**)calloc(K, sizeof(double*));

    /*...*/

    /*example:*/
    double p_arr[3][2] = {{1,0}, {3,0}, {5,0}};
    double c_arr[2][2] = {{0,0},{1,1}};
    d=2;
    N=3;
    K=2;

    int i;
    for(i=0; i<iterations; i++)
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
}


void assign(int n, points, centrieds)
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