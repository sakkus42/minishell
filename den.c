#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char* input;
    int num;

    while((input = readline("Enter a positive number: ")) != NULL) {
            rl_replace_line("Please enter a positive number: ", 1);
            rl_redisplay();
    }
    printf("\n");
    return 0;
}
