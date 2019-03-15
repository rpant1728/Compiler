bison bison.y -d
lex part2.l
g++ bison.tab.c lex.yy.c -o test
./test test.txt