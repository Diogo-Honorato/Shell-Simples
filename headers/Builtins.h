#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdlib.h>
#include <stdio.h>
#include "Trie.h"
#define NUM_BUILTINS sizeof(BUFFER_BUILTINS)/sizeof(char*)//Total de Builtins
#define CLOSE_SHELL -1 //Constante que indica o encerramento do processo

int shellExit(char** argv);
int shellCd(char** argv);
int shellHelp(char** argv);
int addBuiltin(Node *root, const char **nameBuiltin,FunctionType **nameFunction);
Node *startBuffer();//Nome a decidir por equanto vai ser esse :).


#endif