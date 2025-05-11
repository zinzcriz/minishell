#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

//#include "builtin_commands.h"

#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  3

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
//     "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
//     "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", "NULL"};

#define SUCCESS 0
#define FAILURE -1
typedef struct node
{
    pid_t pid_no;
	char cmd_str[100];
	struct node *link;
}Slist;

void scan_input(char *prompt, char *input_string);
char *get_command(char *input_string);

void copy_change(char *prompt, char *input_string);

int check_command_type(char *cmd,char *input_str);
void echo(char *input_string, int status);
void execute_internal_commands(char *input_string);
void signal_handler(int sig_num);
void extract_external_commands(char **external_commands);
int isbuiltin(char *command);
int isexternal_command(char **external_commands,char *command);
char **convertTo2d_execute(char *input_str);
int execute_pipe(char **arg);

//Linked list Functions

int insert_at_last(Slist **head, pid_t data,char *inp_str);
void print_list(Slist *head);
int sl_delete_last(Slist **head);
pid_t return_last(Slist *head);

#endif
