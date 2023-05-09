#include "../libs/automata.h"
#include "../libs/linked_list.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  printf("\n--- Test STRING PERTAINS ---\n");

  List *k = createFrom((int[]){0, 1, 2}, 3);

  Transition transitions[] = {
      createTransition(0, ord('a'), createFrom((int[]){1, 2}, 2)),
      createTransition(0, ord('_'), createFrom((int[]){1}, 1)),
      createTransition(1, ord('b'), createFrom((int[]){2}, 1)),
      createTransition(2, ord('a'), createFrom((int[]){2}, 1)),
      createTransition(2, ord('b'), createFrom((int[]){2}, 1)),
      {-1, -1, NULL} // sentinel element
  };

  List **delta = getDelta(transitions, 4);

  Automata a = createAutomata(k, createFrom((int[]){0, 1}, 2), delta, 0,
                              createFrom((int[]){2}, 1));
  printAutomata(a);
  char test_cases[3][6] = {"ab", "abbbb", "ababab"};

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
    printf("\n--- All string pertains tests cases passed ---\n");
    return 1;
  } else {
    printf("\n--- Some string pertains tests cases failed ---\n");
    return 0;
  }
}