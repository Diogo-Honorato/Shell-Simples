#ifndef PRINTPROMPT_H
#define PRINTPROMPT_H
#define _POSIX_C_SOURCE 200809L

#define COLOR_USER_HOST  "\033[1;32m"  // Verde
#define COLOR_PATH  "\033[1;34m"  // Azul
#define COLOR_RESET "\033[0m" 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <limits.h>
#include <pwd.h>
#include <string.h>

const char* typePrompt();

#endif
