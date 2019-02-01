#include <stdio.h>
#include <string.h>


void int2mem(int mem, char ans[]) {
    sprintf(ans, "%XH", mem);
}

int main() {
    char ans[100];
    int2mem(1728,ans);
    printf("%s", ans);
    return 0;
}