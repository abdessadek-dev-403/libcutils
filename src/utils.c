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