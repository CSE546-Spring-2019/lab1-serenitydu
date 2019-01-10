/*Author: Chenghao Du*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    /*handle arguments*/
    char* inputName;
    char* search;
    char* outputName;
    char buffer[100];
    /*File pointer*/
    FILE *inputFile, *outputFile;
    int size = 0;
    if (argc != 4){
        printf("ERROR: Please enter 4 arguments\n");
    }
    inputName = argv[1];
    search = argv[2];
    outputName = argv[3];

    /*check arguments*/
    if((inputFile = fopen(inputName,"rb")) == NULL){
        printf("ERROR: Can not open input file %s\n", inputName);
        exit(1);
    }
    if((outputFile = fopen(outputName,"wb")) == NULL){
        printf("ERROR: Can not open output file %s\n", outputName);
        exit(1);
    }

    /*get file size*/
    fseek(inputFile, 0, SEEK_END);
    size = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);
    printf("Size of file is %d\n", size);
    while(!feof(inputFile)){
        fread(buffer, 1, 100, inputFile);
        printf("%s\n", buffer);
        fwrite(buffer, 1, 100, outputFile);
    }
    
    //Number of matches =
    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
