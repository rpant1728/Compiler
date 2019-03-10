/*** Definition Section has one variable 
which can be accessed inside yylex()  
and main() ***/
%{ 
int count = 0; 
int classCount = 0;
int inhCount = 0;
char *className[100];
char *array[100];
int classIndex = 0;
%} 
  
/*** Rule Section has three rules, first rule  
matches with capital letters, second rule 
matches with any character except newline and  
third rule does not take input after the enter***/
%% 
(\/\/.*|\/\*(.*(\n*))\*\/|\".*\") ;
((public|private|protected)[ \t\n]+)?class[ \t\n]+([$_a-zA-Z][$_a-zA-Z0-9]*)([ \t\n]+extends[ \t\n]+[$_a-zA-Z][$_a-zA-Z0-9]*)([ \t\n]+implements[ \t\n]+[$_a-zA-Z][$_a-zA-Z0-9]*([ \t\n]*,[ \t\n]*[$_a-zA-Z][$_a-zA-Z0-9]*)*)?[ \t\n]* {
    inhCount++;
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
    className[classIndex++]= array[i];
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
        className[classIndex++]= array[i];
    }
. ;
\n  ; 
%% 
  
/*** Code Section prints the number of 
capital letter present in the given input***/
int yywrap(){} 
int main(){ 
  
// Explanation: 
// yywrap() - wraps the above rule section 
/* yyin - takes the file pointer  
          which contains the input*/
/* yylex() - this is the main flex function 
          which runs the Rule Section*/
// yytext is the text in the buffer 
  
// Uncomment the lines below  
// to take input from file 
FILE *fp; 
char filename[50]; 
printf("Enter the filename: \n"); 
scanf("%s",filename); 
fp = fopen(filename,"r"); 
yyin = fp; 
  
yylex(); 
printf("inhCount-%d classCount-%d\n" , inhCount,classCount); 
int i = 0;
// while(className[i]!=NULL){
//     printf("%s\n",className[i++]);
// }  
return 0; 
} 