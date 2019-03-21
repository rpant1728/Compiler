bison bison.y -d
lex lex.l
g++ bison.tab.c lex.yy.c -o test -w
./test tests/1.txt > output.txt
