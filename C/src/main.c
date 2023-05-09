#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char *in_file = argv[1];
  char *out_file = argv[2];

  Automata AFND = readAutomatafromDot(in_file);

  printf("Original automata:");
  printAutomata(AFND);

  Automata AFD = transformAFNDtoAFD(AFND);

  writeAutomataToDot(AFD, out_file);

  printf("The conversion from AFND to AFD has been completed.\n");
  printf("You can view the result in the file %s\n", out_file);

  return 0;
}