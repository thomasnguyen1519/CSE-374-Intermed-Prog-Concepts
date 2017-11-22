/*
    Thomas Nguyen
    October 26, 2017
    CSE 374
    Homework 4: gasp

    This program mimics the grep command and extracts lines from a file that
    match a client-provided String.

    Syntax: ./gasp [OPTIONS] STRING FILES...

    Options
        -i | ignores letter casing when matching the input string in
             the provided file
        -n | outputs the line count for each of the matched lines
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define LINE_LENGTH_CAP 500
#define WORD_LENGTH_CAP 100

void find_matches(FILE *file, char *file_name, char *word,
                  int ignore_case, int line_count);
void str_to_low(char *str);

int main(int argc, char  *argv[]) {
    int ignore_case = 0;       // stores if the -i option was toggled
    int line_count = 0;        // stores if the -n option was toggled
    int arg_offset = 1;
    if (argc < 3) {                 // checking minimum number of arguments
        fprintf(stderr, "Usage: %s [OPTIONS] STRING FILES...\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= 2; i++) {  // checking selected options
        if (strcmp(argv[i], "-i") == 0) {
            ignore_case = 1;
            arg_offset++;
        } else if (strcmp(argv[i], "-n") == 0) {
            line_count = 1;
            arg_offset++;
        }
    }
    if (arg_offset == 3 && argc == 3) {
        fprintf(stderr, "%s: need STRING and FILE arguments\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *targ_string = argv[arg_offset++];
    if (ignore_case == 1) {
        str_to_low(targ_string);
    }
    if (strlen(targ_string) >= WORD_LENGTH_CAP) {
        fprintf(stderr,
                "%s: STRING arg has to be 100 characters or less\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (arg_offset < argc) {
        for (int i = arg_offset; i < argc; i++) {
            char *file_name = argv[i];
            FILE *file = fopen(file_name, "r");
            if (file != NULL) {
                find_matches(file, file_name, targ_string, ignore_case,
                             line_count);
                fclose(file);
            } else {
                fprintf(stderr, "%s: %s file not found\n", argv[0], file_name);
            }
        }
        exit(EXIT_SUCCESS);
    } else {
        fprintf(stderr, "%s: need input FILE argument(s)\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

/*
    Scans the provided file for the target string and outputs the
    matching lines.

    Params
        file: the file to be scanned
        ignore_case:
        line_count: whether or not to print the line numbers
        word: the provided string to match
        file_name: the name of the prodived file
*/
void find_matches(FILE *file, char *file_name, char *word,
                  int ignore_case, int line_count) {
    char line[LINE_LENGTH_CAP];
    char cp_line[LINE_LENGTH_CAP];
    int line_counter = 0;
    while (fgets(line, LINE_LENGTH_CAP, file)) {
        line_counter++;
        if (ignore_case == 1) {
            strncpy(cp_line, line, LINE_LENGTH_CAP);
            str_to_low(line);
        }
        if (strstr(line, word)) {
            printf("%s: ", file_name);
            if (line_count == 1) {
                printf("(line %d) ", line_counter);
            }
            printf("%s", (ignore_case == 1) ? cp_line : line);
        }
    }
}

/*
    Converts Strings to lowercase.

    Params
        str: the string to be processed
*/
void str_to_low(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
