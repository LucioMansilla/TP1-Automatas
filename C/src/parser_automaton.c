
#include "automata.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
char *input;
int position = 0;
bool accept(char c);
Automata S();
Automata E();
Automata E_();
Automata T();
Automata T_();
Automata F();
Automata F_();
Automata P();
Automata L();
int main(void) {
    input = "(a.a.b*)#";
    if (S()) {
        printf("ACCEPT\n");
    } else {
        printf("REJECT\n");
    }
}
/*
Las funciones que generan autómatas deben estar en las reglas de producción que corresponden a las operaciones de las
expresiones regulares. En tu caso, estas son las uniones, concatenaciones y clausuras de Kleene. Aquí te dejo un ejemplo
de cómo podrías modificar tus funciones:

1. **Unión (`|`)**: La unión se realiza en la regla `E' -> | T E'`. Deberías generar un autómata en la función `E_` que
represente la unión de los autómatas generados por `T` y `E_`.

2. **Concatenación (`.`)**: La concatenación se realiza en la regla `T' -> . F T'`. Deberías generar un autómata en la
función `T_` que represente la concatenación de los autómatas generados por `F` y `T_`.

3. **Clausura de Kleene (`*`)**: La clausura de Kleene se realiza en la regla `F' -> *`. Deberías generar un autómata en
la función `F_` que represente la clausura de Kleene del autómata generado por `P`.

4. **Generación de autómatas para caracteres individuales**: Deberías generar autómatas para caracteres individuales en
la función `L`, que corresponde a las reglas `L -> a`, `L -> b` y `L -> c`.

Por último, necesitarás combinar estos autómatas en las funciones superiores de tu parser. Por ejemplo, en la función
`E`, deberías combinar los autómatas generados por `T` y `E_` de acuerdo a si la operación es una unión o una
concatenación.

Por favor, ten en cuenta que este es solo un ejemplo y que la implementación exacta dependerá de cómo estén
implementadas tus funciones para crear autómatas y realizar operaciones sobre ellos.
*/
bool accept(char c) {
    if (input[position] == c) {
        position++;
        return true;
    }
    return false;
}
Automata S() {
    if (input[position] == '(' || input[position] == 'a' || input[position] == 'b' || input[position] == 'c') {
        Automata automaton_E = E();
        if (automaton_E.k != NULL) {
            if (accept('#') && position == strlen(input)) {
                return automaton_E;
            }
        }
    }
    return null_automaton();
}
Automata E() {
    Automata automaton_T = T();
    if (automaton_T.k != NULL) {
        Automata automaton_E_ = E_();
        if (automaton_E_.k != NULL) {
            return compose(automaton_T, automaton_E_);
        }
    }
    return null_automaton();
}
Automata E_() {
    if (accept('|')) {
        Automata automaton_T = T();
        if (automaton_T.k != NULL) {
            Automata automaton_E_ = E_();
            if (automaton_E_.k != NULL) {
                return compose(automaton_T, automaton_E_);
            }
        }
    }
    return null_automaton();
}
Automata T() {
    Automata automaton_F = F();
    if (automaton_F.k != NULL) {
        Automata automaton_T_ = T_();
        if (automaton_T_.k != NULL) {
            return concat(automaton_F, automaton_T_);
        }
    }
    return null_automaton();
}
Automata T_() {
    if (accept('.')) {
        Automata automaton_F = F();
        if (automaton_F.k != NULL) {
            Automata automaton_T_ = T_();
            if (automaton_T_.k != NULL) {
                return concat(automaton_F, automaton_T_);
            }
        }
    }
    return null_automaton();
}
Automata F() {
    Automata automaton_P = P();
    if (automaton_P.k != NULL) {
        Automata automaton_F_ = F_();
        if (automaton_F_.k != NULL) {
            return kleene_clousure(automaton_P);
        } else {
            return automaton_P;
        }
    }
    return null_automaton();
}
Automata F_() {
    if (accept('*')) {
        return null_automaton();
    }
    return null_automaton();
}
Automata P() {
    if (accept('(')) {
        Automata automaton_E = E();
        if (automaton_E.k != NULL) {
            if (accept(')')) {
                return automaton_E;
            }
        }
    } else if (input[position] == 'a' || input[position] == 'b' || input[position] == 'c') {
        return L();
    }
    return null_automaton();
}
Automata L() {
    if (accept('a')) {
        return create_single_char_automaton('a');
    } else if (accept('b')) {
        return create_single_char_automaton('b');
    } else if (accept('c')) {
        return create_single_char_automaton('c');
    }
    return null_automaton();
}
/*
SD( S -> E # ) =  { ( a b c }
SD( E -> T E' ) = { ( a b c }
SD( E' -> | T E' ) = { | }
SD( E' -> LAMBDA ) = { # ) }
SD( T -> F T' )   = { ( a b c }
SD( T' -> . F T' ) = { . }
SD( T' -> LAMBDA ) = { | ) # }
SD( F -> P F' ) = { ( a b c }
SD( F' -> * ) =  { * }
SD( F' -> LAMBDA ) = { . | ) # }
SD( P -> ( E ) ) = { ( }
SD( P -> L ) = { a b c }
SD (L -> a) = {a}
SD (L -> b) = {b
}
SD (L -> c) = {c}
*/
