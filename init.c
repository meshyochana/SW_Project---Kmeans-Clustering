//#define  _GNU_SOURCE
#include <stdio.h>
//#include <math.h>
//#include <stdlib.h>

int init(int k, char *fileName)
{
    int d = 1;
    int n = 1;
    int c = 0;
    FILE *pfile;  
    pfile = fopen(fileName,"r");
    if(pfile == NULL) {
        perror("Error in opening file");
    }
    else{
        //first read of the file in order to determine d and n size
        while ((c=fgetc(pfile)) != '\n')
        {
            if (c == ',')
            d++;
        }
        while ((c=fgetc(pfile)) != EOF)
        {
            if (c == '\n')
            n++;
        }
        // Reset the file position indicator
        //fseek(ifp, 0, SEEK_SET);

    }
    printf("\nd size is: %d", d);
    printf("\nn size is: %d", n);
    printf("\nk size is: %d", k);

    fclose( pfile );
    return 0;
}

int main(int argc, char *argv[])
{
    int k = atoi(argv[1]); // number of clusters (centroids)
    int iter = atoi(argv[2]);// maximum iteration
    #if 0
    //for linux operation system:
    char *fileName = NULL;
    size_t bufferSize = 0;
    long charactersRead = 0;
    // get input from user dynamicly
    charactersRead = getline(&fileName, &bufferSize, stdin);
    if (charactersRead == -1) {
        printf("Failed to read input.\n");
        return 1;
    }
    #endif

    //for windows operation system:
    int max_len_fileName = 100;
    char fileNameArr[max_len_fileName];
    char *fileName = &fileNameArr[0];
    fgets(fileName, max_len_fileName, stdin);
    for(int i; i < max_len_fileName; i++){
        if (fileName[i] == '\n')
        {
            fileName[i] = '\0';
            break;
        }
    }

    //for all operation systems:
    printf("file name entered: %s", fileName);
    init(k, fileName);
    printf("\niter: %d", iter);
    return 0;
}