#include <stdio.h>
#include <stdlib.h>
#include <string_utils.h>
#include <string.h>
#include <ctype.h>

int scan_until_terminator(char *buffer, char *terminator, int max_len) {
    int index = 0;
    char input_buffer[4] = {0};
    while (index < max_len - 1) {
        char c = getchar();

        if (c == EOF) { // Handle end of file
            printf("Error: Unexpected end of input.\n");
            buffer[index] = '\0';
            return index;
        }

        input_buffer[0] = input_buffer[1];
        input_buffer[1] = input_buffer[2];
        input_buffer[2] = c;

        if (input_buffer[0] == '\n' && input_buffer[1] == terminator[0] && input_buffer[2] == terminator[1])
            break;


        buffer[index++] = (char)c;
    }

    buffer[index-1] = '\0'; // Null-termination
    return index; // return the number of characters stored in buffer.

}


int index_of(const char *str,char c, enum Direction direction)  {
    if (str == NULL) {
        return -1; // Handle NULL string safely
    }

    int str_len = strlen(str);
    
    if (direction == START_TO_END) {
        for (int i = 0; i < str_len; i++) {
            if (str[i] == c) {
                return i;
            }
        }
    } else if (direction == END_TO_START) {
        for (int i = str_len - 1; i >= 0; i--) {
            if (str[i] == c) {
                return i;
            }
        }
    }
    
    return -1; // Character not found
}


char *to_upper(const char *str) {
    int max_len = strlen(str);
    char *upper_str = malloc(max_len + 1);
    if (upper_str == NULL)
        return NULL;

    for (int str_index = 0; str_index < max_len; str_index++)
        upper_str[str_index] = (char)toupper(str[str_index]);
    upper_str[max_len] = '\0';

    return upper_str;
}

char *to_lower(const char *str) {
    int max_len = strlen(str);
    char *lower_str = malloc(max_len + 1);
    if (lower_str == NULL)
        return NULL;

    for (int str_index = 0; str_index < max_len; str_index++)
        lower_str[str_index] = (char)tolower(str[str_index]);
    lower_str[max_len] = '\0';

    return lower_str;
}

char *coloring(char *piece, enum Color color) {
    if (piece == NULL)
        return NULL;

    // Calculate the length of the resulting formatted string including the null terminator.
    int colored_piece_len = snprintf(NULL, 0, "\033[0;%dm%s\033[0m", color, piece) + 1;
    
    // Allocate memory for the formatted string.
    char *colored_piece = malloc(colored_piece_len);
    if (colored_piece == NULL)
        return NULL;
    
    // Generate the formatted colored string.
    snprintf(colored_piece, colored_piece_len, "\033[0;%dm%s\033[0m", color, piece);
    
    return colored_piece;
}