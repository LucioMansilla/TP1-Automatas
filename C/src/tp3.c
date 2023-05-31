#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  

  char *in_file = argv[1];
  //char *out_file = argv[2];
  Automata AFND = readAutomatafromDot(in_file);

  Automata AFD = transformAFNDtoAFD(AFND);
  
 // writeAutomataToDot(AFD, out_file);
  quotient_set(AFD);
  //quotient_playground(AFD);
  
  
  return 0;
}