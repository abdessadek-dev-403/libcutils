#ifndef STRING_UTILS_H
#define STRING_UTILS_H

/**
 * Scans multiple lines from stdin until a two-character termination sequence is encountered.
 * 
 * @param buffer Pointer to store the scanned text.
 * @param terminator Two-character termination sequence to stop input_buffer (e.g., ":w")
 * @param max_len Maximum length of the buffer.
 * @return The number of characters stored in buffer.
 */
int scan_until_terminator(char *buffer, char *terminator, int max_len);

#define NUMBER_OF_ALPHABET_LETTERS 27
enum Case{
    LOWER,
    UPPER
};
/**
 * Converts a given string to uppercase.
 * 
 * This function allocates memory for a new string, converts each character
 * in the input string to its uppercase equivalent, and returns the newly
 * allocated string. The caller is responsible for freeing the allocated memory.
 * 
 * @param str The input string to convert. It must be a null-terminated string.
 * 
 * @return A pointer to a newly allocated string containing the uppercase version
 *         of the input string. If memory allocation fails, returns NULL.
 */
char *to_upper(const char *str);

/**
 * Converts a given string to lowercase.
 * 
 * This function allocates memory for a new string, converts each character
 * in the input string to its lowercase equivalent, and returns the newly
 * allocated string. The caller is responsible for freeing the allocated memory.
 * 
 * @param str The input string to convert. It must be a null-terminated string.
 * 
 * @return A pointer to a newly allocated string containing the lowercase version
 *         of the input string. If memory allocation fails, returns NULL.
 */
char *to_lower(const char *str);

/**
 * Enum representing the direction for searching within the string.
 * START_TO_END: (start to end)
 * END_TO_START: (end to start)
 */
enum Direction {
    START_TO_END,
    END_TO_START
};


/**
 * Finds the index of the first occurrence of a character in a string, searching
 * either from left to right or from right to left, based on the provided direction.
 * 
 * @param str The input string to search. It must be a null-terminated string.
 * @param c The character to search for.
 * @param direction The direction to search in (START_TO_END for start to end, END_TO_START for end to start).
 * 
 * @return The index of the first occurrence of the character in the specified direction,
 *         or -1 if the character is not found.
 */
int index_of(const char *str, char c, enum Direction direction);

enum Color {
    BLACK = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE
};

/**
 * Wraps the input string with ANSI escape codes to apply terminal color formatting.
 * The caller must free the returned string.
 * 
 * @param piece The input string to colorize. It must be a null-terminated string.
 * @param color The color code to apply, as per the Color enum.
 * 
 * @return A newly allocated string with ANSI escape codes for color formatting,
 *         or NULL if memory allocation fails. The caller is responsible for freeing
 *         the returned string.
 */
char *coloring(char *piece, enum Color color);
#endif /* STRING_UTILS_H */