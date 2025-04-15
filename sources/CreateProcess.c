#include "../headers/CreateProcess.h"

//Cria um processo com 'fork()' e o executa com 'execvp()' 
int createProcess(char **argv){

    pid_t pid;

    pid = fork();

    if(pid < 0){

        perror("Error fork\n");
        exit(EXIT_FAILURE);
    }

    if(pid == 0){

        //Processo filho
        if(execvp(argv[0],argv) == -1){

            printf("%s: comando não encontrado\n",argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    else{

        //Processo pai
        wait(NULL); //Aguardando processo filho acabar
    }

    return EXIT_SUCCESS;
}