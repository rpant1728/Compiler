%{ 
    int count = 0; 
    int classCount = 0;
    int inhCount = 0;
    char *className[100];
    char *array[100];
    int classIndex = 0;
    int objCount = 0;
    char *objName;
    int objIndex=0;
    int constCount=0;
    char *constructorName;
    int constIndex=0;
    int prevClassLineNo = -1;
    int prevInhLineNo = -1;
    int prevConstLineNo = -1;
    int prevObjLineNo = -1;
    int blankline = 0;
    int commentline = 0;
    int codeline = 0;
%} 
%% 
\".*\" ;
(\/\/.*\n|\/\*(.*(\n*))*\*\/([ \t]*\n)?) {
    for (int k=0;k<strlen(yytext);k++){
        if(yytext[k]=='\n')
            commentline++;
    }
}
^([ \t]*\n) {blankline++;yylineno++;

        printf("blankline - %s\n",yytext);
        }
\n {codeline++;}        
. ;
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
    
    // i=0;
    // j = 0;
    // while(constName[i]!=NULL){
    //     j=0;
    //     while(className[j]!=NULL){
    //         if(strcmp(className[j],constName[i])==0){
    //             constCount++;
    //             break;
    //         }    
    //         j++;
    //     }
    //     i++;
    // }
    printf("Object Declarations - %d\n",objCount);
    printf("Class Definitions - %d\nConstructor Definitions - %d\nInherited Class Definitions - %d\n", classCount, constCount, inhCount); 
    printf("codeline - %d , commentline - %d , blankline - %d\n",codeline,commentline,blankline);
    return 0; 
} 