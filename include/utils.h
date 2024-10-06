#ifndef UTILS_H
#define UTILS_H

// elog dependencies
#define MAX_ERRNO_MESSAGE_LEN 40
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

#endif /* UTILS_H */
