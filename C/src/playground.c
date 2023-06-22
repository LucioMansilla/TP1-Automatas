#include "../libs/automata.h"
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
    input = "(a)";
    Automata a = L();
    print_automaton(a);
    printf("ACCEPT\n");
}
bool accept(char c) {
    if (input[position] == c) {
        position++;
        return true;
    }
    return false;
}

/*
bool S()
{
    if (input[position] == '(' || input[position] == 'a' || input[position] == 'b' || input[position] == 'c')
    {
        Automata final = E()
        if (final)
        {
            if (accept('#') && position == strlen(input))
            {
                return final
            }
        }
    }
    return null_automata;
}

bool E() //Si hay un error, exit, si no es que esta todo bien
{
    if (input[position] == '(' || input[position] == 'a' || input[position] == 'b' || input[position] == 'c')
    {
        T = T()
        if (AT )
        {
            E_ = E_() //me vino lambdaa utomata  o un automata.
            if (! lambda_automata(E_) )
            {
                union(T,E_)
            }
            return T;
        }
    }

    exit(1);
}

bool E_()
{
    if (accept('|'))
    {
        if (T())
        {
            if (E_())
                return union(T E_)
            return T
        }
    }
    else if (input[position] == '#' || input[position] == ')')
    {
        return lambda_automata;
    }

    exit(1);
}

bool T()
{
    if (input[position] == '(' || input[position] == 'a' || input[position] == 'b' || input[position] == 'c')
    {
        Automata F= F();
        Automata T_ = T_();
        if (T_ == null)
            {
                return F;
            }
        return concat(F,T_);
        }
    }
    exit(1);
}

bool T_()
{
    if (accept('.'))
    {
        if (F())
        {
            if (T_())
            {
                return true;
            }
        }
    }
    else if (input[position] == '|' || input[position] == '#' || input[position] == ')')
    {
        return null;
    }
    exit(1);
}

bool F()
{
    if (input[position] == '(' || input[position] == 'a' || input[position] == 'b' || input[position] == 'c')
    {
        Automapa p = P();
        {
            if (F_() == null)
            {
                return automata p;
            }else{
                return clausura_kleene(p);
            }
        }
    }
    exit(1);
}
*/

/*

Automata F_()
{
    if (accept('*'))
    {
        return lambda_automata;
    }
    else if (input[position] == '.' || input[position] == '|' || input[position] == '#' || input[position] == ')')
    {
        return null;
    }

    exit(1);
}



Automata P() {
    if (input[position] == '(') {
        if (accept('(')) {
            Automata paraentesis = create_single_char_automaton('(');
            Automata E_automata = E();
            Automata cont = concat(paraentesis, E_automata);
            {
                if (accept(')')) {
                    Automata paraentesisCierra = create_single_char_automaton(')');
                    Automata final = concat(cont, paraentesisCierra);
                    return final;
                }
            }
        }
    } else if (input[position] == 'a' || input[position] == 'b' || input[position] == 'c') {
        return L();
    }
    exit(1);
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
