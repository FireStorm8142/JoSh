#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtins.h"

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    char command[1024];

    while (1) {
        printf("$ ");
        if (fgets(command, sizeof(command), stdin) == NULL) break;
        command[strcspn(command, "\n")] = '\0';

        char *args[100];
        int i = 0;

        char *token = strtok(command, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) continue;

        // check builtins
        int found = 0;
        for (int i = 0; i < builtin_count; i++) {
            if (strcmp(args[0], builtins[i].name) == 0) {
                builtins[i].func(args);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("%s: command not found\n", args[0]);
        }
    }
    return 0;
}