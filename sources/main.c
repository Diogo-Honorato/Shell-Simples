#include "../headers/main/main.h"

int main()
{

    if(system("clear") == -1){

        perror("A child process could not be created, or its status could not be retrieved.\n");
        exit(0);
    }

    char** argv = NULL;
    char* commands = NULL;
    Node *root = CreateNode();

    initReadCommand();

    //Main loop
     while((commands = readCommand(typePrompt())) != NULL){

        argv = tokenString(commands);

        createProcess(argv);

        free(commands);
        free(argv);
    }

    FreeTrie(root);

    return EXIT_SUCCESS;
}
