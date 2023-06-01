#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  

  Automata AFND = readAutomatafromDot("TP2.dot");
  Automata AFD = transformAFNDtoAFD(AFND);
  
  printf("--- Test Minimize: ---\n");
  Automata min = minimize(AFD);

  printf("Minimize: \n");
  printAutomata(min);

  writeAutomataToDot(min, "minimize_TP2.dot");
  printf("Test Minimize Passed\n");

  return 1;
  
  
}

