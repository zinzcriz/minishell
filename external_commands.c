#include "msh.h"
void extract_external_commands(char **external_commands)
{
    char ch, str[30];
    int index = 0, i = 0;
    int fd = open("ext_commands.txt", O_RDONLY);
    while (read(fd, &ch, 1) != 0)
    {
        if (ch == '\n' || ch == EOF)
        {
            str[i] = '\0';
            external_commands[index] = malloc(strlen(str) + 1);
            strcpy(external_commands[index], str);
            index++;
            i = 0;
        }
        else
        {
            str[i] = ch;
            i++;
        }
    }
    // i=0;
    // while(external_commands[i])
    // {
    //     printf("%s\n",external_commands[i]);
    //     i++;
    // }
}

int isexternal_command(char **external_commands, char *command)
{
    int i=0;
    while (external_commands[i])
    {
        //printf("%s\n",external_commands[i]);
        if (strstr(external_commands[i], command) != NULL)
        {
            //printf("%s\n",external_commands[i]);
            return 1;
        }
        i++;
    }
    return 0;
}

// int convertTo2d_execute(char *input_str)
// {
//     //char (*commands)[10];
//     int count=0;
//     for(int i=0;input_str[i]!='\0';i++)
//     {
//         if(input_str[i]==' ')
//         {
//             count++;
//         }
//     }
//     count++;
//     char (*commands)[10]=malloc(count*sizeof(char[10]));
//     int start=0;
//     int j=0;
//     for(int i=0;input_str[i]!='\0';i++)
//     {
//         if(input_str[i]==' ')
//         {
//             input_str[i]='\0';
//             strcpy(commands[j],input_str+start);
//             commands[j][9] = '\0'; 
//             j++;
//             start=i+1;
//         }
//     }
//     strcpy(commands[j],input_str+start);
//     commands[j][9] = '\0'; 
    
//     char *argv[count+1];
//     for(int i=0;i<count;i++)
//     {
//         //printf("%s\n",commands[i]);
//         argv[i]=commands[i];
//     }
//     argv[count]=NULL;


//     pid_t pid = fork();

//     if (pid == 0) {
//         // Child process
//         execvp(argv[0],argv);
//         perror("execvp failed");
//     } else {
//         // Parent process
//         int status;
//         wait(&status);
//         //printf("Child finished executing\n");
//     }

    
// }


char ** convertTo2d_execute(char *input_str)
{
    //char (*commands)[10];
    int count=0;
    for(int i=0;input_str[i]!='\0';i++)
    {
        if(input_str[i]==' ')
        {
            count++;
        }
    }
    count++;
    char (*commands)[10]=malloc(count*sizeof(char[10]));
    int start=0;
    int j=0;
    for(int i=0;input_str[i]!='\0';i++)
    {
        if(input_str[i]==' ')
        {
            input_str[i]='\0';
            strcpy(commands[j],input_str+start);
            commands[j][9] = '\0'; 
            j++;
            start=i+1;
        }
    }
    strcpy(commands[j],input_str+start);
    commands[j][9] = '\0'; 
    
    //char *argv[count+1];
    char **argv=malloc((count+1)*sizeof(char *));
    for(int i=0;i<count;i++)
    {
        //printf("%s\n",commands[i]);
        argv[i]=commands[i];
    }
    argv[count]=NULL;


   return argv;

    
}

