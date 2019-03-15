%{ 
    int count = 0; 
    int classCount = 0;
    int inhCount = 0;
    char *className[100];
    char *array[100];
    int classIndex = 0;
    int objCount = 0;
    char *objName[300];
    int objIndex=0;
    int constCount=0;
    char *constName[500];
    int constIndex=0;
    int prevClassLineNo = -1;
    int prevInhLineNo = -1;
    int prevConstLineNo = -1;
    int prevObjLineNo = -1;
%} 
%% 
(\/\/.*|\/\*(.*(\n*))\*\/|\".*\") ;
((public|private|protected)[ \t\n]+)?class[ \t\n]+([$_a-zA-Z][$_a-zA-Z0-9]*)([ \t\n]+extends[ \t\n]+[$_a-zA-Z][$_a-zA-Z0-9]*)([ \t\n]+implements[ \t\n]+[$_a-zA-Z][$_a-zA-Z0-9]*([ \t\n]*,[ \t\n]*[$_a-zA-Z][$_a-zA-Z0-9]*)*)?[ \t\n]* {
    int i=0;
    array[i] = strtok(yytext," \n\t\r{");

    while(array[i]!=NULL)
    {
    array[++i] = strtok(NULL," \n\t\r{");
    }
    i=0;
    while(strcmp(array[i],"class")!=0){
        i++;
    }
    i++;
    // strcpy(className[classIndex],array[i]);
     className[classIndex]= array[i];
        // printf("clasname - %s\n",className[classIndex]);
        for(int j=0;j<strlen(className[classIndex]);j++){
            if(className[classIndex][j]=='{'){
                className[classIndex][j] = '\0';
                // printf("after- %s\n",className[classIndex]);
            }    
        }
    classIndex++;
}
((public|private|protected)[ \t\n]+)?(static[ \t\n]+)?class[ \t\n]+([$_a-zA-Z][$_a-zA-Z0-9]*)([ \t\n]+extends[ \t\n]+[$_a-zA-Z][$_a-zA-Z0-9]*)?([ \t\n]+implements[ \t\n]+[$_a-zA-Z][$_a-zA-Z0-9]*([ \t\n]*,[ \t\n]*[$_a-zA-Z][$_a-zA-Z0-9]*)*)?[ \t\n]* {
        classCount++;
        int i=0;
        array[i] = strtok(yytext," \n\t\r{");

        while(array[i]!=NULL)
        {
        array[++i] = strtok(NULL," \n\t\r{");
        }
        i=0;
        while(strcmp(array[i],"class")!=0){
            i++;
        }
        i++;
        // strcpy(className[classIndex],array[i]);
        className[classIndex]= array[i];
        // printf("classname - %s\n",className[classIndex]);
        for(int j=0;j<strlen(className[classIndex]);j++){
            if(className[classIndex][j]=='{'){
                className[classIndex][j] = '\0';
                // printf("after- %s\n",className[classIndex]);
            }    
        }
        classIndex++;
    }
([ \t\n]*(([$_a-zA-Z][$_a-zA-Z0-9]*))((\[\])*)([ \t\n]*)(<(.*?)>)?([ \t\n]*)([$_a-zA-Z][$_a-zA-Z0-9]*)([ \t\n]*)(=|,|;)) {
        int i=0;
        array[i] = strtok(yytext," \n\t\r{[<");
        while(array[i]!=NULL)
        {
        array[++i] = strtok(NULL," \n\t\r{[<");
        }
        objName[objIndex++] = array[0];
 }   

((public|private|protected)[ \t\n]+)?([$_a-zA-Z][$_a-zA-Z0-9]*)[ \t\n]*\((([$_a-zA-Z][$_a-zA-Z0-9]*([ \t\n]*((\[\][ \t\n]*)|([ \t\n]+\[\]))?)[ \t\n]+[$_a-zA-Z][$_a-zA-Z0-9]*([ \t\n]*((\[\][ \t\n]*)|([ \t\n]+\[\])))?)([ \t\n]*,[ \t\n]*([$_a-zA-Z][$_a-zA-Z0-9]*([ \t\n]*((\[\][ \t\n]*)|([ \t\n]+\[\]))?)[ \t\n]+[$_a-zA-Z][$_a-zA-Z0-9]*([ \t\n]*((\[\][ \t\n]*)|([ \t\n]+\[\])))?))*)*\)[ \t\n]*([^;]|$) {
    // printf("---%s---\n",yytext);
    int i=0;
    array[i] = strtok(yytext," \n\t\r(");
    while(array[i]!=NULL) {
    array[++i] = strtok(NULL," \n\t\r(");
    }
    constName[constIndex]=array[0];
    if (strcmp(array[0],"public")==0 || strcmp(array[0],"private")==0 || strcmp(array[0],"protected")==0){
        constName[constIndex]=array[1];
    }
    constIndex++;
    // int k=0;
    // // printf("//%s\n", constructorName);
    // while(className[k]!=NULL){
    //     // printf("names-%s\n",className[k]);
    //     if(strcmp(className[k], constructorName)==0){
    //         constCount++;
    //         break;
    //     }
    //     k++;
    // }

}
. ;
[\n] {yylineno++;} 
%% 

int yywrap(){} 

int main(){ 
  
    FILE *fp; 
    char filename[50]; 
    printf("Enter the filename: \n"); 
    scanf("%s",filename); 
    fp = fopen(filename,"r"); 
    yyin = fp; 
    
    yylex(); 
    int i = 0;
    while(className[i]!=NULL){
        // printf("stored classname - %s//\n",className[i]);
        for(int j=0;j<strlen(className[i]);j++){
            if(className[i][j]=='{'){
                className[i][j] = '\0';
                // printf("after- %s\n",className[i]);
            }    
        }
        i++;
    }  
    i=0;
    int j = 0;
    while(objName[i]!=NULL){
        j=0;
        while(className[j]!=NULL){
            if(strcmp(className[j],objName[i])==0){
                objCount++;
                break;
            }    
            j++;
        }
        i++;
    }
    i=0;
    j = 0;
    while(constName[i]!=NULL){
        j=0;
        while(className[j]!=NULL){
            if(strcmp(className[j],constName[i])==0){
                constCount++;
                break;
            }    
            j++;
        }
        i++;
    }
    printf("Object def - %d\n",objCount);
    printf("Class Count-%d\n Constructor Count-%d\nInheritance Class Count-%d\n" , classCount,constCount, inhCount); 
    return 0; 
} 