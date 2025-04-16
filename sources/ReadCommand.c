#include "../headers/ReadCommand.h"

char* readCommand(const char* prompt){

    //Tratador de sinais
    sigGroupHandler();
    
    char* stringLine = NULL;
    stringLine = readline(prompt);
    
    if(stringLine == NULL){

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


void sigGroupHandler(){
    
    signal(SIGINT,sigHandler);
}
void sigHandler(int sig){
    (void)sig;
    
    //Gera uma nova linha prompt após um sinal SIGINT(^C)
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

