#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE_CHAR 26

//tipo de dado int(char**) que será usado para receber o endereço das funções do 
//mesmo retorno 'int' e parametro (char**)
typedef int FunctionType(char**);

typedef struct Node
{
    struct Node *children[SIZE_CHAR];
    
    FunctionType *functionPointer; // Ponteiro que armazena o endereço das funções

    const char *DESCRIPTION;

    bool endword;
    
} Node;

//Node *root; deveria ser global?

Node *CreateNode();

bool EmptyTrie(Node *root);

int InsertTrie(Node *root, char *word, FunctionType *function, const char *DESCRIPTION);

FunctionType* Search(Node *root, char *word);

int AddBultin(Node *root, char *nameBuiltin,FunctionType *nameFunction, const char *DESCRIPTION);

int PrintTrie(Node *root, char *str, int index);

bool EmptyNode(Node *root);

Node *removed(Node *root, char *word, int init);

int RemovedTrie(Node *root, char *word);

void FreeTrie(Node *root);

#endif