#include<stdio.h>
#include<stdlib.h>

void foo(){
    static int x=10;
    x+=10;
}

int main() {
    printf("joe\n");
    foo();
    foo();
    printf("nice");
    return 0;
}
