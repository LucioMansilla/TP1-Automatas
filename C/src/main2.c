

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char *input;
int position = 0;

bool accept(char c);
bool S();
bool E();
bool E_();
bool T();
bool T_();
bool F();
bool F_();
bool P();
bool L();

int main(void)
{
    input = "(a.a.b*)#";
    if (S())
    {
        printf("ACCEPT\n");
    }
    else
    {
        printf("REJECT\n");
    }
}

bool accept(char c)
{
    if (input[position] == c)
    {
        position++;
        return true;
    }
    return false;
}

bool S()
{
    if (input[position] == '(' || input[position] == 'a' || input[position] == 'b' || input[position] == 'c')
    {
        if (E())
        {
            if (accept('#') && position == strlen(input))
            {
                return true;
            }
        }
    }
    return false;
}

bool E()
{
    if (input[position] == '(' || input[position] == 'a' || input[position] == 'b' || input[position] == 'c')
    {
        if (T())
        {
            if (E_())
            {
                return true;
            }
        }
    }
    return false;
}

bool E_()
{
    if (accept('|'))
    {
        if (T())
        {
            if (E_())
            {
                return true;
            }
        }
    }
    else if (input[position] == '#' || input[position] == ')')
    {
        return true;
    }
    return false;
}

bool T()
{
    if (input[position] == '(' || input[position] == 'a' || input[position] == 'b' || input[position] == 'c')
    {
        if (F())
        {
            if (T_())
            {
                return true;
            }
        }
    }
    return false;
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
        return true;
    }
    return false;
}

bool F()
{
    if (input[position] == '(' || input[position] == 'a' || input[position] == 'b' || input[position] == 'c')
    {
        if (P())
        {
            if (F_())
            {
                return true;
            }
        }
    }
    return false;
}

bool F_()
{
    if (accept('*'))
    {
        return true;
    }
    else if (input[position] == '.' || input[position] == '|' || input[position] == '#' || input[position] == ')')
    {
        return true;
    }
    return false;
}

bool P()
{
    if (input[position] == '(')
    {
        if (accept('('))
        {
            if (E())
            {
                if (accept(')'))
                {
                    return true;
                }
            }
        }
    }
    else if (input[position] == 'a' || input[position] == 'b' || input[position] == 'c')
    {
        if (L())
        {
            return true;
        }
    }
    return false;
}

bool L()
{
    if (input[position] == 'a')
    {
        if (accept('a'))
        {
            return true;
        }
    }
    else if (input[position] == 'b')
    {
        if (accept('b'))
        {
            return true;
        }
    }
    else if (input[position] == 'c')
    {
        if (accept('c'))
        {
            return true;
        }
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
