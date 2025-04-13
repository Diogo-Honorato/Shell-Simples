#include "../../headers/read_command/readCommand.h"

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