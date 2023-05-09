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
  printf("Se ha completado la conversión AFND a AFD.\n");
  printf("Puede ver el resultado en el archivo %s\n", out_file);

  return 0;
}