#include "msh.h"

//function to insert pid data and input string to linked list
int insert_at_last(Slist **head, pid_t data, char *inp_str)
{
    Slist *new = malloc(sizeof(Slist));
    if (new == NULL)
        return FAILURE;
    new->pid_no = data;
    strcpy(new->cmd_str, inp_str);
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }
    Slist *temp = *head;
    while (temp->link != NULL)
    {
        // printf("%d\n",temp->data);
        temp = temp->link;
    }
    temp->link = new;
    return SUCCESS;
}

//Function to print the linked list or jobs 
void print_list(Slist *head)
{
    if (head == NULL)
    {
        printf("No jobs to show\n");
    }
    else
    {
        int count = 1;
        while (head)
        {
            printf("[%d]+\tStopped", count);
            printf("\t\t\t");
            printf("%s\n", head->cmd_str);
            head = head->link;
            count++;
        }
    }
}

//Delete the last element of list
int sl_delete_last(Slist **head)
{
    if (*head == NULL)
    {
        return FAILURE;
    }
    Slist *temp = *head;
    Slist *prev = NULL;
    if (temp->link == NULL)
    {
        *head = prev;
        free(temp);
        return SUCCESS;
    }
    while (temp->link != NULL)
    {
        prev = temp;
        temp = temp->link;
    }
    free(temp);
    prev->link = NULL;
    return SUCCESS;
}

//Function to return last element of list
pid_t return_last(Slist *head)
{
    if (head == NULL)
    {
        printf("No jobs to show\n");
        // return FAILURE;
    }
    else
    {
        int count = 1;
        while (head->link != NULL)
        {

            head = head->link;
            count++;
        }
        printf("%s\n", head->cmd_str);
        return head->pid_no;
    }
}
