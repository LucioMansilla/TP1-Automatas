#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf(" -- Test TP1 -- \n");

  Automata AFND = read_automaton_from_dot("AFND_TP.dot");

  char *a = "b";

  printf("Original automata:");
  print_automaton(AFND);

  Automata AFD = to_AFD(AFND);

  write_automaton_to_dot(AFD, "AFD_TP.dot");

  printf("The conversion from AFND to AFD has been completed.\n");
  printf("You can view the result in the file %s\n", "AFD_TP.dot");

  printf("belongs: %d\n", belongs(AFND, a));

  printf(" -- Test TP1 passed -- \n");
  return 1;
}