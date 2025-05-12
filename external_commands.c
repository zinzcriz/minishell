#include "msh.h"
void extract_external_commands(char **external_commands)
{
    char ch, str[30];
    int index = 0, i = 0;
    int fd = open("ext_commands.txt", O_RDONLY); //Opening file
    while (read(fd, &ch, 1) != 0)
    {
        if (ch == '\n' || ch == EOF)
        {
            //Reading untill /n or EOF,and then copies that word to 2d array
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
}

//To check whether a command is external
int isexternal_command(char **external_commands, char *command)
{
    int i=0;
    while (external_commands[i])
    {
        if (strstr(external_commands[i], command) != NULL)
        {
            return 1;
        }
        i++;
    }
    return 0;
}




char ** convertTo2d_execute(char *input_str)
{
    //char (*commands)[10];
     // Count how many space-separated words are in the input string
    int count=0;
    for(int i=0;input_str[i]!='\0';i++)
    {
        if(input_str[i]==' ')
        {
            count++;
        }
    }
    count++;

     // Allocate memory for storing the words (each up to 10 characters)
    // 'commands' is a pointer to an array of 10 characters (2D array)
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

    // Create an array of pointers to the words (like argv)
    char **argv=malloc((count+1)*sizeof(char *));
    for(int i=0;i<count;i++)
    {
        //printf("%s\n",commands[i]);
        argv[i]=commands[i]; // Each argv[i] points to a command string
    }
    argv[count]=NULL;  // NULL-terminate the array (like standard argv)


   return argv; // Return the array of string pointers

    
}

