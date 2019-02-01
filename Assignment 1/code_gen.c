#include <stdio.h>
#include "lex.c"
#include "name.c"
#include "code_gen.h"

void statements(){
    /*  statements -> statement statements | statement  */
    char *tempvar;
    while(!match(EOI)){
        statement();
    }
    return;
}

void statement(){
    char *tempvar, *tempvar1;
    char var[100];
    int i=0;
    while(i<yyleng){
        var[i] = *(yytext+i);
        i++;
    }
    var[i] = '\0';
    if(match(NUM_OR_ID)){
        advance();
        if(match(ASS)){
            advance();
            tempvar = expr1();
            if(!match(SEMI)){
                fprintf(stderr, "%d: ';' expected\n", yylineno);
            }
            else{
                printf("    %s <- %s", var, tempvar);
                advance();
            }
        }        
    }
    if(match(WHILE)){
        advance();
        tempvar = expr1();
        if(match(DO)){
            advance();
            printf("while (%s) do { \n", tempvar);
            statement();
            printf("\n}");
        }
    }
    if(match(IF)){
        advance();
        tempvar = expr1();
        if(match(THEN)){
            advance();
            printf("if (%s) then { \n", tempvar);
            statement();
            printf("\n}");
        }
    }
    if(match(BEG)){
        advance();
        printf("begin { \n");
        // stmt_list();
        while (!match(END)){
            statement();
        }
        printf("\n} end \n");
        advance();           
    }
}

char *expr1(){
    char *tempvar, *tempvar1, *tempvar2;
    tempvar = expression();
    // advance();
    if(match(EQU)){
        advance();
        tempvar2 = newname();
        tempvar1 = expression();
        printf("    %s <- %s = %s\n", tempvar2, tempvar, tempvar1);
        return tempvar2;
    }
    else if(match(LT)){
        advance();
        tempvar2 = newname();
        tempvar1 = expression();
        printf("    %s <- %s < %s\n", tempvar2, tempvar, tempvar1);
        return tempvar2;
    }
    else if(match(GT)){
        advance();
        tempvar2 = newname();
        tempvar1 = expression();
        printf("    %s <- %s > %s\n", tempvar2, tempvar, tempvar1);
        return tempvar2;
    }
    return tempvar;
}

char *expression(){
    /* expression -> term expression'
     * expression' -> PLUS term expression' |  epsilon
     */
    char  *tempvar, *tempvar1;
    tempvar = term();
    while(1){
        if(match(PLUS)){ 
            advance();
            tempvar1 = term();
            printf("    %s += %s\n", tempvar, tempvar1);
            freename(tempvar1);
        }
        else if(match(MINUS)){
            advance();
            tempvar1 = term();
            printf("    %s -= %s\n", tempvar, tempvar1);
            freename(tempvar1);
        }
        else break;
    }
    return tempvar;
}
char *term() {
    char  *tempvar, *tempvar1 ;
    tempvar = factor();
    while(1){
        if(match(TIMES)){ 
            advance();
            tempvar1 = term();
            printf("    %s *= %s\n", tempvar, tempvar1);
            freename(tempvar1);
        }
        else if(match(DIV)){
            advance();
            tempvar1 = term();
            printf("    %s /= %s\n", tempvar, tempvar1);
            freename(tempvar1);
        }
        else break;
    }
    return tempvar;
}

char *factor(){
    char *tempvar;

    if(match(NUM_OR_ID)){
	/* Print the assignment instruction. The %0.*s conversion is a form of
	 * %X.Ys, where X is the field width and Y is the maximum number of
	 * characters that will be printed (even if the string is longer). I'm
	 * using the %0.*s to print the string because it's not \0 terminated.
	 * The field has a default width of 0, but it will grow the size needed
	 * to print the string. The ".*" tells printf() to take the maximum-
	 * number-of-characters count from the next argument (yyleng).
	 */
        printf("    %s = %0.*s\n", tempvar = newname(), yyleng, yytext);
        advance();
    }
    else if(match(LP)){
        advance();
        tempvar = expression();
        if(match(RP))
            advance();
        else
            fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
    else
	    fprintf(stderr, "%d: Number or identifier expected\n", yylineno);
    return tempvar;
}