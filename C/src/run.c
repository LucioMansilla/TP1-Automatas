#include "../libs/mini_grep.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s regex line\n", argv[0]);
        return 1;
    }

    char *regex = argv[1];
    char *line = argv[2];
    bool result = minigrep(regex, line);

    if (result)
        printf("The line matches the provided regular expression.\n");
    else
        printf("The line does NOT match the provided regular expression.\n");

    return 0;
}
