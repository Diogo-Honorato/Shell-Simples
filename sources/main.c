#include "../headers/main.h"

int main()
{
    if (system("clear") == -1)
    {

        perror("A child process could not be created, or its status could not be retrieved.\n");
        exit(0);
    }
    
    char **argv = NULL;
    char *commands = NULL;

    Node *root = startBuffer();
    initReadCommand();
    

    if(root == NULL){

        exit(EXIT_FAILURE);
    }
    
    FunctionType *function;

    // Main loop
    while ((commands = readCommand(typePrompt())) != NULL)
    {
        //Verifica se o comando e externo ou interno
        if (commands != NULL && *commands != '\0')
        {
            argv = tokenString(commands);

            function = Search(root, argv[0]);

            if (function != NULL)
            {
                if(function(argv)){//Execução do comando interno (builtins)

                    free(argv);
                    free(commands);
                    break;
                } 
            }
            else{

                createProcess(argv); //Execução do comando externo
            }

            free(argv);
        }

        free(commands);
    }

    FreeTrie(root);

    return EXIT_SUCCESS;
}
