#include "lex.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *yytext = "begin if a>3 then while a<3 do a:=a+1; end~"; /* Lexeme (not '\0' terminated) */
int yyleng = 0;    /* Lexeme length */
int yylineno = 0;  /* Input line number */

int lex(void){
    static char input_buffer[1024];
    char *current;
    
    current = yytext + yyleng; /* Skip current lexeme */

    while(1){                 /* Get the next one */
        // printf("%s", yytext);
        
        // while(!*current ){
        //     /* Get new lines, skipping any leading
        //     * white space on the line,
        //     * until a nonblank line is found.
        //     */
        //     current = input_buffer;
        //     if(!fgets(input_buffer)){
        //         *current = '\0' ;
        //         return EOI;
        //     }
        //     ++yylineno;
        while(isspace(*current))
            ++current;
        // }
        for(; *current; ++current){ /* Get the next token */
            
            yytext = current;
            yyleng = 1;
            switch( *current ){
            case ';':
                return SEMI;
            case '~':
                return EOI;
            case '+':
                return PLUS;
            case '-':
                return MINUS;
            case '*':
                return TIMES;
            case '/':
                return DIV;
            case '>':
                return GT;
            case '<':
                return LT;
            case '=':
                return EQU;
            case '(':
                return LP;
            case ')':
                return RP;
            case ':':
                return COL;
            case '\n':
            case '\t':
            case ' ' :
                break;
            default:
                if(!isalnum(*current)){
                    char arr[20];
                    int i=0;
                    while(i<2){
                        arr[i] = *current;
                        ++current;
                        i++;
                    }
                    arr[i] = '\0';
                    if(strcmp(arr, ":=") == 0){
                        yyleng = 2;
                        return ASS;
                    }
                    // fprintf(stderr, "Syntax error\n", *current);
                }
                else{
                    char arr[20];
                    int i=0;
                    while(isalnum(*current)){
                        arr[i] = *current;
                        ++current;
                        i++;
                    }
                    arr[i] = '\0';
                    // printf("%s\n", arr);
                    if(strcmp(arr, "if") == 0){
                        yyleng = 2;
                        return IF;
                    }
                    if(strcmp(arr, "then") == 0){
                        yyleng = 4;
                        return THEN;
                    }
                    if(strcmp(arr, "else") == 0){
                        yyleng = 4;
                        return ELSE;
                    }
                    if(strcmp(arr, "while") == 0){
                        yyleng = 5;
                        return WHILE;
                    }  
                    if(strcmp(arr, "do") == 0){
                        yyleng = 2;
                        return DO;
                    }
                    if(strcmp(arr, "begin") == 0){
                        yyleng = 5;
                        return BEG;
                    }
                    if(strcmp(arr, "end") == 0){
                        yyleng = 3;
                        return END;
                    }
                    // printf("cfghjkh");
                    yyleng = current - yytext;
                    return NUM_OR_ID;
                }
                break;
            }
        }
    }
}

static int Lookahead = -1; /* Lookahead token  */

int match(int token){
    // 
    // printf("%d", lex());
    /* Return true if "token" matches the current lookahead symbol. */
    if(Lookahead == -1) 
        Lookahead = lex();
        // printf("%d", Lookahead);
    return token == Lookahead;
}

void advance(void){
/* Advance the lookahead to the next input symbol. */
    Lookahead = lex();
    // printf("%d", Lookahead);
}
