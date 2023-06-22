#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
char *input;
int position = 0;
bool S();
bool E();
bool E_();
bool T();
bool T_();
bool F();
bool F_();
bool P();
bool L();
int main(void) { return 0; }
bool accept(char c) {
    if (input[position] == c) {
        position++;
        return true;
    }
    return false;
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
SD (L -> b) = {b}
SD (L -> c) = {c}
*/
