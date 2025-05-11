#include "../headers/CreateProcess.h"

//Cria um processo com 'fork()' e o executa com 'execvp()' 
int createProcess(char **argv, int background) {
    pid_t pid;
    
    pid = fork();
    
    if (pid < 0) {
        perror("Error fork\n");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {
        // Processo filho
        if (execvp(argv[0], argv) == -1) {
            printf("%s: comando não encontrado\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    } else {
        // Processo pai
        if (!background) {
            wait(NULL); // Aguarda o processo filho se não for em background
        } else {
            printf("[%d] %s em background\n", pid, argv[0]);
        }
    }
    
    return EXIT_SUCCESS;
}