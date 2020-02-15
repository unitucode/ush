#include "ush.h"

t_list **mx_get_list_procs() {
    static t_list *list = NULL;

    return &list;
}

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
}


// t_processes_on_pause **mx_get_procs_on_pause() {
//     static t_processes_on_pause *processes = NULL;

//     return &processes;
// }

// void mx_add_process(t_process *process, t_processes_on_pause **procs) {
//     t_processes_on_pause *current = procs[0];

//     if (current == NULL) {
//         current = (t_processes_on_pause *)malloc(sizeof(t_processes_on_pause));
//         current->process = process;
//         current->next = NULL;
//         return;
//     }
//     while (current->next != NULL)
//         current = current->next;
//     current->next = (t_processes_on_pause *)malloc(sizeof(t_processes_on_pause));
//     current->next->process = process;
//     current->next->next = NULL;
// }

// t_process *mx_get_process_on_pause(char *input, t_processes_on_pause **procs) {
//     t_processes_on_pause *current = procs[0];
//     int id;
//     int i = 1;

//     if (current == NULL)
//         return NULL;
//     if (input[0] == '%') {
//         id = atoi(input + 1);
//         for (; i < id && current->next != NULL; i++)
//             current = current->next;
//         return (i == id) ? current->process : NULL;
//     }
//     id = atoi(input);
//     while (current->next != NULL) {
//         if (current->process->pid == id)
//             return current->process;
//         current = current->next;
//     }
//     return NULL;
// }

// void mx_remove_process(t_process *process, t_processes_on_pause **procs) {
//     t_processes_on_pause *current = procs[0];
//     t_process *temp = NULL;

//     if (current == NULL)
//         return;
//     if (current->process->pid == process->pid && current->next == NULL) {
//         free(&process);
//         process = NULL;
//         current = NULL;
//     }
//     while (current->next != NULL && current->next->process->pid != process->pid)
//         current = current->next;
//     if (current->next->process->pid == process->pid) {
//         temp = current->next->process;
//         current->next = current->next->next;
//         free(&temp);
//         temp = NULL;
//     }
// }

// void mx_output_processes(t_processes_on_pause **procs) {
//     t_processes_on_pause *current = procs[0];

//     if (current == NULL) {
//         mx_printstr("List is empty\n");
//         return;
//     }
//     while (current->next != NULL) {
//         mx_printstr("Element - ");
//         mx_printstr(mx_itoa(current->process->pid));
//         mx_printstr("\n");
//         current = current->next;
//     }
// }
