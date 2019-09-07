#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "progress.h"

// Sleep for n milliseconds, OS independant
void cross_sleep(unsigned int delay) {
    #ifdef _WIN32
    Sleep(delay);
    #else
    usleep(delay * 1000);
    #endif
}

void p() {
    // Print progress from 0 to 100%
    for (unsigned int i = 0; i <= 100; i++) {
        // Use default progress bar
        progress_print(i, 100);
        // Sleep for an amount of time from 0 to 100ms between each iteration
        cross_sleep(rand() % 100);
    }
}

void pf(char format[12], unsigned char length, unsigned char show_percentage) {
    // Print progress from 0 to 100%
    for (unsigned int i = 0; i <= 100; i++) {
        // Use customized progress bar
        progress_printf(i, 100, format, length, show_percentage);
        // Sleep for an amount of time from 0 to 100ms between each iteration
        cross_sleep(rand() % 100);
    }
}

int main() {
    // Initialize random number generation
    time_t t;
    srand((unsigned) time(&t));

    // Default progress bar
    p();
    fprintf(stderr, "\n");
    // No delimiters, no percentage, custom characters and length
    pf(":;-", 29, 0);
    fprintf(stderr, "\n");
    // Delimiters, percentage, custom characters and length
    pf("(=> )", 24, 1);
    fprintf(stderr, "\n");
    
    return 0;
}