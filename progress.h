#include <string.h>
#include <stdio.h>

int pg_parse_format_string(char format[11], char* delimiters, char* fills, unsigned char* length, unsigned char* show_percentage) {
    size_t format_length = strlen(format);
    int filled;
    switch (format_length) {
        // Use defaults
        case 0:
            break;
        // Only the progress fill character was specified
        case 1:
            filled = sscanf(format, "%c", &fills[0]);
            if (filled != 1) {
                return 1;
            }
            break;
        // Both the progress fill and empty characters are specified
        case 2:
            filled = sscanf(format, "%c%c", &fills[0], &fills[1]);
            if (filled != 2) {
                return 1;
            }
            break;
        // Both progress fill and empty characters and delimiter characters are specified
        case 4:
            filled = sscanf(format, "%c%c%c%c", &delimiters[0], &fills[0], &fills[1], &delimiters[1]);
            if (filled != 4) {
                return 1;
            }
            break;
        // All characters are specified, length is also specified
        case 6:
            filled = sscanf(format, "%c%c%c%c %hhu", &delimiters[0], &fills[0], &fills[1], &delimiters[1], length);
            if (filled != 5) {
                return 1;
            }
            break;
        case 7:
            filled = sscanf(format, "%c%c%c%c %hhu", &delimiters[0], &fills[0], &fills[1], &delimiters[1], length);
            if (filled != 5) {
                return 1;
            }
            break;
        case 8:
            filled = sscanf(format, "%c%c%c%c %hhu", &delimiters[0], &fills[0], &fills[1], &delimiters[1], length);
            if (filled != 5) {
                return 1;
            }
            break;
        // All characters, length and percentage use are specified
        case 9:
            filled = sscanf(format, "%c%c%c%c %hhu %hhu", &delimiters[0], &fills[0], &fills[1], &delimiters[1], length, show_percentage);
            if (filled != 6) {
                return 1;
            }
            break;
        case 10:
            filled = sscanf(format, "%c%c%c%c %hhu %hhu", &delimiters[0], &fills[0], &fills[1], &delimiters[1], length, show_percentage);
            if (filled != 6) {
                return 1;
            }
            break;
        default:
            return 1;
    }
}

int pg_print(char format[11], unsigned long int current, unsigned long int max) {
    char delimiters[2] = {'[', ']'}, fills[2] = {'#', ' '};
    unsigned char length = 20;
    unsigned char show_percentage = 1;

    int parse_result = pg_parse_format_string(format, delimiters, fills, &length, &show_percentage);
    if (parse_result == 1) {
        return 1;
    }

    unsigned long int progress_divider = max / length;
    printf("%c", delimiters[0]);
    unsigned char fill_length = current / progress_divider;
    unsigned char empty_length = length - fill_length;
    for (unsigned char i = 0; i < fill_length; i++) {
        printf("%c", fills[0]);
    }
    for (unsigned char i = 0; i < empty_length; i++) {
        printf("%c", fills[1]);
    }
    printf("%c", delimiters[1]);

    if (show_percentage) {
        unsigned long int percentage_divider = max / 100;
        unsigned char percentage = current / percentage_divider;
        printf(" %3hhu%%", percentage);
    }

    printf("\r");
    fflush(stdout);
}

int pg_finish(char format[11]) {
    char delimiters[2] = {'[', ']'}, fills[2] = {'#', ' '};
    unsigned char length = 20;
    unsigned char show_percentage = 1;

    int parse_result = pg_parse_format_string(format, delimiters, fills, &length, &show_percentage);
    if (parse_result == 1) {
        return 1;
    }

    printf("%c", delimiters[0]);
    for (unsigned char i = 0; i < length; i++) {
        printf("%c", fills[0]);
    }
    printf("%c", delimiters[1]);

    if (show_percentage) {
        printf(" 100%%");
    }

    printf("\n");
    fflush(stdout);
}