#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "progress.h"

void cross_sleep(unsigned int delay) {
    #ifdef _WIN32
    Sleep(delay);
    #else
    usleep(delay * 1000);
    #endif
}

void p(unsigned int delay) {
    for (unsigned int i = 1; i <= 100; i++) {
        progress_print(i, 100);
        cross_sleep(delay);
    }
}

void pf(unsigned int delay, char format[12]) {
    for (unsigned int i = 0; i <= 100; i++) {
        progress_printf(i, 100, format);
        cross_sleep(delay);
    }
}

int main() {
    p(10);
    printf("\n");
    pf(10, ":|~ 029 0");
    printf("\n");
    pf(10, "(=> ) 024 1");
    printf("\n");
    
    return 0;
}