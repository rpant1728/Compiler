// Grammar:
// stmt_list ==> stmt_list S; | S;
// S ==> Select | Project | Product | Join
// Select ==> "SELECT" "<" cond ">"

%{
#include <bits/stdc++.h>
using namespace std;
extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int yylineno;
int yyerror(char *s);

%}

%token SELECT PROJECT PRODUCT JOIN LESS GREATER EQ LE GE NE AND OR DOT ID LP RP STRING NUM COMMA SEM

%left OR
%left AND

%type <name> ID
%type <number> NUM
%type <str> STRING

%union{
	char name[20];
    int number;
    char str[32];
}
%start stmt_list
    
%%
stmt_list:
    stmt_list S SEM
    |S SEM
;    
S:
  Select    {printf("Line No.%d: valid Syntax\n", yylineno);}
  | Project {printf("Line No.%d: valid Syntax\n", yylineno);}
  | Product {printf("Line No.%d: valid Syntax\n", yylineno);}
  | Join    {printf("Line No.%d: valid Syntax\n", yylineno);}
  | error
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
    ID EQ STRING
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
attr_list: attr_list COMMA ID
    | ID
;
Product: LP ID RP PRODUCT LP ID RP 
;
Join: LP ID RP JOIN LESS cond2 GREATER LP ID RP
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
  extern char *yytext;
  printf("Line No.%d ERROR: %s at symbol %s\n",yylineno, s, yytext);
}

int main(int argc, char* argv[])
{
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("File not found\n");
        return 0;
    }
    yyin = fp;
	do {
		yyparse();
	} while(!feof(yyin));
	return 0;
}