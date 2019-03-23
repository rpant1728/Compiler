#include <bits/stdc++.h>
using namespace std;

list<pair<char*, int>> sel;
list<pair<char*, int>> table;
char *s;
int value;
char op;

void code(char *str){
    FILE *f = fopen("code.c", "w");
    fprintf(f, "#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\ntypedef struct Field{\n    char type[20];\n    char name[20];\n} Field;\n\nint getIndex(Field fields[], char *name, int len){\n    for(int i=0; i<len; i++){\n        if(strcmp(fields[i].name, name) == 0){\n            return i;\n        }\n    }\n    return -1;\n}\n\nint main(){\n    FILE *fp;\n    char *line = NULL;\n    size_t len = 0, read;\n    int i = 0, j = 0;\n    int %s = %d;\n    char *field = \"%s\";\n    Field fields[20];\n\n    fp = fopen(\"%s.csv\", \"r\");\n    if (fp == NULL)\n        exit(EXIT_FAILURE);\n\n    while ((read = getline(&line, &len, fp)) != -1) {\n        if(i == 0){\n            char *ele, *ptr;\n            ele = strtok_r(line, \",\", &ptr);\n            char *temp = strtok(ele, \"()\");\n            strcpy(fields[j].name, temp);\n            temp = strtok(NULL, \"()\");\n            strcpy(fields[j].type, temp); \n            while((ele = strtok_r(NULL, \",\", &ptr)) != NULL){\n                j++;\n                char *temp = strtok(ele, \"()\");\n                strcpy(fields[j].name, temp);\n                temp = strtok(NULL, \"()\");\n                strcpy(fields[j].type, temp); \n            }\n        }\n        else{\n            int index = getIndex(fields, field, j+1);\n            strtok(line, \",\");\n            for(int i=0; i<index-1; i++){\n                strtok(NULL, \",\");\n            }\n            int %s1 = atoi(strtok(NULL, \",\"));\n            if(%s1 %c %s){\n                printf(\"Found\");\n            }\n        }\n        i++;\n    }\n\n    fclose(fp);\n    if (line)\n        free(line);\n    exit(EXIT_SUCCESS);\n}\n", s, value, s, str, s, s, op, s);
}

void save_vars(char *str, char c, int val){
    // sel.push_back(make_pair(s, val));
    s = str;
    value = val;
    op = c;
}

void print(char *s){
    if(s[0] == 'A'){
        s = strtok(s, " ");
    }
    cout << "cond" << s << endl;
}