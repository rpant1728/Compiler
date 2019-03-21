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
AND {return (AND);}
OR {return (OR);}
[_a-zA-Z][_a-zA-Z0-9]* {return (ID);}
[0-9]+ {return (NUM);}
\<\= {return (LE);}
\>\= {return (GE);}
\!\= {return (NE);}
\< {return (LESS);}
\> {return (GREATER);}
\= {return (EQ);}
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