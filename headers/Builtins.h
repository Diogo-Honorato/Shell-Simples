#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdlib.h>
#include <stdio.h>
#include "Trie.h"
#define CLOSE_SHELL -1 //Constante que indica o encerramento do processo

int shellExit(char** argv);
int shellCd(char** argv);
int shellHelp(char** argv);
int addBuiltin(Node *root, const char **NAME_BUILTINS,FunctionType **nameFunctions, const size_t NUM_BUILTINS);
Node *startBufferBuiltins();

#endif