#include "../../headers/read_command/readCommand.h"

char* readCommand(const char* prompt){

    char* stringLine = NULL;

    stringLine = readline(prompt);

    if(CLOSE_SHELL){

        //Libera o comando e encerra o shell
        free(stringLine);
        exit(0);
    }
    else{

        add_history(stringLine);  //Adicionando comando no historico
    }

    return stringLine;
}