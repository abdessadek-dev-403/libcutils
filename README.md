# C Utility Function Library (`libcutils`)

`libcutils` is a collection of reusable utility functions written in C. These functions cover various operations such as file handling, string manipulation, mathematical calculations, and more, which can be easily integrated into other C projects.

## Features

- **Error Logging**: Logs system error messages using a customizable prefix.
- **File Utilities**: Provides utilities to handle file operations.
- **String Utilities**: Functions for string manipulation.
- **Math Utilities**: Basic math operations.
- **Time Utilities**: Functions to handle time operations.


## Building the Project

### Prerequisites

- Ensure you have `gcc` installed.

### Building the Static Library

To compile the static library (`libcutils.a`) and the necessary object files, run the `Makefile`:

```bash
make
```

This will compile the `.c` files in the `src/` directory and place the resulting `.o` files in the `bin/` directory. It will also generate the libcutils.a static library.

## Usage

To use libcutils in your own projects, include the header files from the include/ directory and link the static library during compilation.

### Example Usage

1. Include the header file:
```c
#include "path_to_libcutils/include/utils.h"
```

2. Link the static library when compiling:
```bash
gcc -o myprogram myprogram.c -Lpath_to_libcutils/bin -lcutils
```

### Example: Logging an Error
log_errno function:
```c
#include "path_to_libcutils/include/utils.h"

int main() {
    log_errno("Warning", 2);  // Logs: "Warning: No such file or directory"
    return 0;
}
```
Compile this example program with the static library:
```bash
gcc -o myprogram myprogram.c -Lpath_to_libcutils/bin -lcutils
```
