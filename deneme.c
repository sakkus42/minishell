#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct s_list
{
    void            *content;
    struct s_list   *next;
}                   t_list;

typedef struct s_parse
{
    pid_t   pid;
    char    **argv;
}           t_parse;

void execute_pipes(t_list *commands) {
    int num_commands = 0;
    for (t_list *current = commands; current != NULL; current = current->next)
        num_commands++;
    int pipefd[num_commands - 1][2];
    for (int i = 0; i < num_commands - 1; i++) {
        if (pipe(pipefd[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
    int command_idx = 0;
    for (t_list *current = commands; current != NULL; current = current->next, command_idx++) {
        t_parse *parse = (t_parse *)current->content;
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            if (command_idx > 0) {
                dup2(pipefd[command_idx - 1][0], STDIN_FILENO);
            }
            if (command_idx < num_commands - 1) {
                dup2(pipefd[command_idx][1], STDOUT_FILENO);
            }
            for (int i = 0; i < num_commands - 1; i++) {
                close(pipefd[i][0]);
                close(pipefd[i][1]);
            }
            execve(parse->argv[0], parse->argv, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            parse->pid = pid;
        }
    }
    for (int i = 0; i < num_commands - 1; i++) {
        close(pipefd[i][0]);
        close(pipefd[i][1]);
    }
    for (t_list *current = commands; current != NULL; current = current->next) {
        t_parse *parse = (t_parse *)current->content;
        waitpid(parse->pid, NULL, 0);
    }
}
int main() {
    // Example usage with cat | ls
    t_parse cmd1 = {0, (char *[]){"/bin/cat", NULL}};
    t_parse cmd2 = {0, (char *[]){"/bin/ls", NULL}};
    t_list command_list = {&cmd1, &(t_list){&cmd2, NULL}};
    execute_pipes(&command_list);
    return 0;
}