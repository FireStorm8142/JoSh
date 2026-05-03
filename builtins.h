#ifndef BUILTINS_H
#define BUILTINS_H

typedef int (*builtin_func)(char **args);

typedef struct {
    char *name;
    builtin_func func;
} builtin;

int cmd_echo(char **args);
int cmd_exit(char **args);
int cmd_type(char **args);

extern builtin builtins[];
extern int builtin_count;

#endif