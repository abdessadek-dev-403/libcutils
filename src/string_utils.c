#include <stdio.h>
#include <string_utils.h>
#include <string.h>

/**
 * Scans multiple lines from stdin until a two-character termination sequence is encountered.
 * 
 * @param buffer Pointer to store the scanned text.
 * @param terminator Two-character termination sequence to stop input_buffer (e.g., ":w")
 * @param max_len Maximum length of the buffer.
 * @return The number of characters stored in buffer.
 */
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
