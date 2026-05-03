#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtins.h"

int cmd_echo(char **args) {
    for (int i = 1; args[i]; i++) {
        printf("%s", args[i]);
        if (args[i + 1]) printf(" ");
    }
    printf("\n");
    return 0;
}

int cmd_exit(char **args) {
    exit(0);
}

int cmd_type(char **args){
    if (args[1] == NULL) return 0;
    for (int i = 0; i < builtin_count; i++){
        if (strcmp(args[1], builtins[i].name) == 0){
            printf("%s is a shell builtin\n", builtins[i].name);
            return 0;
        }
    }

    char *path = getenv("PATH");

    if (path == NULL) return 0;

    char path_copy[1024];
    strcpy(path_copy, path);

    char *dir = strtok(path_copy, ":");

    while (dir != NULL) {
        char full[1024];
        snprintf(full, sizeof(full), "%s/%s", dir, args[1]);

        if (access(full, X_OK) == 0) {
            printf("%s is %s\n", args[1], full);
            return 0;
        }

        dir = strtok(NULL, ":");
    }
    printf("%s: not found\n", args[1]);
    return 0;
}

builtin builtins[] = {
    {"echo", cmd_echo},
    {"exit", cmd_exit},
    {"type", cmd_type},
};

int builtin_count = sizeof(builtins) / sizeof(builtin);