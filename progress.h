// https://github.com/raftario/progress.h

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

// Prints a progress bar without delimiters
void _progress_progress_print(unsigned long int current, unsigned long int max, char fill, char head, char empty, unsigned char length) {
    unsigned char fill_length = current / (max / length);
    if (fill_length > length) {
        fill_length = length;
    }
    unsigned char empty_length = length - fill_length;

    if (fill_length) {
        fill_length--;

        for (unsigned char i = 0; i < fill_length; i++) {
            fprintf(stderr, "%c", fill);
        }
        fprintf(stderr, "%c", head);
    }
    for (unsigned char i = 0; i < empty_length; i++) {
        fprintf(stderr, "%c", empty);
    }
}

// Prints a progress bar with delimiters
void _progress_progress_print_d(unsigned long int current, unsigned long int max, char left, char fill, char head, char empty, char right, unsigned char length) {
    fprintf(stderr, "%c", left);
    _progress_progress_print(current, max, fill, head, empty, length);
    fprintf(stderr, "%c", right);
}

// Prints a percentage
void _progress_percentage_print(unsigned long int current, unsigned long int max) {
    unsigned char percentage = current / (max / 100);
    fprintf(stderr, "%3hhu%%", percentage);
}


void _progress_print(unsigned long int current, unsigned long int max, unsigned char r) {
    if (!r) {
        fprintf(stderr, "\r");
    }
    _progress_progress_print_d(current, max, '[', '#', '#', ' ', ']', 20);
    fprintf(stderr, " ");
    _progress_percentage_print(current, max);
    if (r) {
        fprintf(stderr, "\r");
    }

    fflush(stderr);
}

void progress_print(unsigned long int current, unsigned long int max) {
    _progress_print(current, max, 0);
}

void progress_rprint(unsigned long int current, unsigned long int max) {
    _progress_print(current, max, 1);
}


int _progress_printf(unsigned long int current, unsigned long int max, char format[6], unsigned char length, unsigned char show_percentage, unsigned char r) {
    unsigned char format_length = strlen(format);

    if (format_length != 3 && format_length != 5) {
        return 1;
    }

    char fill, head, empty;

    if (!r) {
        fprintf(stderr, "\r");
    }

    if (format_length == 3) {
        fill = format[0];
        head = format[1];
        empty = format[2];
        _progress_progress_print(current, max, fill, head, empty, length);
    } else {
        char left = format[0], right = format[4];

        fill = format[1];
        head = format[2];
        empty = format[3];

        _progress_progress_print_d(current, max, left, fill, head, empty, right, length);
    }

    if (show_percentage) {
        fprintf(stderr, " ");
        _progress_percentage_print(current, max);
    }

    if (r) {
        fprintf(stderr, "\r");
    }

    fflush(stderr);
}

int progress_printf(unsigned long int current, unsigned long int max, char format[6], unsigned char length, unsigned char show_percentage) {
    _progress_printf(current, max, format, length, show_percentage, 0);
}

int progress_rprintf(unsigned long int current, unsigned long int max, char format[6], unsigned char length, unsigned char show_percentage) {
    _progress_printf(current, max, format, length, show_percentage, 1);
}
