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
void log_errno(const char *prefix, int value);

#endif /* UTILS_H */
