#include <stdio.h>
#include <string.h>

#include "../libs/automata.h"
#include "../libs/linked_list.h"

int main(int argc, char *argv[]) {
  printf("--- Test Build from DOT ---\n");
  Automata a = readAutomatafromDot("AFND.dot");
  printAutomata(a);

  if (a.k != NULL && a.initialState == 0 && a.delta != NULL &&
      a.alphabet != NULL && a.finalStates != NULL) {
    printf("\n--- Test Build from dot Passed ---\n");
    return 1;
  } else {
    printf("\n--- Test Build from dot Failed ---\n");
    return 0;
  }
}
