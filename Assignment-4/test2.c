#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Field{
    char type[20];
    char name[20];
} Field;

int main(){
    FILE *fp, *fp1;
    char *line = NULL, *line1 = NULL;
    size_t len = 0, read, size = 2, read1;
    int i=0, j=0;
    Field fields[20];

    fp = fopen("Employee.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int index[10];
    char *s[10];
    s[0] = "name";
    s[1] = "salary";

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
            for(int l=0; l<size; l++){
                for(int k=0; k<j+1; k++){
                    if(strcmp(fields[k].name, s[l]) == 0){
                        index[l] = k;
                        break;
                    }
                }
            }
        }
        else{
            char temp[100];
            strcpy(temp, line);
            for(int i=0; i<size; i++){
                strcpy(line, temp);
                if(index[i] == 0){
                    printf("%s", strtok(line, ","));
                }
                else{
                    strtok(line, ",\n");
                    for(int j=0; j<index[i]-1; j++){
                        strtok(NULL, ",\n");
                    }
                    printf("%s", strtok(NULL, ",\n"));
                }
                printf("\n");
            }
        }
        i++;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}