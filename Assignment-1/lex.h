#define EOI	0	    /* ~ */
#define SEMI 1	    /* ; */
#define PLUS 2	    /* + */
#define MINUS 3	    /* - */
#define TIMES 4	    /* * */
#define DIV 5	    /* / */
#define GT 6	    /* > */
#define LT 7	    /* < */
#define EQU 8	    /* = */
#define LP 9	    /* ( */
#define RP 10	    /* ) */
#define IF 11	    /* if condition */
#define THEN 12	    /* then */
#define ELSE 13	    /* else */
#define WHILE 14	/* while loop */
#define DO 15	    /* do */
#define BEG 16	    /* begin */
#define END 17	    /* end */
#define NUM 18	/* Decimal Number or Identifier */
#define ASS 19      /* assignment operator */
#define ID 20

extern char *yytext;
extern int yyleng;
extern int yylineno;
