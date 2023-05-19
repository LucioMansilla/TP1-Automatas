#include "../libs/automata.h"
#include "../libs/linked_list.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

int main(int argc, char *argv[]) {

  printf("\n--- Test PERTAINS ---\n");

  List *k = createFrom((int[]){0, 1, 2}, 3);

  Transition transitions[] = {
      createTransition(0, 0, createFrom((int[]){1, 2}, 2)),
      createTransition(0, 47, createFrom((int[]){1}, 1)),
      createTransition(1, 1, createFrom((int[]){2}, 1)),
      createTransition(2, 0, createFrom((int[]){2}, 1)),
      createTransition(2, 1, createFrom((int[]){2}, 1)),
      {-1, -1, NULL} // sentinel element
  };

  List **delta = getDelta(transitions, 4);

  Automata a = createAutomata(k, createFrom((int[]){0, 1}, 2), delta, 0,
                              createFrom((int[]){2}, 1));
  printAutomata(a);
  char test_cases[3][6] = {"01", "01111", "010101"};
  assert(pertains(a, "01") == 1);
  assert(pertains(a, "10") == 0);
  assert(pertains(a, "001") == 0);
  assert(pertains(a, "011") == 1);
  assert(pertains(a, "010") == 0);
  assert(pertains(a, "0110") == 1);

  int result = 1;
  for (int i = 0; i < 3; i++) {
    if (pertains(a, test_cases[i])) {
      printf("Test case %s passed\n", test_cases[i]);
    } else {
      printf("Test case %s failed\n", test_cases[i]);
      result = 0;
    }
  }

  if (result) {
    printf("\n--- All pertains tests cases passed ---\n");
    return 1;
  } else {
    printf("\n--- Some pertains tests cases failed ---\n");
    return 0;
  }
}