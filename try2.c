#include <stdio.h>
#include <stdlib.h>

enum checkInputLine {
    FIRST_LINE,    // 0
    NOT_FIRST_LINE,  // 1
};

int main() {
    int maxNumberLen = 200;
    char str[200] = {0};
    int n = 0;
    int d = 0;
    enum checkInputLine inputLine = FIRST_LINE;
    
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
            if(inputLine == FIRST_LINE && str[i] == '\n'){
                d = indexOfPoints_nxd + 1;
                inputLine = NOT_FIRST_LINE;
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
    } while((str[i] = getchar()) && (str[i] != 'z'))
    // (str[i] != 'z') use to demonstrate end of file when debuging
    printf("end");
}