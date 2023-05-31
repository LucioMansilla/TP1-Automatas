#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf("--- Test Union ---\n");
  char *in_file_one = argv[1];
  char *in_file_two = argv[2];
  char *out_file = argv[3];

  Automata AFND = readAutomatafromDot("TP2.dot");
  Automata AFND2 = readAutomatafromDot("TP2.dot");

  printf("Union: \n");
  Automata u = unionA(AFND, AFND2);
  printAutomata(u);
  writeAutomataToDot(u, "union.dot");
  printf("\n--- Test Union Passed ---\n");
  return 1;
}