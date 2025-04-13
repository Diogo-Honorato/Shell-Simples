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

/* Handles SIGINT */
void signalHandler(int signal)
{
    switch (signal)
    {
    case SIGINT:
        /* Put readline in a clean state after Ctrl+C. */
        rl_free_line_state();
        rl_cleanup_after_signal();

        /* HACK: Shows ^C and skip to next line! */
        printf("^C");
        break;
    }
}