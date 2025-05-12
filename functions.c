#include "msh.h"
char *ext_cmd[200];
int pid_status = 1;

//Globally declaring pid
pid_t pid = 1;
char prompt_backup[20] = "minishell$";
int jobs_count = 0;
Slist *head = NULL; //Declaring slist globally
void my_handler(int signum)   //Signal handler function
{
    if (signum == SIGINT)
    {
        if (pid == 1) //only works for parent
        {
            printf("\n%s", prompt_backup);
            fflush(stdout);
        }
        else
        {
            printf("\n");
        }
    }
    else if (signum == SIGTSTP)
    {
        // if(pid!=0)
        if (pid == 1) //only works for parent
        {
            printf("\n%s", prompt_backup);
            // printf("%d\n",pid);
            fflush(stdout);
        }
        else
        {
            printf("\n", pid);
        }
    }
}

void scan_input(char *prompt, char *input_string)
{
    extract_external_commands(ext_cmd);
    signal(SIGINT, my_handler);  //Registering signal
    signal(SIGTSTP, my_handler);
    while (1)
    {
        strcpy(prompt_backup, prompt);
        printf("%s", prompt);
        scanf("%[^\n]", input_string);
        getchar();
        // printf("%s\n",input_string);
        if (strncmp(input_string, "PS1", 3) == 0)
        {
            if (strncmp(input_string, "PS1=", 4) != 0)
            {
                printf("%s: Command not found...\n",input_string);
            }
            else
            {
                char *temp = strtok(input_string, "=,\n");
                temp = strtok(NULL, "=,\n");
                // printf("%s\n",temp);
                strcpy(prompt, temp);
            }
        }
        else
        {
            // char *cmd=get_command(input_string);
            // printf("%s\n",cmd);
            char *commd = get_command(input_string);  //Returns the first word of command
            check_command_type(commd, input_string);  //Checks type of command
        }
    }
}

char *get_command(char *input_string)
{
    int i = 0;
    while (input_string[i] != '\0')
    {
        if (input_string[i] == ' ')
        {
            break;
        }
        i++;
    }
    char *commd = malloc(i + 1);
    strcpy(commd, input_string);
    commd[i] = '\0';
    return commd;
}

int check_command_type(char *cmd, char *input_str)
{
    char input_str_backup[100]; //Backup for input string since it is modified
    strcpy(input_str_backup, input_str);
    if (isbuiltin(cmd))
    {
        //printf("Command is Builtin\n");
        execute_internal_commands(input_str);
    }
    else if (isexternal_command(ext_cmd, cmd))
    {
        //printf("External command\n");
        if (strstr(input_str, "|") != NULL)
        {
            //printf("This command has pipe in it\n");
            char **argv;
            argv = convertTo2d_execute(input_str);
            execute_pipe(argv);
        }
        else
        {
            char **argv;
            argv = convertTo2d_execute(input_str); //convert input string into 2d array
            pid = fork();

            if (pid == 0)
            {
                // Child process
                signal(SIGINT, SIG_DFL); //Changing signal bahaviour into default for child
                signal(SIGTSTP, SIG_DFL);
                execvp(argv[0], argv);
                perror("execvp failed");
            }
            else
            {
                // Parent process
                int status;
                waitpid(pid, &status, WUNTRACED);
                if (WIFEXITED(status))
                {
                    //printf("Parent: Child exited with status %d\n", WEXITSTATUS(status));
                }
                else if (WIFSIGNALED(status))
                {
                    //printf("Parent: Child was killed by signal %d\n", WTERMSIG(status));
                }
                else if (WIFSTOPPED(status))
                {
                    //printf("Child was stopped by signal %d\n", WSTOPSIG(status));
                    if (insert_at_last(&head, pid, input_str_backup) == SUCCESS) 
                    {
                        //Calling insert function to make linked list containing info about all stopped jobs
                        jobs_count++; //Increasing jobs count
                        printf("[%d]+\tStopped", jobs_count);
                        printf("\t\t\t");
                        printf("%s\n", input_str_backup);
                    }
                }
                else
                {
                    printf("Parent: Child ended abnormally\n");
                }
                pid = 1; //Changes pid value to 1 again
            }
        }
    }
    else
    {
        printf("%s: Command not found...\n",cmd);
    }
}

//Function for checking command is builtin
int isbuiltin(char *command)
{
    char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
                        "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
                        "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", "jobs", "fg", "bg", NULL};

    int i = 0;
    while (builtins[i])
    {
        // printf("%s\n",builtins[i]);
        if (strstr(command, builtins[i]) != NULL)
        {
            return 1;
        }
        i++;
    }
    return 0;
}
