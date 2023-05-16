#include <stdio.h>
#include <stdlib.h>

enum boolean {
    FALSE,    // 0
    TRUE,  // 1
};


int main() {
    int maxNumberLen = 200;
    char str[200] = {0};
    int n = 0;
    int d = 0;
    enum boolean isFirstLine = TRUE;
    
    //--------for daynamic allocation--------
    size_t sizeOfPoints_nxd = 100;
    size_t sizeOfpoints = 100;  
    double* points_nxd = (double*) calloc(sizeOfPoints_nxd, sizeof(double));
    double** points = (double*) calloc(sizeOfpoints, sizeof(double*));
    //--------------------------------
    points[0] = points_nxd;
    int indexOfPoints_nxd = 0;
    int indexOfpoints = 1; 
    int i = 0;
    
    str[i] = getchar();
        do{
        if(str[i] == ',' || str[i] == '\n'){
            if(isFirstLine == TRUE && str[i] == '\n'){
                d = indexOfPoints_nxd + 1;
                isFirstLine = FALSE;
            }
            str[i] = '\0';
            points_nxd[indexOfPoints_nxd] = strtod(str, NULL);
            indexOfPoints_nxd++;
            i = 0;
        }
        else
            i++;
        if(indexOfPoints_nxd == sizeOfPoints_nxd){
            sizeOfPoints_nxd *= 2;
            points_nxd = (double*)realloc(points_nxd, sizeof(double) *  sizeOfPoints_nxd);
        }
    } while((str[i] = getchar()) && (str[i] != 'z'));
    // (str[i] != 'z') use to demonstrate end of file when debuging
    n = indexOfPoints_nxd/d;
    for(i=0;i<n;i++){
        if(i==sizeOfpoints){
            sizeOfpoints *= 2;
            points = (double**)realloc(points, sizeof(double*) *  sizeOfpoints);
        }
        points[i] = points_nxd +i*d;
    }
    printf("input matrix:");
    for(i=0;i<n;i++){
        printf("\n");
        for(int j=0;j<d;j++){
            printf("%.4f", points[i][j]);
            if(j<d-1)
                printf(",");
        }
    }
    return 0;
}