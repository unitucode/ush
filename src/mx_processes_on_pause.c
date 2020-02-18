#include "ush.h"

void mx_pop_process(int id) {
    t_list **list = mx_get_list_procs();
    t_list *current = *mx_get_list_procs();
    t_process *process = NULL;
    int i = 2;

    if (id == 1) {
        *list = (*list)->next;
        return;
    }
    for (; i < id && current != NULL; i++)
        current = current->next;
    process = current->next->data;
    current->next = current->next->next;
    free(process);
    process = NULL;
}

t_process *mx_get_process_by_id(int id) {
    t_list **list = mx_get_list_procs();
    t_list *current = *list;
    
    if (id == 1)
        return (t_process *)(*list)->data;
    for (int i = 2; i < id && current != NULL; i++)
        current = current->next;
    if (current == NULL)
        return NULL;
    return (t_process *)current->next->data;
}

int mx_get_process_id_by_pid(pid_t pid) {
    int result = 1;
    t_list *current = *mx_get_list_procs();
    
    if (current == NULL)
        return -1;
    while (current != NULL) {
        if (((t_process *)current->data)->pid == pid)
            return result;
        current = current->next;
        result++;
    }
    return -1;
}

pid_t mx_get_process_pid_by_id(int id) {
    t_list *current = *mx_get_list_procs();
    int i = 1;

    if (id < 1)
        return -1;
    if (current == NULL)
        return -1;
    for (; i != id && current != NULL; i++)
        current = current->next;
    if (i != id)
        return -1;
    return ((t_process *)current->data)->pid;
    return 0;
}
