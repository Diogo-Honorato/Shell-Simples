#include "../headers/ExecuteCommand.h"
#include "../headers/ReadCommand.h"
#include "../headers/CreateProcess.h"
#include "../headers/Pipe.h"
#include <string.h>

int executeCommand(char *command, Node *root) {

    // Verifica se a linha contém pipe antes de tokenizar
    if (strchr(command, '|') != NULL) {
        // Executa pipeline diretamente
        execute_with_pipes(command);
        return EXIT_SUCCESS;
    }

    char **tokens = tokenString(command);
    int i = 0, background = 0;
    
    if (tokens[0] == NULL) {
        // Comando vazio
        free(tokens);
        return EXIT_SUCCESS;
    }
    
    // Verificar se o comando deve ser executado em background
    while (tokens[i] != NULL) i++;
    if (i > 0 && strcmp(tokens[i-1], "&") == 0) {
        background = 1;
        tokens[i-1] = NULL; // Remove o & da lista de argumentos
    }
    
    // Verificar se há pipes
    i = 0;
    int pipeCount = 0;
    while (tokens[i] != NULL) {
        if (strcmp(tokens[i], "|") == 0) pipeCount++;
        i++;
    }
    
    if (pipeCount > 0) {
        // Implementação básica para comandos com pipe
        printf("Comando com pipe detectado. Funcionalidade ainda não implementada.\n");
        free(tokens);
        return EXIT_SUCCESS;
        
        // Nota: A implementação completa de pipes será adicionada posteriormente
    } else {
        // Verificar se é um comando interno
        FunctionType *function = Search(root, tokens[0]);
        
        if (function != NULL) {
            int result = function(tokens);
            free(tokens);
            return result;
        } else {
            // É um comando externo
            int result = createProcess(tokens, background);
            free(tokens);
            return result;
        }
    }
}