bison bison.y -d
lex part2.l
g++ bison.tab.c lex.yy.c -o test -w
./test tests/1.txt > output.txt