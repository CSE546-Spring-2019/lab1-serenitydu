/* Author: Chenghao Du*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]){
    /* handle arguments */
    char* inputName;
    char* search;
    char* outputName;
    char buffer[100];
    /* File pointer */
    FILE *inputFile, *outputFile;
    /* size of the file*/
    int size = 0;
    int wordSize = 0;
    /* count the number of a string appears in the file*/
    int countWord = 0;
    int count = 0;
    int i =0, l = -1;
    int m=0, n=0;
    int checkA[20] = {0};

    /* check if the input is valid*/
    if (argc != 4){
        printf("ERROR: Please enter 4 arguments\n");
    }
    inputName = argv[1];
    search = argv[2];
    outputName = argv[3];

    /* check arguments */
    if((inputFile = fopen(inputName,"rb")) == NULL){
        printf("ERROR: Can not open input file %s\n", inputName);
        exit(1);
    }
    if((outputFile = fopen(outputName,"wb")) == NULL){
        printf("ERROR: Can not open output file %s\n", outputName);
        exit(1);
    }
    if(strlen(search)> 20){
        printf("ERROR: The search string should smaller than 20 characters.\n");
        exit(1);
    }

    /* get file size */
    fseek(inputFile, 0, SEEK_END);
    size = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    printf("Size of file is %d\n", size);

    wordSize = strlen(search);

    /*Using KMP*/
    fread(buffer, 1, 100, inputFile);
    fseek(inputFile, 0, 0);
    while(!feof(inputFile)){
        
        //find nextf
        checkA[0] = -1;
        while (i < wordSize -1){
            if (l==-1||search[i] == search[l]){
                i++; 
                l++;   
                checkA[i] = l;
            }
            else{
                l = checkA[l];  
            }
        }
        //check match
        while (m < 100){
            if (n==-1||buffer[m] == search[n]){
                m++; n++;
            }
            else{
                n = checkA[n];
            }
            if (n == wordSize){
                countWord++;
                n = 0;
                m -= wordSize-1;
            }
        }
        fseek(inputFile,(100-wordSize),(100-wordSize)*count);
        fread(buffer, 1, 100, inputFile);
        count++;
        i =0;
        l = -1;
        m=0;
        n=0;
        //printf("%s\n", buffer);
    }
    printf("Number of matches = %d\n", countWord);

    /* Print output to the file.*/
    fprintf(outputFile, "Size of file is %d\n", size);
    fprintf(outputFile, "Number of matches = %d\n", countWord);

    /* Close all the file*/
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}


