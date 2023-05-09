#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "utils.h"

typedef struct {
  List *k;
  List *alphabet;
  List **delta;
  int initialState;
  List *finalStates;
} Automata;

Automata createAutomata(List *k, List *alphabet, List **delta, int initialState,
                        List *finalStates);
int pertains(Automata a, char *w);
List *move(Automata a, List *states, int symbol);
List *lambdaClousure(Automata a, List *states);
void printAutomata(Automata a);
Automata transformAFNDtoAFD(Automata a);

Automata readAutomatafromDot(char *filename);
void writeAutomataToDot(Automata a, char *filename);

#endif