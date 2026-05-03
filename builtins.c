#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "builtins.h"

//Built in cmd for echo
int cmd_echo(char **args) {
    for (int i = 1; args[i]; i++) {
        printf("%s", args[i]);
        if (args[i + 1]) printf(" ");
    }
    printf("\n");
    return 0;
}

//Built in cmd for exit
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
    printf("%s: not found\n", args[1]);
    return 0;
}

builtin builtins[] = {
    {"echo", cmd_echo},
    {"exit", cmd_exit},
    {"type", cmd_type},
};

int builtin_count = sizeof(builtins) / sizeof(builtin);