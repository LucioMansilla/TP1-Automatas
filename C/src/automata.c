#include "../libs/automata.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Automata create_automaton(List *k, List *alphabet, List **delta, int initial_state,
                        List *final_states)
{
  Automata a;
  a.k = k;
  a.alphabet = alphabet;
  a.initial_state = initial_state;
  a.delta = delta;
  a.final_states = final_states;

  return a;
}


int belongs(Automata a, char *w)
{
  int i = 0;
  List *d = lambda_clousure(a, create_from((int[]){a.initial_state}, 1));
  while (i < strlen(w) && d->size > 0)
  {
    d = move(a, d, ord(w[i]));
    d = lambda_clousure(a, d);
    i++;
  }
  return contains_any(a.final_states, d);
}

List *move(Automata a, List *states, int symbol)
{
  List *new_states = create_empty_list();
  int length_states = states->size;
  int i = 0;
  while (i < length_states)
  {
    int state = get_data(states, i);
    List next_states = a.delta[state][symbol];
    int length_next_states = next_states.size;
    int j = 0;
    while (j < length_next_states)
    {
      add(new_states, get_data(&next_states, j));
      j++;
    }
    i++;
  }
  return new_states;
}

List *union_alphabet(List *alphabet_1, List *alphabet_2)
{
  List *new_alphabet = create_empty_list();
  for (int i = 0; i < alphabet_1->size; i++)
  {
    add(new_alphabet, get_data(alphabet_1, i));
  }
  for (int i = 0; i < alphabet_2->size; i++)
  {
    add(new_alphabet, get_data(alphabet_2, i));
  }
  return new_alphabet;
}


Automata rename_states(Automata automaton, int shift, List *new_k)
{
  Automata result;
  result.alphabet = automaton.alphabet;
  result.initial_state = automaton.initial_state + shift;
  result.final_states = create_empty_list();
  int mapping[automaton.k->size];

  result.delta = (List **)malloc(sizeof(List) * automaton.k->size);
  for (int i = 0; i < automaton.k->size; i++)
  {
    if (contains(automaton.final_states, i))
    {
      add(result.final_states, i + shift);
    }
    mapping[i] = i + shift;
  }
  for (int i = 0; i < automaton.k->size + shift; i++)
  {
    result.delta[i] = (List *)malloc(sizeof(List) * ALPHABET_SIZE);
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      result.delta[i][j] = *create_empty_list();
    }
  }

  for (int i = 0; i < automaton.k->size; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < automaton.delta[i][j].size; k++)
      {
        add(&result.delta[i + shift][j], mapping[get_data(&automaton.delta[i][j], k)]);
      }
    }
  }

  for (int i = 0; i < automaton.k->size; i++)
  {
    if (automaton.delta[i][LAMBDA].size)
    {
      for (int k = 0; k < automaton.delta[i][LAMBDA].size; k++)
      {
        add(&result.delta[i + shift][LAMBDA], mapping[get_data(&automaton.delta[i][LAMBDA], k)]);
      }
    }
  }


  Automata a = create_automaton(new_k, result.alphabet, result.delta, result.initial_state, result.final_states);
  return a;
}


Automata kleene_clousure(Automata automaton)
{
  List *new_k = create_K(automaton.k->size + 2);
  List *new_alphabet = automaton.alphabet;
  int new_initial_state = 0;
  Automata shifted_automaton = rename_states(automaton, 1, new_k);
  List **new_delta = (List **)malloc(sizeof(List) * (automaton.k->size + 2));

  for (int i = 0; i < automaton.k->size + 2; i++)
  {
    new_delta[i] = (List *)malloc(sizeof(List) * ALPHABET_SIZE);
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      new_delta[i][j] = *create_empty_list();
    }
  }

  add(&new_delta[0][LAMBDA], shifted_automaton.initial_state);

  for (int i = 1; i < shifted_automaton.k->size - 1; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < shifted_automaton.delta[i][j].size; k++)
      {
        add(&new_delta[i][j], get_data(&shifted_automaton.delta[i][j], k));
      }
    }
  }

  for (int i = 0; i < shifted_automaton.final_states->size; i++)
  {
    add(&new_delta[get_data(shifted_automaton.final_states, i)][LAMBDA], shifted_automaton.initial_state);
    add(&new_delta[get_data(shifted_automaton.final_states, i)][LAMBDA], shifted_automaton.k->size - 1);
  }
  List *final_states = create_empty_list();
  add(final_states, shifted_automaton.k->size - 1);
  add(&new_delta[0][LAMBDA], shifted_automaton.k->size - 1);
  return create_automaton(new_k, new_alphabet, new_delta, new_initial_state, final_states);
}

Automata compose(Automata automaton_1, Automata automaton_2)
{
  int i = 0;

  List *new_k = create_K(automaton_1.k->size + automaton_2.k->size + 2);

  List *new_alphabet = union_alphabet(automaton_1.alphabet, automaton_2.alphabet);

  List *final_state = create_empty_list();

  add(final_state, new_k->size - 1);

  Automata shifted_automaton_1 = rename_states(automaton_1, 1, new_k);

  Automata shifted_automaton_2 = rename_states(automaton_2, automaton_1.k->size + 1, new_k);

  List **new_delta = (List **)malloc(sizeof(List) * (new_k->size));

  for (int i = 0; i < new_k->size; i++)
  {
    new_delta[i] = (List *)malloc(sizeof(List) * ALPHABET_SIZE);
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      new_delta[i][j] = *create_empty_list();
    }
  }

  add(&new_delta[0][LAMBDA], shifted_automaton_1.initial_state);
  add(&new_delta[0][LAMBDA], shifted_automaton_2.initial_state);

  for (int i = 1; i < automaton_1.k->size + 1; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < shifted_automaton_1.delta[i][j].size; k++)
      {
        add(&new_delta[i][j], get_data(&shifted_automaton_1.delta[i][j], k));
      }
    }
  }

  int shift = automaton_1.k->size;

  for (int i = shift; i < shift + automaton_2.k->size; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < shifted_automaton_2.delta[i][j].size; k++)
      {
        add(&new_delta[i][j], get_data(&shifted_automaton_2.delta[i][j], k));
      }
    }
  }

  for (int i = 0; i < automaton_1.final_states->size; i++)
  {
    add(&new_delta[get_data(shifted_automaton_1.final_states, i)][LAMBDA], new_k->size - 1);
  }

  for (int i = 0; i < shifted_automaton_2.final_states->size; i++)
  {
    add(&new_delta[get_data(shifted_automaton_2.final_states, i)][LAMBDA], new_k->size - 1);
  }

  return create_automaton(new_k, new_alphabet, new_delta, 0, final_state);
}



Automata concat(Automata automaton_1, Automata automaton_2)
{

  List *new_k = create_K(automaton_1.k->size + automaton_2.k->size);
  List *new_alphabet = union_alphabet(automaton_1.alphabet, automaton_2.alphabet);
  int new_initial_state = automaton_1.initial_state;
  Automata automata_temp = rename_states(automaton_2, automaton_1.k->size, new_k);
  int shift = automaton_1.k->size;
  List *final_states = automata_temp.final_states;
  List **new_delta = (List **)malloc(sizeof(List) * (automaton_1.k->size + shift));

  for (int i = 0; i < automaton_1.k->size + shift; i++)
  {
    new_delta[i] = (List *)malloc(sizeof(List) * ALPHABET_SIZE);
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      new_delta[i][j] = *create_empty_list();
    }
  }

  for (int i = 0; i < automaton_1.k->size; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < automaton_1.delta[i][j].size; k++)
      {
        add(&new_delta[i][j], get_data(&automaton_1.delta[i][j], k));
      }
    }
  }

  for (int i = shift; i < automaton_1.k->size + shift; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < automata_temp.delta[i][j].size; k++)
      {
        add(&new_delta[i][j], get_data(&automata_temp.delta[i][j], k));
      }
    }
  }


  for (int i = 0; i < automaton_1.final_states->size; i++)
  {
    add(&new_delta[get_data(automaton_1.final_states, i)][LAMBDA], automata_temp.initial_state);
  }
  Automata new = create_automaton(new_k, new_alphabet, new_delta, new_initial_state, final_states);
  print_automaton(new);

  return new;
}

List *lambda_clousure(Automata a, List *states)
{
  int visited[a.k->size][2];
  int visited_size = 0;
  List *reached = states;

  for (int i = 0; i < reached->size; i++)
  {
    int state = get_data(reached, i);
    if (!is_visited(visited, state, LAMBDA, visited_size))
    {
      visited[visited_size][0] = state;
      visited[visited_size][1] = LAMBDA;
      visited_size++;

      List next_states = a.delta[state][LAMBDA];

      for (int j = 0; j < next_states.size; j++)
      {
        int next_data = get_data(&next_states, j);
        append(reached, next_data);
      }
    }
  }
  return reached;
}

void print_automaton(Automata a)
{
  printf("-------Automata-------\n");
  printf("K: ");
  print_list(a.k);
  printf("Alphabet: ");
  print_list(a.alphabet);
  printf("Delta: \n");
  for (int i = 0; i < a.k->size; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      if (a.delta[i][j].size)
      {
        printf("From %d with %c to ", i, chr(j));
        print_list(&a.delta[i][j]);
      }
    }
  }
  printf("Initial state: %d\n", a.initial_state);
  printf("Final states: ");
  print_list(a.final_states);
  printf("---------------------\n");
}

int get_equivalent_class(List_List *P, int state){
  int size = P->size;
  List_List* curr = P->next;
  for (int i = 0; i < size; i++)
  {
    if(contains(curr->list, state)){
      return i;
    }
    curr = curr->next;
  }
  return -1;
}

List * get_pi(List_List *P, int idx){
  int size = P->size;
  List_List* curr = P->next;
  for (int i = 0; i < size; i++)
  {
    if(i == idx){
      return curr->list;
    }
    curr = curr->next;
  }
  return NULL;
}


List *get_final_state_minimize(Automata automaton, List_List *equiv_class)
{
  List *final_states = create_empty_list();
  int size = equiv_class->size;

  List_List *curr = equiv_class->next;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < curr->list->size; j++)
    {
      if (contains(automaton.final_states, get_data(curr->list, j)))
      {
        add(final_states, i);
        break;
      }
    }
    curr = curr->next;
  }
  return final_states;
}

List_List *quotient_set(Automata automaton)
{
  List_List *P = create_empty_list_list();
  List_List *P_prime = create_empty_list_list();
  bool partition_change = false;
  bool same_equivalence;
  List *K_F = create_empty_list();
  List *F = create_empty_list();
  for (int i = 0; i < automaton.k->size; i++)
  {
    if (!contains(automaton.final_states, i))
    {
      add(K_F, i);
    }
    else
    {
      add(F, i);
    }
  }
  add_list_list(P, K_F);
  add_list_list(P, F);

  int marked[automaton.k->size];
  for (int i = 0; i < automaton.k->size; i++)
  {
    marked[i] = false;
  }

  while (!partition_change)
  {

    List_List *curr = P->next;
    for (int i = 0; i < automaton.k->size; i++)
    {
      marked[i] = false;
    }

    for (int i = 0; i < P->size; i++)
    {
      List *X_i = get_pi(P, i);

      for (int j = 0; j < X_i->size; j++)
      {
        int e = get_data(X_i, j);
        if (marked[e])
        {
          continue;
        }

        marked[e] = true;
        List *X_prime = create_empty_list();

        add(X_prime, e);

        for (int k = 0; k < X_i->size; k++)
        {
          int e_prime = get_data(X_i, k);

          if (marked[e_prime])
          {
            continue;
          }
          same_equivalence = true;

          for (int r = 0; r < automaton.alphabet->size; r++)
          {

            int symbol = get_data(automaton.alphabet, r);
            int dest_e = get_data(&automaton.delta[e][symbol], 0);
            int dest_e_prime = get_data(&automaton.delta[e_prime][symbol], 0);

            int class_dest_e = get_equivalent_class(P, dest_e);
            int class_dest_e_prime = get_equivalent_class(P, dest_e_prime);

            if (class_dest_e != class_dest_e_prime)
            {
              same_equivalence = false;
              break;
            }
          }

          if (same_equivalence)
          {
            marked[e_prime] = true;
            add(X_prime, e_prime);
          }
        }

        add_list_list(P_prime, X_prime);
      }
    }

    if (P->size == P_prime->size)
    {
      partition_change = true;
      break;
    }
    else
    {
      P = P_prime;
      P_prime = create_empty_list_list();
    }
  }

  return P;
}

int get_equivalent_index(List_List *P, int state)
{
  int size = P->size;
  List_List *curr = P->next;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < curr->list->size; j++)
    {
      if (get_data(curr->list, j) == state)
      {
        return i;
      }
    }
    curr = curr->next;
  }
  return -1;
}


Automata minimize(Automata automaton)
{
  List_List *equiv_class = quotient_set(automaton);

  List *K = create_K(equiv_class->size);
  int initial_state = get_equivalent_index(equiv_class, automaton.initial_state);
  List *final_states = get_final_state_minimize(automaton, equiv_class);

  int max_transitions = 1000;
  int transitions_count = 0;
  Transition *transitions = (Transition *)malloc(max_transitions * sizeof(Transition));

  int size = equiv_class->size;
  List_List *curr = equiv_class->next;
  for (int i = 0; i < size; i++)
  {
    int from = get_equivalent_index(equiv_class, get_data(curr->list, 0));
    for (int j = 0; j < automaton.alphabet->size; j++)
    {
      int symbol = get_data(automaton.alphabet, j);
      int to = get_equivalent_index(equiv_class, get_data(&automaton.delta[get_data(curr->list, 0)][symbol], 0));
      Transition temp = create_transition(from, symbol, create_from((int[]){to}, 1));
      if (transitions_count == max_transitions)
      {
        max_transitions *= 2;
        transitions = (Transition *)realloc(
            transitions, max_transitions * sizeof(Transition));
      }
      transitions[transitions_count] = temp;
      transitions_count++;
    }
    curr = curr->next;
  }

  transitions[transitions_count] = create_transition(-1, -1, NULL);
  List **delta = get_delta(transitions, K->size);

  return create_automaton(K, automaton.alphabet, delta, initial_state, final_states);
}


Automata to_AFD(Automata a)
{

  List *states = a.k;
  List **T = (List **)malloc(100 * sizeof(List *));

  List *Q = lambda_clousure(a, create_from((int[]){a.initial_state}, 1));

  T[0] = Q;

  List **explored = (List **)malloc(100 * sizeof(List *));
  explored[0] = Q;

  int explored_count = 1;
  int t_size = 1;
  int delta_count = 0;
  int max_transitions = 100;

  Transition *new_transitions =
      (Transition *)malloc(max_transitions * sizeof(Transition));

  for (int t_index = 0; t_index < t_size; t_index++)
  {
    List *s = T[t_index];
    int alphabet_size = a.alphabet->size;
    int j = 0;
    while (j < alphabet_size)
    {
      int symbol = get_data(a.alphabet, j);
      List *mov = move(a, s, symbol);
      List *U = lambda_clousure(a, mov);

      int u_index = in(U, explored, explored_count);
      if (u_index == -1)
      {
        T[t_size] = U;
        explored[t_size] = U;
        explored_count++;
        t_size++;
        u_index = t_size - 1;
      }
      if (symbol == LAMBDA)
      {
        j++;
        continue;
      }
      Transition temp =
          create_transition(t_index, symbol, create_from((int[]){u_index}, 1));
      if (delta_count == max_transitions)
      {
        max_transitions *= 2;
        new_transitions = (Transition *)realloc(
            new_transitions, max_transitions * sizeof(Transition));
      }
      new_transitions[delta_count] = temp;
      delta_count++;
      j++;
    }
  }

  new_transitions[delta_count] = create_transition(-1, -1, NULL);

  int new_initial_state = 0;
  List *new_alphabet = a.alphabet;
  List *new_k = create_K(explored_count);

  List **new_delta = get_delta(new_transitions, new_k->size);
  List *old_final_states = a.final_states;

  List *new_final_states = create_empty_list();
  for (int i = 0; i < t_size; i++)
  {
    List *s = T[i];
    Node *curr = old_final_states->next;
    while (curr != NULL)
    {
      if (contains(s, curr->data))
      {
        append(new_final_states, i);
        break;
      }
      curr = curr->next;
    }
  }

  printf("T: \n");
  for (int i = 0; i < t_size; i++)
  {
    printf("T[%d]: ", i);
    print_list(T[i]);
  }

  return create_automaton(new_k, new_alphabet, new_delta, new_initial_state,
                        new_final_states);
}

void parser_transitions(int from, int to, int *symbols, int size_symbols,
                       Transition *transitions, int *transition_count)
{
  int already_symbol_exists = 0;
  for (int i = 0; i < size_symbols; i++)
  {
    int symbol = symbols[i];
    for (int j = 0; j < *transition_count; j++)
    {
      if (transitions[j].from == from && transitions[j].symbol == symbol)
      {
        append(transitions[j].to, to);
        already_symbol_exists = 1;
        break;
      }
    }
    if (!already_symbol_exists)
    {
      transitions[*transition_count] =
          create_transition(from, symbol, create_from((int[]){to}, 1));
      (*transition_count)++;
    }
  }
}


Automata read_automaton_from_dot(char *filename)
{
  FILE *file = fopen(filename, "r");
  Automata a;
  int num_states = 0;
  List *final_states = create_empty_list();
  char line[1000];
  Transition *transitions = (Transition *)malloc(100 * sizeof(Transition));
  int transitions_count = 0;
  List *states = create_empty_list();
  List *alphabet = create_empty_list();

  while (fgets(line, sizeof(line), file) != NULL)
  {

    if (strstr(line, "inic->") != NULL)
    {
      char *token = strtok(line, "->");
      token = strtok(NULL, "->");
      a.initial_state = atoi(token);
    }

    if (strstr(line, "doublecircle") != NULL)
    {
      char *token = strtok(line, "[");

      int state = atoi(token);
      append(final_states, state);
    }

    if (strstr(line, "->") != NULL && strstr(line, "inic->") == NULL)
    {
      char lineCopy[1000];
      strcpy(lineCopy, line);
      char *token = strtok(lineCopy, "->");
      int from = atoi(token);
      int to = atoi(strtok(NULL, "->"));
      append(states, from);
      append(states, to);

      char *symbols = strtok(line, "=");
      symbols = strtok(NULL, "=");
      symbols = strtok(symbols, ";");
      symbols = strtok(symbols, "\"");

      int size = 0;
      char *temp = symbols;
      while (*temp != '\0')
      {
        if (*temp == ',')
        {
          size++;
        }
        temp++;
      }
      size++;

      int *symbols_int = (int *)malloc(size * sizeof(int));

      char *symbol = strtok(symbols, ",");
      int i = 0;
      while (symbol != NULL)
      {

        symbols_int[i] = ord(*symbol);
        if (symbols_int[i] != LAMBDA)
          append(alphabet, symbols_int[i]);

        symbol = strtok(NULL, ",");
        i++;
      }

      parser_transitions(from, to, symbols_int, size, transitions,
                        &transitions_count);
    }
  }

  transitions[transitions_count] = create_transition(-1, -1, NULL);
  List **delta = get_delta(transitions, states->size);
  a = create_automaton(states, alphabet, delta, a.initial_state, final_states);

  fclose(file);

  return a;
}

void write_automaton_to_dot(Automata a, char *filename)
{
  FILE *file = fopen(filename, "w");
  fprintf(file, "digraph{\n");
  fprintf(file, "rankdir=LR;\n");
  fprintf(file, "inic[shape=point];\n");
  fprintf(file, "inic->%d;\n", a.initial_state);

  for (int i = 0; i < a.k->size; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      if (a.delta[i][j].size)
      {
        for (int k = 0; k < a.delta[i][j].size; k++)
        {
          int to = get_data(&a.delta[i][j], k);
          fprintf(file, "%d->%d [label=\"%c\"];\n", i, to, chr(j));
        }
      }
    }
  }

  for (int i = 0; i < a.final_states->size; i++)
  {
    int state = get_data(a.final_states, i);
    fprintf(file, "%d[shape=doublecircle];\n", state);
  }

  fprintf(file, "}");
  fclose(file);
}
