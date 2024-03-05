#include <stdio.h>
#include <fcntl.h>

int main() {
    
    volatile int fd = open("/dev/null", O_WRONLY);

    return 0;
}