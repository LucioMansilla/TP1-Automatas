#include "../libs/automata.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char *input;
int position = 0;
bool accept(char c);
Automata K();
Automata P();
Automata L();
Automata S();
bool kleene = false;
bool nulo = false;


int main(void) {

    input = "(b)#";
    Automata a = S();
    print_automaton(a);
}

bool accept(char c) {
    if (input[position] == c) {
        position++;
        return true;
    }
    return false;
}

Automata L() {
    if (accept('a'))
        return create_single_char_automaton('a');
    else if (accept('b'))
        return create_single_char_automaton('b');
    else if (accept('c'))
        return create_single_char_automaton('c');
    exit(1);
}

Automata K() {
    if (input[position] == 'a' || input[position] == 'b' || input[position] == 'c') {
        return L();
    } else
        exit(1);
}

Automata P() {
    if (accept('(')) {
        Automata k = K();
        if (accept(')')) {
            Automata openParenthesis = create_single_char_automaton('k');
            Automata closeParenthesis = create_single_char_automaton('z');
            Automata concatenated = concat(openParenthesis, k);
            return concat(concatenated, closeParenthesis);
        }
    } else if (input[position] == 'a' || input[position] == 'b' || input[position] == 'c') {
        return L();
    }
    exit(1);
}

Automata S() { 
    if (input[position] == 'a' || input[position] == 'b' || input[position] == 'c' || input[position] == '('){
        Automata p = P();
        if (accept('#'))
            return p;
    }
    exit(1);
}


