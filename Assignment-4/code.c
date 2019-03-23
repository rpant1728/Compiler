#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Field{
    char type[20];
    char name[20];
} Field;

int getIndex(Field fields[], char *name, int len){
    for(int i=0; i<len; i++){
        if(strcmp(fields[i].name, name) == 0){
            return i;
        }
    }
    return -1;
}

int main(){
    FILE *fp;
    char *line = NULL;
    size_t len = 0, read;
    int i = 0, j = 0;
    int salary = 200;
    char *field = "salary";
    Field fields[20];

    fp = fopen("Employee.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        if(i == 0){
            char *ele, *ptr;
            ele = strtok_r(line, ",", &ptr);
            char *temp = strtok(ele, "()");
            strcpy(fields[j].name, temp);
            temp = strtok(NULL, "()");
            strcpy(fields[j].type, temp); 
            while((ele = strtok_r(NULL, ",", &ptr)) != NULL){
                j++;
                char *temp = strtok(ele, "()");
                strcpy(fields[j].name, temp);
                temp = strtok(NULL, "()");
                strcpy(fields[j].type, temp); 
            }
        }
        else{
            int index = getIndex(fields, field, j+1);
            strtok(line, ",");
            for(int i=0; i<index-1; i++){
                strtok(NULL, ",");
            }
            int salary1 = atoi(strtok(NULL, ","));
            if(salary1 < salary){
                printf("Found");
            }
        }
        i++;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}
