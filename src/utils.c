#include <stdio.h>
#include <utils.h>
#include <stdlib.h>
#include <string.h>

/**
 * Helper function for `log_errno` to get the err structure
 * based on value of errno
 * 
 * @param value errno value
 * 
 * @return `Errno*` a pointer structure point on a specific error if it found or `NULL`
 * when encounter an error during allocate memory 
 */
Errno *getErrno(int value) {
    Errno *err = malloc(sizeof(Errno));
    if (!err) return NULL;

    static struct {
        int value;
        const char *message;
    } errno_list[] = {
        { OPERATION_NOT_PERMITTED, "Operation not permitted" },
        { NO_SUCH_FILE_OR_DIRECTORY, "No such file or directory" },
        { NO_SUCH_PROCESS, "No such process" },
        { INTERRUPTED_SYSTEM_CALL, "Interrupted system call" },
        { IO_ERROR, "I/O error" },
        { NO_SUCH_DEVICE_OR_ADDRESS, "No such device or address" },
        { THE_ARGUMENT_LIST_IS_TOO_LONG, "The argument list is too long" },
        { EXEC_FORMAT_ERROR, "Exec format error" },
        { BAD_FILE_NUMBER, "Bad file number" },
        { NO_CHILD_PROCESSES, "No child processes" },
        { TRY_AGAIN, "Try again" },
        { OUT_OF_MEMORY, "Out of memory" },
        { PERMISSION_DENIED, "Permission denied" }
    };

    size_t errno_count = sizeof(errno_list) / sizeof(errno_list[0]);
    for (size_t i = 0; i < errno_count; i++) {
        if (errno_list[i].value == value) {
            err->value = value;
            strncpy(err->message, errno_list[i].message, MAX_ERRNO_MESSAGE_LEN);
            return err;
        }
    }

    free(err);
    return NULL; // Error not found
}

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
void log_errno(const char *prefix, int value) {
    if (prefix == NULL)
        prefix = "Error";

    Errno *err = getErrno(value);
    if (err) {
        printf("%s: %s\n", prefix, err->message);
        free(err);
    } else {
        printf("%s: Unknown error code: %d\n", prefix, value);
    }
}