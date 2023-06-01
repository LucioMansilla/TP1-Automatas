#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  printf(" -- Test TP1 -- \n");

  Automata AFND = readAutomatafromDot("AFND_TP.dot");

  char *a = "b";

  printf("Original automata:");
  printAutomata(AFND);

  Automata AFD = transformAFNDtoAFD(AFND);

  writeAutomataToDot(AFD, "AFD_TP.dot");

  printf("The conversion from AFND to AFD has been completed.\n");
  printf("You can view the result in the file %s\n", "AFD_TP.dot");

  printf("Pertains: %d\n", pertains(AFND, a));

  printf(" -- Test TP1 passed -- \n");
  return 1;
}