#include "msh.h"
extern Slist *head;
extern pid_t pid;
extern int jobs_count;
void execute_internal_commands(char *input_string)
{
    if(strstr(input_string,"exit")!=NULL)
    {
        exit(0);
    }
    else if(strcmp(input_string,"pwd")==0)
    {
        char path[50];
        getcwd(path,sizeof(path));
        printf("%s\n",path);
    }
    else if(strstr(input_string,"cd")!=NULL)
    {
        char *path=input_string+3;
        if (chdir(path) == 0) {
            printf("Changed directory to %s\n",path);
        }
        else
        {
            printf("Changing directory failed\n");
        }
    }
    else if(strcmp(input_string,"echo $$")==0)
    {
        pid_t pid=getpid();
        printf("%d\n",pid);
    }
    else if(strcmp(input_string,"jobs")==0)
    {
        print_list(head);
    }
    else if(strcmp(input_string,"fg")==0)
    {
        pid=return_last(head);
        kill(pid, SIGCONT);
        waitpid(pid, NULL, WUNTRACED); 
        sl_delete_last(&head);
        pid=1;
        if(jobs_count>0)
            jobs_count--;
    }
    else if(strcmp(input_string,"bg")==0)
    {
        pid_t pid_no=return_last(head);
        kill(pid_no, SIGCONT);
        sl_delete_last(&head);
        if(jobs_count>0)
            jobs_count--;
    }
    else if(strcmp(input_string,"echo $?")==0)
    {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {  // Check if child exited normally
            int exit_status = WEXITSTATUS(status);
            printf("Parent: child exited with status %d\n", exit_status);
        } else {
            printf("Parent: child did not exit normally\n");
        }
    }
    else if (strcmp(input_string,"echo $SHELL")==0)
    {
        const char *path=getenv("SHELL");
        if (path != NULL) {
            printf("SHELL: %s\n", path);
        } else {
            printf("SHELL environment variable not found.\n");
        }
    }
    
}