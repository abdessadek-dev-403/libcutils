#ifndef UTILS_H
#define UTILS_H

// elog dependencies
#define MAX_ERRNO_MESSAGE_LEN 40
#define DOTENV_PATH ".env"
#define ENV_MAX_LEN 1024
#define SUCCESS 0

enum ErrnoValue {
    OPERATION_NOT_PERMITTED = 1,
    NO_SUCH_FILE_OR_DIRECTORY,
    NO_SUCH_PROCESS,
    INTERRUPTED_SYSTEM_CALL,
    IO_ERROR,
    NO_SUCH_DEVICE_OR_ADDRESS,
    THE_ARGUMENT_LIST_IS_TOO_LONG,
    EXEC_FORMAT_ERROR,
    BAD_FILE_NUMBER,
    NO_CHILD_PROCESSES,
    TRY_AGAIN,
    OUT_OF_MEMORY,
    PERMISSION_DENIED,
};
typedef struct Errno {
    int value;
    char message[MAX_ERRNO_MESSAGE_LEN];
} Errno;

/**
 * Logs the error message corresponding to a given errno value.
 * 
 * This function takes an error code (errno value) and logs the corresponding 
 * error message with an optional prefix. If the prefix is `NULL`, it defaults 
 * to "Error". If the provided errno value does not correspond to a known error 
 * code, the function logs an unknown error message.
 * 
 * @param prefix A pointer to a string used as a prefix in the logged message. 
 *               If `NULL`, it defaults to "Error".
 * @param value The errno code, representing the type of error.
 * 
 * Example:
 * 
 * ```
 * log_errno(NULL, 2);   // Outputs: "Error: No such file or directory"
 * log_errno("Warning", 12);  // Outputs: "Warning: Out of memory"
 * ```
 */
void log_errno(const char *prefix, int value);

/**
 * Retrieves the value of an environment variable from a .env file.
 * 
 * The .env file is expected to have lines in the format NAME=VALUE.
 * The function searches for the provided NAME and returns its corresponding
 * value as a dynamically allocated string. The caller is responsible for freeing
 * the returned string.
 * 
 * @param name The name of the environment variable to search for.
 * 
 * @return A pointer to a dynamically allocated string containing the value,
 *         or NULL if the variable is not found or an error occurs.
 */
char *dotenv_get(const char *name);

/**
 * Checks if the .env file exists.
 * 
 * @return 0 (SUCCESS) if the file exists, or an appropriate errno value if an error occurs.
 */
int check_dotenv_existance();

#endif /* UTILS_H */
