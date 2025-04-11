#include "../../headers/view/PrintPrompt.h"

void printPrompt() {
    char hostname[HOST_NAME_MAX];
    char cwd[PATH_MAX];
    char *home_dir = getenv("HOME");
    struct passwd *pw = getpwuid(getuid());

    if (gethostname(hostname, HOST_NAME_MAX) != 0) {
        perror("gethostname");
        exit(EXIT_FAILURE);
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    char *abbreviated_cwd = cwd;
    if (home_dir != NULL && strstr(cwd, home_dir) == cwd) {

        abbreviated_cwd = malloc(strlen(cwd) - strlen(home_dir) + 2);
        if (abbreviated_cwd != NULL) {
            abbreviated_cwd[0] = '~';
            strcpy(abbreviated_cwd + 1, cwd + strlen(home_dir));
        }
    }

    printf("%s%s@%s%s%s:%s%s%s$ ",
        COLOR_USER_HOST, pw->pw_name,
        COLOR_USER_HOST, hostname,
        COLOR_RESET,      
        COLOR_PATH, abbreviated_cwd, 
        COLOR_RESET               
    );

    if (abbreviated_cwd != cwd) {
        free(abbreviated_cwd);
    }
}

