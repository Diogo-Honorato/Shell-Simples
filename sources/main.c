#include "../headers/main/main.h"

int main(){

    if(system("clear") == -1){

        perror("\nA child process could not be created, or its status could not be retrieved.");
        exit(0);
    }

    char* output = NULL;

    initReadCommand();

    //Main loop
    while((output = readCommand(typePrompt())) != NULL){

        printf("seu comando foi: %s\n",output);//Apenas para testes
        free(output);
    }

    return 0;
}

