#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex.c"
#include "name.c"
#include "code_gen.h"
#include "symtab.c"
#include "labelstack.c"

int label = 0;

char *mapper(char *tempvar) {
    int index = 7 - (tempvar[1] - '0');
    return Registers[index];
}

void statements(){
    /*  statements -> statement statements | statement  */
    inter = fopen("main.ic", "w");
    assembly = fopen("main.asm", "w");
    fprintf(assembly, "ORG 100H\n");

    while(!match(EOI)){
        statement();
    }
    fclose(inter); 
    map *temp = head;
    fprintf(assembly, "RET\n");
    while(temp != NULL){
        fprintf(assembly, "%s DB ?\n", temp->var);
        temp = temp->next;
    }
    fprintf(assembly, "END\n");
    fclose(assembly); 
}

void statement(){
    char *tempvar;
    char var[100];
    int i=0;
    while(i<yyleng){
        var[i] = *(yytext+i);
        i++;
    }
    var[i] = '\0';
    if(match(ID)){
        advance();
        if(match(ASS)){
            advance();
            tempvar = expr1(0);
            if(!match(SEMI)){
                fprintf(stderr, "%d: ';' expected\n", yylineno);
            }
            else{
                char var2[100];
                sprintf(var2, "_%s", var);
                insert(var2);

                fprintf(inter, "    %s <- %s\n", var2, tempvar);
                fprintf(assembly, "MOV %s, %s\n", var2, mapper(tempvar));
                advance();
            }
            freename(tempvar);
        }      
    }
    else if(match(WHILE)){
        advance();
        label++;
        push(label);
        fprintf(assembly, "WHILELABEL%d: \n", top->data);
        tempvar = expr1(1);                            
        if(match(DO)){
            advance();          
            fprintf(inter, "while (%s) do { \n", tempvar);
            statement();
            fprintf(inter, "\n}");
            fprintf(assembly, "JMP WHILELABEL%d\n", top->data);
            fprintf(assembly, "LABEL%d: \n", top->data);
            pop();     
        }
        freename(tempvar);
    }
    else if(match(IF)){
        advance();
        label++;
        push(label);
        tempvar = expr1(1);
        if(match(THEN)){
            advance();
            fprintf(inter, "if (%s) then { \n", tempvar);
            statement();
            fprintf(inter, "\n}"); 
            fprintf(assembly, "LABEL%d: \n", top->data);
            pop();  
        }
        freename(tempvar);
    }
    else if(match(BEG)){
        advance();
        fprintf(inter, "begin { \n");
        while (!match(END)){
            statement();
        }
        fprintf(inter, "\n} end \n");
        advance();           
    }
    else {
        fprintf(stderr, "%d: Syntax error\n", yylineno);
        terminate();
    }
}

char *expr1(int flag){
    char *tempvar, *tempvar1, *tempvar2;
    tempvar = expression();
    // advance();
    if(match(EQU) && flag > 0){
        advance();
        tempvar2 = newname();
        tempvar1 = expression();
        fprintf(inter, "    %s <- %s = %s\n", tempvar2, tempvar, tempvar1);
        fprintf(assembly, "CMP %s, %s\n", mapper(tempvar), mapper(tempvar1));
        fprintf(assembly, "JNE LABEL%d\n", top->data);
        freename(tempvar);
        freename(tempvar1);
        return tempvar2;
    }
    else if(match(LT) && flag > 0){
        advance();
        tempvar2 = newname();
        tempvar1 = expression();
        fprintf(inter, "    %s <- %s < %s\n", tempvar2, tempvar, tempvar1);
        fprintf(assembly, "CMP %s, %s\n", mapper(tempvar), mapper(tempvar1));
        fprintf(assembly, "JGE LABEL%d\n", top->data);
        freename(tempvar);
        freename(tempvar1);
        return tempvar2;
    }
    else if(match(GT) && flag > 0){
        advance();
        tempvar2 = newname();
        tempvar1 = expression();
        fprintf(inter, "    %s <- %s > %s\n", tempvar2, tempvar, tempvar1);
        fprintf(assembly, "CMP %s, %s\n", mapper(tempvar), mapper(tempvar1));
        fprintf(assembly, "JLE LABEL%d\n", top->data);
        freename(tempvar);
        freename(tempvar1);
        return tempvar2;
    }
    if (flag > 0) {
        fprintf(assembly, "CMP %s, 0\n", mapper(tempvar));
        fprintf(assembly, "JLE LABEL%d\n", top->data);
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
            fprintf(inter, "    %s += %s\n", tempvar, tempvar1);
            fprintf(assembly, "ADD %s, %s\n", mapper(tempvar), mapper(tempvar1));
            freename(tempvar1);
        }
        else if(match(MINUS)){
            advance();
            tempvar1 = term();
            fprintf(inter, "    %s -= %s\n", tempvar, tempvar1);
            fprintf(assembly, "SUB %s, %s\n", mapper(tempvar), mapper(tempvar1));
            freename(tempvar1);
        }
        else break;
    }
    return tempvar;
}
char *term() {
    char  *tempvar, *tempvar1 ;
    tempvar = factor();

    int flag = 0;
    if (match(TIMES) || match(DIV)) {
        flag = 1;
    }

    if (flag > 0 && strcmp(mapper(tempvar),"AL") != 0) {
        fprintf(assembly, "XCHG AL, %s\n", mapper(tempvar));
    }
    while(1){
        if(match(TIMES)){ 
            advance();
            tempvar1 = term();
            fprintf(inter, "    %s *= %s\n", tempvar, tempvar1);
            fprintf(assembly, "MOV AH, 0\n");
            fprintf(assembly, "MUL %s\n", mapper(tempvar1));
            freename(tempvar1);
        }
        else if(match(DIV)){
            advance();
            tempvar1 = term();
            fprintf(inter, "    %s /= %s\n", tempvar, tempvar1);
            fprintf(assembly, "MOV AH, 0\n");
            fprintf(assembly, "DIV %s\n", mapper(tempvar1));
            freename(tempvar1);
        }
        else break;
    }
    if (flag > 0 && strcmp(mapper(tempvar),"AL") != 0) {
        fprintf(assembly, "XCHG AL, %s\n", mapper(tempvar));
    }
    return tempvar;
}

char *factor(){
    char *tempvar;

    if(match(NUM) || match(ID)){
	/* Print the assignment instruction. The %0.*s conversion is a form of
	 * %X.Ys, where X is the field width and Y is the maximum number of
	 * characters that will be printed (even if the string is longer). I'm
	 * using the %0.*s to print the string because it's not \0 terminated.
	 * The field has a default width of 0, but it will grow the size needed
	 * to print the string. The ".*" tells printf() to take the maximum-
	 * number-of-characters count from the next argument (yyleng).
	 */
        char var[100];
        int i=0;
        var[0] = '_';
        while(i<yyleng){
            var[i+1] = *(yytext+i);
            i++;
        }
        var[i+1] = '\0';
        map *temp = search(var);
        if (match(ID) && temp == NULL) {
            fprintf(stderr, "%d: Undeclared identifier\n", yylineno);            
        }

        if (match(ID)) {
            fprintf(inter, "    %s = %s\n", tempvar = newname(), var);
            fprintf(assembly, "MOV %s, %s\n", mapper(tempvar), var);
        }
        else if (match(NUM)) {
            fprintf(inter, "    %s = %s\n", tempvar = newname(), (var+1));
            fprintf(assembly, "MOV %s, %s\n", mapper(tempvar), (var+1));
        }
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

