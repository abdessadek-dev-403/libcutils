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

size_t count_envs() {
    char env_line[ENV_MAX_LEN];
    FILE *dotenv = fopen(DOTENV_PATH, "r");
    if (dotenv == NULL) 
        return (size_t)-1;  // return an invalid size value if fopen fails

    size_t count = 0;
    while (fgets(env_line, ENV_MAX_LEN, dotenv)) 
        count++;
    
    fclose(dotenv);
    return count;
}

int load_env(Dotenv **envs, size_t *size_envs) {
    char env_line[ENV_MAX_LEN];
    FILE *dotenv = fopen(DOTENV_PATH, "r");
    if (dotenv == NULL) 
        return -1;
    
    size_t index = 0;
    while (index < *size_envs && fgets(env_line, ENV_MAX_LEN, dotenv)) {
        env_line[strcspn(env_line, "\n")] = '\0';  // remove newline character

        char *equal_sign = strchr(env_line, '=');
        if (equal_sign != NULL) {
            *equal_sign = '\0';  // split key and value
            char *key = env_line;
            char *value = equal_sign + 1;

            // Ensure memory boundaries are respected
            strncpy((*envs)[index].key, key, MAX_KEY_LEN - 1);
            (*envs)[index].key[MAX_KEY_LEN - 1] = '\0';  // null-terminate
            
            strncpy((*envs)[index].value, value, MAX_VALUE_LEN - 1);
            (*envs)[index].value[MAX_VALUE_LEN - 1] = '\0';  // null-terminate
            index++;
        }
    }
    fclose(dotenv);
    return 0;
}

int dotenv_set(const char *key, unsigned char *value) {
    size_t size_envs = count_envs();
    if (size_envs == (size_t)-1)
        return -1;  // Failed to open the .env file or no env variables found

    Dotenv *envs = malloc(size_envs * sizeof(Dotenv));
    if (envs == NULL)
        return -1;  // Memory allocation failed

    load_env(&envs, &size_envs);

    int key_found = 0;
    for (size_t i = 0; i < size_envs; i++) {
        if (strcmp(envs[i].key, key) == 0) {
            strncpy(envs[i].value, (char*)value, MAX_VALUE_LEN - 1);
            envs[i].value[MAX_VALUE_LEN - 1] = '\0';  // Ensure null-termination
            key_found = 1;
            break;
        }
    }

    if (!key_found) {
        // Handle the case when the key is not found, either return an error or add it to envs
        Dotenv *temp = realloc(envs, (size_envs + 1) * sizeof(Dotenv));
        if (temp ==NULL) {
            free(envs);
            return -1;
        }
        envs = temp;
        strncpy(envs[size_envs].key, key, MAX_KEY_LEN - 1);
        envs[size_envs].key[MAX_KEY_LEN - 1] = '\0';
        strncpy(envs[size_envs].value, (char*)value, MAX_VALUE_LEN - 1);
        envs[size_envs].value[MAX_VALUE_LEN - 1] = '\0';
        size_envs++;
    }

    FILE *dotenv = fopen(DOTENV_PATH, "w");
    if (dotenv == NULL) {
        free(envs);
        return -1;
    }

    for (size_t i = 0; i < size_envs; i++) {
        if (fprintf(dotenv, "%s=%s\n", envs[i].key, envs[i].value) < 0) {
            fclose(dotenv);
            free(envs);
            return -1;  // Error writing to file
        }
    }
    
    fclose(dotenv);
    free(envs);
    return SUCCESS;
}
