#include "../../headers/view/PrintPrompt.h"

/*Exibi o prompt na tela com o nome do host e o caminho atual de onde esta sendo 
  executado o programa */
const char* typePrompt() {

    struct passwd *pw = getpwuid(getuid());

    char hostname[HOST_NAME_MAX];
    char cwd[PATH_MAX];
    char *home_dir = getenv("HOME");
    static char prompt[512];

    // Obtém informações do sistema
    if (gethostname(hostname, HOST_NAME_MAX)) {
        perror("gethostname");
        return "[erro]";
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        return "[erro]";
    }
    
    if (!pw) {
        perror("getpwuid");
        return "[erro]";
    }

    // Substitui $HOME por '~' no caminho
    char *abbreviated_cwd = cwd;

    if (home_dir && strstr(cwd, home_dir) == cwd) {

        abbreviated_cwd = malloc(strlen(cwd) - strlen(home_dir) + 2);

        if (abbreviated_cwd) {
            sprintf(abbreviated_cwd, "~%s", cwd + strlen(home_dir));
        }
    }

    snprintf(
        prompt, sizeof(prompt),
        "%s%s@%s%s%s:%s%s%s$ ",
        COLOR_USER_HOST, pw->pw_name,
        COLOR_USER_HOST, hostname,
        COLOR_RESET,
        COLOR_PATH, abbreviated_cwd,
        COLOR_RESET
    );

    if (abbreviated_cwd != cwd) {
        free(abbreviated_cwd);
    }

    return prompt;
}
