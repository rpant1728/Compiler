# include <stdio.h>
# include <string.h>
# include <stdlib.h>

FILE *inter, *assembly;

typedef struct _map{
    char var[20];
    struct _map *next;
} map;

map *head = NULL;
map *last = NULL;

map *create_node(char *arr){
    map *entry = (map*)malloc(sizeof(map)); 
    entry->next = NULL;
    strcpy(entry->var, arr);
    return entry;
}


map *search(char *entry){
    map *temp = head;
    while(temp != NULL){
        if(strcmp(temp->var, entry) == 0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void insert(char *arr){
    map *temp = search(arr);
    if(temp==NULL){
        if (head == NULL) {
            map *entry = create_node(arr);
            head = entry;
            last = head;
        }
        else {  
            map *entry = create_node(arr);
            last->next = entry;
            last = last->next;
        }
    }
}




