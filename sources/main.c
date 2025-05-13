#include "../headers/main.h"
#include "../headers/Builtins.h"

int main()
{
    if (system("clear") == -1)
    {
        perror("Um processo filho não pôde ser criado ou seu status não pôde ser recuperado.\n");
        exit(0);
    }
    
    char *commands = NULL;
    Node *root = startBufferBuiltins();
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