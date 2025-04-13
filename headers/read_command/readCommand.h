#ifndef READCOMMAND_H
#define READCOMMAND_H

#define CLOSE_SHELL (stringLine == NULL || strcmp(stringLine, "exit") == 0)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>


char* readCommand(const char* prompt);
void initReadCommand();
void signalHandler(int signal);

#endif