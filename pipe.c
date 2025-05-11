#include "msh.h"
int status;
int execute_pipe(char **arr)
{
    int argc_count=0;
    while(arr[argc_count++]!=NULL);
    argc_count--;
    printf("%d\n",argc_count);
    int cmd_ind[argc_count];
    int pipe_count=0;
    int j=0;
    cmd_ind[j++]=0;
    for(int i=0;i<argc_count;i++)
    {
        if(!strcmp(arr[i],"|"))
        {
            arr[i]=NULL;
            pipe_count++;
            cmd_ind[j++]=i+1;
        }
    }

    int fd[2];
    pid_t pid;
    int std_in = dup(0); // backup stdin file descriptor
    int std_out = dup(1);

    for(int i=0;i<pipe_count+1;i++)
    {
        if(i!=pipe_count)
             pipe(fd);
        pid=fork();
        if(pid>0)
        {
            close(fd[1]);
            dup2(fd[0],0);
            close(fd[0]);
            wait(&status);
        }
        else if(pid==0)
        {
            if(i!=pipe_count)
            {
                close(fd[0]);
                dup2(fd[1],1);
            }
            execvp(arr[cmd_ind[i]],arr+cmd_ind[i]);
        }
    }
    dup2(std_in, 0); // restore stdin and stdout
    dup2(std_out, 1);
    close(std_in); // close backup
    close(std_out);
}