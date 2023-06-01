#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("--- Test Kleene ---\n");
  Automata AFND = readAutomatafromDot("AFND_TP2.dot");
  printf("Kleene: \n");
  Automata k = kleene_clousure(AFND);
  printAutomata(k);
  writeAutomataToDot(k, "kleene.dot");
  printf("\n--- Test Kleene Passed ---\n");
  return 1;
}