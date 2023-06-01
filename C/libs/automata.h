#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "utils.h"

typedef struct
{
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
Automata renameStates(Automata automaton, int shift, List *new_k);
Automata concat(Automata a, Automata b);
Automata kleene_clousure(Automata automaton);
Automata unionA(Automata automaton_1, Automata automaton_2);
List_List *quotient_set(Automata automaton);
void quotient_playground(Automata automaton);
Automata minimize(Automata automaton);

#endif