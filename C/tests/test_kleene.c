#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("--- Test Kleene ---\n");
  char *in_file_one = argv[1];
  char *out_file = argv[2];

  Automata AFND = readAutomatafromDot("TP2.dot");

  printf("Kleene: \n");
  Automata k = kleene_clousure(AFND);
  printAutomata(k);
  writeAutomataToDot(k, "kleene.dot");

  printf("\n--- Test Kleene Passed ---\n");
  return 1;
}