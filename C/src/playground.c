#include "../libs/automata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    //test renameStates
    char *in_file = argv[1];
    char *out_file = argv[2];

    Automata AFND = readAutomatafromDot(in_file);
  //  Automata AFND2 = readAutomatafromDot(in_file);
    printAutomata(AFND);
    printf("Now the other: \n");
    //printAutomata(AFND2);

//    Automata concated = concat(AFND, AFND2);
    Automata kleeneado = kleene_clousure(AFND);
    printf("KLENEADO ------------------\n");
   // printAutomata(concated);
   printAutomata(kleeneado);

}