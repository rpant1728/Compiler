/* Basic parser, shows the structure but there's no code generation */

#include <stdio.h>
#include "lex.c"

void statements(int level);
void statement(int level);
void stmt_list(int level);
void expr1(int level);
void expression(int level);
void expr_prime(int level);
void term(int level);
void term_prime(int level);
void factor(int level);

void print(char *str, int level) {
    for(int i = 0; i < level; i++)
    {
        printf("          ");
    }
    printf("%s\n", str);
}

void statements(int level) {
    // statement statements | statement
    print("statements", level);
    statement(level+1);
    if (!match(EOI))
        statements(level+1);
}
void stmt_list(int level) {
    print("stmt_list", level);
    if (!match(END)) {
        statement(level+1);
        stmt_list(level+1);
    }
}
void statement(int level){
    print("statement", level);
    /*  statements -> expression SEMI
     *             |  expression SEMI statements
     */
    // ID:=expression1;
	// 				|	IF expression1 then statement
	// 				|	while expression1 do statement
	// 				|	begin  stmt_list end
    // expression();
    // if(match(SEMI))
	//     advance();
    // else
    //     fprintf(stderr, "%d: Inserting missing semicolon\n", yylineno);
    // if( !match(EOI) )
    //     statement();			/* Do another statement. */

    if (match(ID)) {
        char var[100];
        int i=0;
        while(i<yyleng){
            var[i] = *(yytext+i);
            i++;
        }
        var[i] = '\0';
        advance();
        if (match(ASS)) {
            advance();
            char var2[100];
            sprintf(var2, "''%s''", var);
            print(var2,level+1);
            print("'':=''", level+1);
            expr1(level+1);
            if (match(SEMI)) {
                advance();
            }
        }
    }
    else if (match(IF)) {
        advance();
        expr1(level+1);
        if (match(THEN)) {
            advance();
            statement(level+1);
        }
    }
    else if (match(WHILE)) {
        advance();
        expr1(level+1);
        if (match(DO)) {
            advance();
            statement(level+1);
        }
    }
    else if (match(BEG)) {
        advance();
        stmt_list(level+1);
        advance();
    }
}

void expr1(int level) {
    print("expr1", level);
    expression(level+1);
    if (match(LT)) {
        advance();
        expression(level+1);
    }
    else if (match(GT)) {
        advance();
        expression(level+1);
    }
    else if (match(EQU)) {
        advance();
        expression(level+1);
    }
}

void expression(int level){
    print("expression", level);
    /* expression -> term expression' */
    term(level+1);
    expr_prime(level+1);
}

void expr_prime(int level){
    print("expr'", level);
    /* expression' -> PLUS term expression'
     *              | epsilon
     */
    if(match(PLUS)){
        advance();
        term(level+1);
        expr_prime(level+1);
    }
    else if(match(MINUS)){
        advance();
        term(level+1);
        expr_prime(level+1);
    }
    else {
        print("''epsilon''", level+1);
    }
}

void term(int level){
    /* term -> factor term' */
    print("term", level);
    factor(level+1);
    term_prime(level+1);
}

void term_prime(int level){
    /* term' -> TIMES factor term'
     *       |   epsilon
     */
    print("term'", level);
    if(match(TIMES)){
        advance();
        factor(level+1);
        term_prime(level+1);
    }
    else if(match(DIV)){
        advance();
        factor(level+1);
        term_prime(level+1);
    }
    else {
        print("''epsilon''", level+1);
    }
}

void factor(int level){
    /* factor   ->    NUM_OR_ID
     *          |     LP expression RP
     */
    print("factor", level);
    if(match(ID) || match(NUM)) {
        char var[100];
        int i=0;
        while(i<yyleng){
            var[i] = *(yytext+i);
            i++;
        }
        var[i] = '\0';
        char var2[100];
        sprintf(var2, "''%s''", var);
        print(var2,level+1);
        advance();
    }

    else if(match(LP)){
        advance();
        expression(level+1);
        if( match(RP) )
            advance();
        else
            fprintf( stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
    else
	    fprintf( stderr, "%d Number or identifier expected\n", yylineno );
}

int main () {
    statements(0);
}