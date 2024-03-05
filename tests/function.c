#include <stdio.h>

#pragma optimize("", off)
int foo(){
    printf("foo\n");
}

int main() {
    foo();
    return 0;
}