#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fp, *fp1;
    char *line = NULL, *line1 = NULL;
    size_t len = 0, read, len1 = 0, read1;
    int i=0;

    fp = fopen("Employee.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        fp1 = fopen("Department.csv", "r");
        if (fp1 == NULL)
            exit(EXIT_FAILURE);
        int j=0;
        while ((read1 = getline(&line1, &len1, fp1)) != -1) {
            if(i==0 && j==0){
                line = strtok(line, "\n");
                printf("%s,%s" ,line, line1);
                j++;
                break;
            }
            else if(i!=0 && j!=0){
                line = strtok(line, "\n");
                printf("%s,%s" ,line, line1);
            }
            else if(i!=0 && j==0){
                j++;
                continue;
            }
            j++;
        }
        i++;
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
    fclose(fp1);
    if (line1)
        free(line1);
    exit(EXIT_SUCCESS);
    return 0;
}