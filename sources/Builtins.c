#include "../headers/Builtins.h"

//Obs.: A ordem das inserções dos nomes dos builtins tem que ser a mesma que a ordem de inserção de suas funções.
const char* BUFFER_BUILTINS[] = {"exit","cd","help"};

FunctionType *BUFFER_FUNCTIONS[] = {shellExit,shellCd,shellHelp};


int shellExit(char **argv)
{   
    printf("%s\n",argv[0]);
    
    return 1;
}

int shellCd(char **argv)
{

    printf("Usou o comando cd\n");
    return EXIT_SUCCESS;
}

int shellHelp(char **argv)
{

    printf("Usou o comando help\n");
    return EXIT_SUCCESS;
}

int addBuiltin(Node *root, const char **nameBuiltin, FunctionType **nameFunction)
{

    int tam = NUM_BUILTINS;

    for (int i = 0; i < tam; i++)
    {

        if (Search(root, nameBuiltin[i]) == NULL)
        {
            InsertTrie(root, nameBuiltin[i], nameFunction[i]);
        }
        else
        {
            printf("%s: comando existente\n", nameBuiltin[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

Node *startBuffer(){

    Node *root = CreateNode();

    if(addBuiltin(root,BUFFER_BUILTINS,BUFFER_FUNCTIONS)){

        perror("Não foi possível iniciar a árvore de dependências");
        return NULL;
    }


    return root;
}