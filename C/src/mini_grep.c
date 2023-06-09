#include "../libs/mini_grep.h"
#include "../libs/automata.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input;
int position = 0;

Automata parser(char *regex) {
    input = regex;
    position = 0;
    return S();
}

bool accept(char c) {
    if (input[position] == c) {
        position++;
        return true;
    }
    return false;
}

bool minigrep(char *regex, char *line) {

    int max_length = strlen(regex);
    char *regex_with_end_marker = (char *)malloc((max_length + 1) * sizeof(char));
    strcpy(regex_with_end_marker, regex);
    strcat(regex_with_end_marker, "#");

    Automata universe_automaton = parser("(a|b|c)*#");
    Automata regex_automaton = parser(regex_with_end_marker);
    Automata concat_universe_regex = concat(regex_automaton, universe_automaton);

    Automata concat_final_regex = concat(universe_automaton, concat_universe_regex);

    Automata concat_final_regex_minimized = minimize(to_AFD(concat_final_regex));
    return belongs(concat_final_regex_minimized, line);
}

//Esta función no se utiliza más. se dejan ambas versiones por ahora.
bool minigrep_sub_string(char *regex, char *line) {

    int line_length = strlen(line);
    int max_length = strlen(regex) + 2;
    char *regex_with_end_marker = (char *)malloc((max_length + 1) * sizeof(char));
    strcpy(regex_with_end_marker, regex);
    strcat(regex_with_end_marker, "#");

    input = regex_with_end_marker;
    position = 0;
    Automata regex_automaton = S();

    Automata regex_automaton_minimized = minimize(to_AFD(regex_automaton));
    free(regex_with_end_marker);

    for (int start = 0; start < line_length; start++) {
        for (int end = start + 1; end <= line_length; end++) {
            int substring_length = end - start;

            char *substring = (char *)malloc((substring_length + 1) * sizeof(char));
            memcpy(substring, &line[start], substring_length);
            substring[substring_length] = '\0';

            bool is_match = belongs(regex_automaton_minimized, substring);
            free(substring);

            if (is_match) {
                return true;
            }
        }
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

Automata P() {
    if (accept('(')) {

        Automata e = E();
        if (accept(')')) {
            return e;
        }
    } else {
        return L();
    }
    exit(1);
}

Automata F() {
    Automata p = P();
    return F_prime(p);
}

Automata F_prime(Automata f) {
    if (accept('*')) {
        return kleene_clousure(f);
    }
    return f;
}

Automata T() {
    Automata f = F();
    return T_prime(f);
}

Automata T_prime(Automata t) {
    if (input[position] == '.') {
        accept('.');
        Automata f = F();
        return T_prime(concat(t, f));
    }
    return t;
}

Automata E() {
    Automata t = T();
    return E_prime(t);
}

Automata E_prime(Automata e) {
    if (input[position] == '|') {
        accept('|');
        Automata t = T();
        return E_prime(compose(e, t));
    }
    return e;
}

Automata S() {
    Automata e = E();
    if (accept('#') && position == strlen(input)) return e;
    exit(1);
}
