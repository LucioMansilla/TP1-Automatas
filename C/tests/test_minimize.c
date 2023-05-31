#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  

  Automata AFND = readAutomatafromDot("TP2.dot");

  Automata AFD = transformAFNDtoAFD(AFND);
  
 // writeAutomataToDot(AFD, out_file);
  quotient_set(AFD);
  //quotient_playground(AFD);
  
  
  return 0;
}