#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("--- Test Union ---\n");

  Automata AFND = read_automaton_from_dot("AFND_TP2.dot");
  Automata AFND2 = read_automaton_from_dot("AFND_TP2.dot");

  printf("Union: \n");
  Automata u = compose(AFND, AFND2);
  print_automaton(u);
  write_automaton_to_dot(u, "union.dot");
  printf("\n--- Test Union Passed ---\n");
  return 1;
}