#ifndef CREATEPROCESS_H
#define CREATEPROCESS_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int createProcess(char **argv);

#endif