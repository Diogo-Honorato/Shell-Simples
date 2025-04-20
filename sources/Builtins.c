#include "../headers/Builtins.h"
#include <unistd.h>

int shellExit(char **argv)
{   
    printf("%s\n",argv[0]);
    
    return CLOSE_SHELL;
}

int shellCd(char **argv)
{
    if (argv[1] == NULL) {
        char *home_dir = getenv("HOME");
        if (home_dir == NULL) {
            fprintf(stderr, "cd: não foi possível obter o diretório home\n");
            return EXIT_FAILURE;
        }
        if (chdir(home_dir) != 0) {
            perror("cd");
            return EXIT_FAILURE;
        }
    } else {
        if (chdir(argv[1]) != 0) {
            perror("cd");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

int shellHelp(char **argv)
{
    (void)argv;//so pra parar de aparecer warning, pode retirar quando implementar a função

    printf("Usou o comando help\n");
    return EXIT_SUCCESS;
}

int addBuiltin(Node *root, const char **NAME_BUILTINS, FunctionType **nameFunctions, const size_t NUM_BUILTINS)
{

    for (size_t i = 0; i < NUM_BUILTINS; i++)
    {

        if (Search(root,NAME_BUILTINS[i]) == NULL)
        {
            InsertTrie(root,NAME_BUILTINS[i], nameFunctions[i]);
        }
        else
        {
            printf("%s: comando existente\n",NAME_BUILTINS[i]);
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

Node *startBufferBuiltins(){

    Node *root = CreateNode();

    /*Obs.: A ordem das inserções dos nomes dos builtins tem que ser a mesma 
    que a ordem de inserção de suas funções*/
    const char* BUFFER_BUILTINS[] = {"exit","cd","help"};

    FunctionType *BUFFER_FUNCTIONS[] = {shellExit,shellCd,shellHelp};

    //Total de Builtins
    size_t NUM_BUILTINS = sizeof(BUFFER_BUILTINS)/sizeof(char*);

    if(addBuiltin(root,BUFFER_BUILTINS,BUFFER_FUNCTIONS, NUM_BUILTINS)){

        perror("Não foi possível iniciar a árvore de dependências");
        return NULL;
    }


    return root;
}