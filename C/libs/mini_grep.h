#ifndef MINI_GREP_H
#define MINI_GREP_H
#include "../libs/automata.h"
#include <stdbool.h>

Automata L();
Automata P();
Automata F();
Automata F_prime(Automata f);
Automata T();
Automata T_prime(Automata t);
Automata E();
Automata E_prime(Automata e);
Automata S();
bool accept(char c);
Automata parser(char *regex);
bool minigrep(char* regex, char* line);

#endif
