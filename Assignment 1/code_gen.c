#include <stdio.h>
#include "lex.c"
#include "name.c"

char *factor (void);
char *term (void);
char *expression (void);
char *expr1(void);

extern char *newname();
extern void freename(char *name);

void statement(){
    char *tempvar;
    if(match(NUM_OR_ID)){
        char var[100];
        int i=0;
        while(i<yyleng){
            var[i] = *(yytext+i);
            i++;
        }
        var[i] = '\0';
        advance();
        // printf("%c", *(yytext));
        if(match(COL)){
            advance();
            if(!match(EQU)){
                fprintf(stderr, "%d: ':=' expected\n", yylineno);
            }
            else{ 
                advance();
                tempvar = expr1();
                if(!match(SEMI)){
                    fprintf(stderr, "%d: ';' expected\n", yylineno);
                }
                else{
                    printf("%s <- %s", var, tempvar);
                    advance();
                }
            }
        }
        else{
            advance();
            tempvar = expr1();
            if(!match(SEMI)){
                fprintf(stderr, "%d: ';' expected\n", yylineno);
            }
            else{
                printf("%s <- %s", var, tempvar);
                advance();
            }
        }
    }
}

void statements(){
    /*  statements -> statement statements | statement  */
    char *tempvar;
    // int i = 0;
    while(!match(EOI)){
        statement();
    }
    return;
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

char *term(){
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
