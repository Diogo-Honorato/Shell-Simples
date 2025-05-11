#include "../headers/main.h"
#include "../headers/Builtins.h"

int main()
{
    if (system("clear") == -1)
    {
        perror("A child process could not be created, or its status could not be retrieved.\n");
        exit(0);
    }
    
    char *commands = NULL;
    Node *root = startBufferBuiltins(); // Changed from startBuffer() to startBufferBuiltins()
    initReadCommand();
    
    if(root == NULL){
        exit(EXIT_FAILURE);
    }
    
    // Main loop
    while ((commands = readCommand(typePrompt())) != NULL)
    {
        // Verifica se o comando não está vazio
        if (commands != NULL && *commands != '\0')
        {
            if (executeCommand(commands, root)) {
                // Se executeCommand retornar verdadeiro, saímos do loop
                free(commands);
                break;
            }
        }
        
        free(commands);
    }
    
    FreeTrie(root);
    
    return EXIT_SUCCESS;
}