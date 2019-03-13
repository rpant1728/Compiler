%{
#include <iostream>
using namespace std;
int yylex();
int yyerror(char *s);

%}

%token SELECT PROJECT PRODUCT JOIN LESS GREATER EQ LE GE NE AND OR DOT ID LP RP STRING NUM COMMA SEM

%type <name> ID
%type <number> NUM
%type <str> STRING

%union{
	char name[20];
    int number;
    char str[32];
}

%%

S:
  Select 
  | Project 
  | Product
  | Join 
;

Select:
    SELECT LESS cond GREATER LP ID RP
;
cond:
    cond1
    | cond AND cond1
    | cond OR cond1
;
cond1: 
    ID eq STRING
    | ID OP NUM    
;    
OP:
    LESS
    | GREATER
    | EQ
    | LE
    | GE
    | NE
;
Project: PROJECT LESS attr_list GREATER LP ID RP
;
attr_list: attr_list COMMA attr_list ID
    | ID
;
Product: LESS ID GREATER PRODUCT LP ID GP 
;
Join: LESS ID GREATER JOIN LESS cond2 GREATER LESS ID GREATER
;
cond2:
    cond3
    | cond2 AND cond3
;
cond3: 
    ID DOT ID EQ ID DOT ID
;  

%%

int yyerror(char *s)
{
	printf("Syntax Error on line %s\n", s);
	return 0;
}

int main()
{
    yyparse();
    return 0;
}