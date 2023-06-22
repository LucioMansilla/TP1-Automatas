#include "../libs/utils.h"
#include <stdio.h>
Transition create_transition(int from, int symbol, List *to) {
    Transition t;
    t.from = from;
    t.symbol = symbol;
    t.to = to;
    return t;
}
void print_transition(Transition t) {
    printf("From %d with %c to: ", t.from, (char)(t.symbol + DELTA_SYMBOL));
    print_list(t.to);
}