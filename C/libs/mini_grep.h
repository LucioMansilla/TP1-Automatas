#ifndef MINI_GREP_H
#define MINI_GREP_H
#include "../libs/automata.h"
#include <stdbool.h>
bool accept(char c);
Automata L();
Automata P();
Automata F();
Automata F_prime();
Automata T();
Automata T_prime();
Automata E();
Automata E_prime();
Automata S();
Automata parser(char *regex);
bool minigrep(char* regex, char* line);

#endif
