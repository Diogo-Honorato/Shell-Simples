#include "../../headers/read_command/ReadCommand.h"

char* readCommand(const char* prompt){

    char* stringLine = NULL;

    stringLine = readline(prompt);

    if(CLOSE_SHELL){

        //Libera o comando e encerra o shell
        free(stringLine);
        return NULL;
    }
    else{

        add_history(stringLine);  //Adicionando comando no historico
    }

    return stringLine;
}

void initReadCommand(){
    
   //Configure o readline para completar caminhos automaticamente quando a tecla Tab for pressionada.
    rl_bind_key('\t', rl_complete);
    // Ativar historico
    using_history();
}

//Tokenização da string de comandos
char** tokenString(char* string){

    char** tokens = calloc(BUFFER_SIZE, sizeof(*tokens));

    if(!tokens){

        perror("Falha ao alocar memoria para 'tokens'\n");
        exit(EXIT_FAILURE);
    }

    tokens[0] = strtok(string,DELIMITERS);

    for(int i = 1; (tokens[i] = strtok(NULL,DELIMITERS)) != NULL; i++){

        if((i + 1) == BUFFER_SIZE){

            perror("limite de comandos alcançados\n");
            break;
        }
    }

    return tokens;
}

