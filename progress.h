#include <string.h>
#include <stdio.h>

/// current: Current progress value
/// max:     Maximum progress value
/// formatL  Format string
/// left:    Character to use as the left progress delimiter
/// fill:    Character to use to represent completed progress
/// head:    Character to use at the most advanced progress position
/// empty:   Character to use to represent progress left to complete
/// right:   Character to use as the right delimiter
/// length:  Length of the progress bar

/// Prints a progress bar without delimiters
void _progress_progress_print(unsigned long int current, unsigned long int max, char fill, char head, char empty, unsigned char length) {
    unsigned char fill_length = current / (max / length);
    if (fill_length > length) {
        fill_length = length;
    }
    unsigned char empty_length = length - fill_length;

    if (fill_length) {
        fill_length--;

        for (unsigned char i = 0; i < fill_length; i++) {
            printf("%c", fill);
        }
        printf("%c", head);
    }
    for (unsigned char i = 0; i < empty_length; i++) {
        printf("%c", empty);
    }
}

/// Prints a progress bar with delimiters
void _progress_progress_print_d(unsigned long int current, unsigned long int max, char left, char fill, char head, char empty, char right, unsigned char length) {
    printf("%c", left);
    _progress_progress_print(current, max, fill, head, empty, length);
    printf("%c", right);
}

/// Prints a percentage
void _progress_percentage_print(unsigned long int current, unsigned long int max) {
    unsigned char percentage = current / (max / 100);
    printf("%3hhu%%", percentage);
}


void _progress_print(unsigned long int current, unsigned long int max, unsigned char r) {
    if (!r) {
        printf("\r");
    }
    _progress_progress_print_d(current, max, '[', '#', '#', ' ', ']', 20);
    printf(" ");
    _progress_percentage_print(current, max);
    if (r) {
        printf("\r");
    }

    fflush(stdout);
}

void progress_print(unsigned long int current, unsigned long int max) {
    _progress_print(current, max, 0);
}

void progress_rprint(unsigned long int current, unsigned long int max) {
    _progress_print(current, max, 1);
}


int _progress_printf(unsigned long int current, unsigned long int max, char format[12], unsigned char r) {
    unsigned char format_length = strlen(format);

    if (format_length != 9 && format_length != 11) {
        return 1;
    }

    char fill, head, empty;
    unsigned char length, show_percentage;

    if (!r) {
        printf("\r");
    }

    if (format_length == 9) {
        int filled = sscanf(format, "%c%c%c %3hhu %1hhu", &fill, &head, &empty, &length, &show_percentage);
        if (filled != 5) {
            return 1;
        }

        _progress_progress_print(current, max, fill, head, empty, length);
    } else {
        char left, right;

        int filled = sscanf(format, "%c%c%c%c%c %3hhu %1hhu", &left, &fill, &head, &empty, &right, &length, &show_percentage);
        if (filled != 7) {
            return 1;
        }

        _progress_progress_print_d(current, max, left, fill, head, empty, right, length);
    }

    if (show_percentage) {
        printf(" ");
        _progress_percentage_print(current, max);
    }

    if (r) {
        printf("\r");
    }

    fflush(stdout);
}

int progress_printf(unsigned long int current, unsigned long int max, char format[12]) {
    _progress_printf(current, max, format, 0);
}

int progress_rprintf(unsigned long int current, unsigned long int max, char format[12]) {
    _progress_printf(current, max, format, 1);
}
