#include "../headers/Trie.h"

Node *CreateNode()
{
    Node *newnode = malloc(sizeof(*newnode));

    for (int i = 0; i < SIZE_CHAR; i++)
    {
        newnode->children[i] = NULL;
    }

    newnode->endword = false;

    newnode->functionPointer = NULL;
    
    newnode->DESCRIPTION = NULL;

    return newnode;
}

bool EmptyTrie(Node *root)
{
    for (int i = 0; i < SIZE_CHAR; i++)
    {
        if (root->children[i] != NULL)
        {
            return false;
        }
    }
    perror("EMPTY TREE !\n");

    return true;
}

int InsertTrie(Node *root, char *word, FunctionType *function, const char *DESCRIPTION)
{
    Node *current = root;
    int index;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        index = word[i] - 'a';

        if (current->children[index] == NULL)
        {
            current->children[index] = CreateNode();
        }

        current = current->children[index];
    }

    current->endword = true;
    current->functionPointer = function;
    current->DESCRIPTION = DESCRIPTION;

    return EXIT_SUCCESS;
}

FunctionType* Search(Node *root, char *word)
{
    Node *current = root;
    int index;
    int len = strlen(word);

    if(EmptyTrie(root)){

        return NULL;
    }

    for (int i = 0; i < len; i++)
    {
        index = word[i] - 'a';

        if (current->children[index] == NULL)
        {
            return NULL;
        }

        current = current->children[index];
    }

    if (current->endword)
    {
        return current->functionPointer;
    }
    else
    {
        return NULL;
    }
}

int AddBultin(Node *root, char *nameBuiltin,FunctionType *nameFunction, const char *DESCRIPTION)
{
    if(EmptyTrie(root)){

        return EXIT_FAILURE;
    }

    if(Search(root,nameBuiltin) == NULL)
    {
        InsertTrie(root,nameBuiltin,nameFunction,DESCRIPTION);
        return EXIT_SUCCESS;
    }
    else
    {
        printf("%s: comando existente\n",nameBuiltin);
        return EXIT_FAILURE;
    }
}

int PrintTrie(Node *root, char *str, int index)
{
    Node *aux = root;

    if (aux->endword)
    {
        str[index] = '\0';
        printf("%s\n", str);
    }

    for (int i = 0; i < SIZE_CHAR; i++)
    {
        if (aux->children[i] != NULL)
        {
            str[index] = i + 'a';
            PrintTrie(aux->children[i], str, index + 1);
        }
    }

    return EXIT_SUCCESS;
}

bool EmptyNode(Node *root)
{
    for (int i = 0; i < SIZE_CHAR; i++)
    {
        if (root->children[i] != NULL)
        {
            return false;
        }
    }

    return true;
}

Node *removed(Node *root, char *word, int init)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (init == (int)strlen(word))
    {
        root->endword = false;

        if (EmptyNode(root))
        {
            free(root);
            root = NULL;
        }
        return root;
    }

    int index = word[init] - 'a';

    root->children[index] = removed(root->children[index], word, init + 1);

    if (EmptyNode(root) && !root->endword)
    {
        free(root);
        root = NULL;
    }

    return root;
}

int RemovedTrie(Node *root, char *word)
{
    if(Search(root,word))
    {
        removed(root,word,0);
        printf("\n\nWord remove: %s\n\n",word);
        return EXIT_SUCCESS;
    }
    else
    {
        printf("\n\nWord NOT found to remove: %s\n\n",word);
        return EXIT_FAILURE;
    }
}

void FreeTrie(Node *root)
{
    if(!root)
    {
        return;
    }
    else
    {
        for(int i = 0; i < SIZE_CHAR; i++)
        {
            FreeTrie(root->children[i]);
        }
    }
    free(root);
}