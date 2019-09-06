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

void progress(char format[10], unsigned int delay) {
    for (unsigned int i = 0; i < 100; i++) {
        pg_print(format, i, 100);
        cross_sleep(delay);
    }
    pg_finish(format);
}

int main() {
    progress("", 10);
    progress(":", 10);
    progress("+-", 10);
    progress("(Xx)", 10);
    progress("{Yy} 33", 10);
    progress("<Zz> 10 0", 10);
    
    return 0;
}