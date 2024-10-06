#include <stdio.h>
#include <utils.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

int check_dotenv_existance() {
    errno = 0;
    FILE *dotenv = fopen(DOTENV_PATH, "r");
    if (dotenv == NULL)
        return errno;
    fclose(dotenv);
    return SUCCESS;
}

char *dotenv_get(const char *name) {
    char env_line[ENV_MAX_LEN];
    FILE *dotenv = fopen(DOTENV_PATH, "r");
    if (dotenv == NULL) 
        return NULL;

    while (fgets(env_line, ENV_MAX_LEN, dotenv)) {
        // Remove trailing newline if present
        env_line[strcspn(env_line, "\n")] = '\0';

        // Find the first '=' in the line
        char *equal_sign = strchr(env_line, '=');
        if (equal_sign != NULL) {
            // Split the line into key and value
            *equal_sign = '\0';
            char *key = env_line;
            char *value = equal_sign + 1;

            // If the key matches the requested name, return the value
            if (strcmp(key, name) == 0) {
                fclose(dotenv);

                // Allocate memory for the value and return it
                char *result = malloc(strlen(value) + 1);
                if (result != NULL) {
                    strcpy(result, value);
                }
                return result;
            }
        }
    }
    fclose(dotenv);
    return NULL;
}