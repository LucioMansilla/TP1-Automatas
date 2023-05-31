#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("--- Test Concat ---\n");

  Automata AFND = readAutomatafromDot("TP2.dot");
 Automata AFND2 = readAutomatafromDot("TP2.dot");
  printAutomata(AFND);
    printf("Now the other: \n");
    printAutomata(AFND2);
    
  printf("Concat: \n");
  Automata u = concat(AFND, AFND2);
  writeAutomataToDot(u, "concat.dot");

  printf("\n--- Test Concat Passed ---\n");
  return 1;
}