#ifndef PRINTPROMPT_H
#define PRINTPROMPT_H
#define _POSIX_C_SOURCE 200809L

#define COLOR_USER_HOST  "\001\033[01;32m\002"  // Verde
#define COLOR_PATH  "\001\033[01;34m\002"  // Azul
#define COLOR_RESET "\001\033[0m\002" 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>
#include <limits.h>
#include <pwd.h>
#include <string.h>

const char* typePrompt();


#endif
