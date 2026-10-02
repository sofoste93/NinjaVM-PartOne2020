#ifndef NJVM_H
#define NJVM_H

#include <stdbool.h>

#define NJVM_RELEASE_VERSION "4.1.0"

/* Load and execute one NJBF version 4 file. Returns zero on success. */
int njvm_run_file(const char *path, bool debug_mode);

#endif
