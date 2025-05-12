#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMDS 10
#define MAX_ARGS 64

void parse_command(char *cmd, char **args) {
    int i = 0;
    char *token = strtok(cmd, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

void execute_with_pipes(char *input) {
    char *cmds[MAX_CMDS];
    int num_cmds = 0;

    // Separa os comandos por '|'
    char *token = strtok(input, "|");
    while (token != NULL && num_cmds < MAX_CMDS) {
        cmds[num_cmds++] = strdup(token);  // strdup para preservar input original
        token = strtok(NULL, "|");
    }

    int pipefd[2], prev_fd = -1;

    for (int i = 0; i < num_cmds; i++) {
        char *args[MAX_ARGS];
        parse_command(cmds[i], args);

        if (i < num_cmds - 1) {
            if (pipe(pipefd) < 0) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Redireciona entrada se não for o primeiro comando
            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO);
                close(prev_fd);
            }

            // Redireciona saída se não for o último comando
            if (i < num_cmds - 1) {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[0]);
                close(pipefd[1]);
            }

            execvp(args[0], args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        // Pai: fecha descritores que não precisa
        if (prev_fd != -1) close(prev_fd);
        if (i < num_cmds - 1) {
            close(pipefd[1]);
            prev_fd = pipefd[0];
        }
    }

    // Espera todos os filhos
    for (int i = 0; i < num_cmds; i++) {
        wait(NULL);
    }

    // Libera memória
    for (int i = 0; i < num_cmds; i++) {
        free(cmds[i]);
    }
}
