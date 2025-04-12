#ifndef READCOMMAND_H
#define READCOMMAND_H

#define CLOSE_SHELL (strcmp(stringLine, "exit") == 0)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


char* readCommand(const char* prompt);


#endif