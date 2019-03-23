%option noyywrap
%{
    #include "bison.tab.h"
    #include <bits/stdc++.h>
    #define YY_DECL int yylex()
    using namespace std;
    void showError();
    int yyerror(char *s);
    
%}
%%
SELECT {return (SELECT);}
PROJECT {return (PROJECT);}
CARTESIAN_PRODUCT {return (PRODUCT);}
EQUI_JOIN {return (JOIN);}
AND {yylval.str = yytext; return (AND);}
OR {yylval.str = yytext; return (OR);}
[_a-zA-Z][_a-zA-Z0-9]* {yylval.str = strdup(yytext);return (ID);}
[0-9]+ {yylval.number = atoi(yytext); return (NUM);}
\<\= {yylval.sym = char(*yytext); return (LE);}
\>\= {yylval.sym = char(*yytext); return (GE);}
\!\= {yylval.sym = char(*yytext); return (NE);}
\< {yylval.sym = char(*yytext); return (LESS);}
\> {yylval.sym = char(*yytext); return (GREATER);}
\= {yylval.sym = char(*yytext); return (EQ);}
\. {return (DOT);}
\( {return (LP);}
\) {return (RP);}
\".*\" {return (STRING);}
\, {return (COMMA);}
\; {return (SEM);}
[ \t] {}
[\n] { yylineno++;	}
. {showError();}
%%

void showError(){
    printf("Other input");
}