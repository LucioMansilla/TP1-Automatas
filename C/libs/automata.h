#ifndef AUTOMATA_H
#define AUTOMATA_H
#include "utils.h"

typedef struct
{
  List *k;
  List *alphabet;
  List **delta;
  int initial_state;
  List *final_states;
} Automata;

Automata create_automaton(List *k, List *alphabet, List **delta, int initial_state,
                        List *final_states);
int belongs(Automata a, char *w);
List *move(Automata a, List *states, int symbol);
List *lambda_clousure(Automata a, List *states);
void print_automaton(Automata a);
Automata to_AFD(Automata a);

Automata read_automaton_from_dot(char *filename);
void write_automaton_to_dot(Automata a, char *filename);
Automata rename_states(Automata automaton, int shift, List *new_k);
Automata concat(Automata a, Automata b);
Automata kleene_clousure(Automata automaton);
Automata compose(Automata automaton_1, Automata automaton_2);
List_List *quotient_set(Automata automaton);
Automata minimize(Automata automaton);

#endif