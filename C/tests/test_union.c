#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("--- Test Union ---\n");

  Automata AFND = readAutomatafromDot("TP2.dot");
  Automata AFND2 = readAutomatafromDot("TP2.dot");

  printf("Union: \n");
  Automata u = unionA(AFND, AFND2);
  printAutomata(u);
  writeAutomataToDot(u, "union.dot");
  printf("\n--- Test Union Passed ---\n");
  return 1;
}