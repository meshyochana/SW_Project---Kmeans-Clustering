#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t maxCharNumber = 10; 
    char* str = (char*) calloc(maxCharNumber, sizeof(char));
    int i = 0;

    printf("Enter input: ");
    //(str[i] != 'z') use to demonstrate end of file when debuging
    while((str[i] = getchar()) && (str[i] != 'z')){
        i++;
        if(i==maxCharNumber){
            maxCharNumber *= 2;
            str = (char*)realloc(str, sizeof(char) *  maxCharNumber);
        }
    }
    str[i] = '\0';

    printf("%s", str);
    printf("end");
    free( (void *) str);
    return 0;
}