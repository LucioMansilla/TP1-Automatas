#include "../libs/automata.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Automata createAutomata(List *k, List *alphabet, List **delta, int initialState,
                        List *finalStates)
{
  Automata a;
  a.k = k;
  a.alphabet = alphabet;
  a.initialState = initialState;
  a.delta = delta;
  a.finalStates = finalStates;

  return a;
}

int containsAny(List *l1, List *l2)
{
  for (int i = 0; i < l1->size; i++)
  {
    if (contains(l2, getData(l1, i)))
    {
      return 1;
    }
  }
  return 0;
}

int pertains(Automata a, char *w)
{
  int i = 0;
  List *d = lambdaClousure(a, createFrom((int[]){a.initialState}, 1));
  while (i < strlen(w) && d->size > 0)
  {
    d = move(a, d, ord(w[i]));
    d = lambdaClousure(a, d);
    i++;
  }
  return containsAny(a.finalStates, d);
}

List *move(Automata a, List *states, int symbol)
{
  List *newStates = createEmptyList();
  int lengthStates = states->size;
  int i = 0;
  while (i < lengthStates)
  {
    int state = getData(states, i);
    List nextStates = a.delta[state][symbol];
    int lengthNextStates = nextStates.size;
    int j = 0;
    while (j < lengthNextStates)
    {
      add(newStates, getData(&nextStates, j));
      j++;
    }
    i++;
  }
  return newStates;
}

List *unionAlphabet(List *alphabet_1, List *alphabet_2)
{
  List *new_alphabet = createEmptyList();
  for (int i = 0; i < alphabet_1->size; i++)
  {
    add(new_alphabet, getData(alphabet_1, i));
  }
  for (int i = 0; i < alphabet_2->size; i++)
  {
    add(new_alphabet, getData(alphabet_2, i));
  }
  return new_alphabet;
}



Automata renameStates(Automata automaton, int shift, List *new_k)
{
  Automata result;
  result.alphabet = automaton.alphabet;
  result.initialState = automaton.initialState + shift;
  result.finalStates = createEmptyList();
  int mapping[automaton.k->size];

  result.delta = (List **)malloc(sizeof(List) * automaton.k->size);
  for (int i = 0; i < automaton.k->size; i++)
  {
    if (contains(automaton.finalStates, i))
    {
      add(result.finalStates, i + shift);
    }
    mapping[i] = i + shift;
  }
  for (int i = 0; i < automaton.k->size + shift; i++)
  {
    result.delta[i] = (List *)malloc(sizeof(List) * ALPHABET_SIZE);
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      result.delta[i][j] = *createEmptyList();
    }
  }

  for (int i = 0; i < automaton.k->size; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < automaton.delta[i][j].size; k++)
      {
        add(&result.delta[i + shift][j], mapping[getData(&automaton.delta[i][j], k)]);
      }
    }
  }

  for (int i = 0; i < automaton.k->size; i++)
  {
    if (automaton.delta[i][LAMBDA].size)
    {
      for (int k = 0; k < automaton.delta[i][LAMBDA].size; k++)
      {
        add(&result.delta[i + shift][LAMBDA], mapping[getData(&automaton.delta[i][LAMBDA], k)]);
      }
    }
  }


  Automata a = createAutomata(new_k, result.alphabet, result.delta, result.initialState, result.finalStates);
  return a;
}


Automata kleene_clousure(Automata automaton)
{
  List *new_k = createK(automaton.k->size + 2);
  List *new_alphabet = automaton.alphabet;
  int new_initialState = 0;
  Automata shifteado = renameStates(automaton, 1, new_k);
  List **new_delta = (List **)malloc(sizeof(List) * (automaton.k->size + 2));

  for (int i = 0; i < automaton.k->size + 2; i++)
  {
    new_delta[i] = (List *)malloc(sizeof(List) * ALPHABET_SIZE);
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      new_delta[i][j] = *createEmptyList();
    }
  }

  add(&new_delta[0][LAMBDA], shifteado.initialState);

  for (int i = 1; i < shifteado.k->size - 1; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < shifteado.delta[i][j].size; k++)
      {
        add(&new_delta[i][j], getData(&shifteado.delta[i][j], k));
      }
    }
  }

  for (int i = 0; i < shifteado.finalStates->size; i++)
  {
    add(&new_delta[getData(shifteado.finalStates, i)][LAMBDA], shifteado.initialState);
    add(&new_delta[getData(shifteado.finalStates, i)][LAMBDA], shifteado.k->size - 1);
  }
  List *final_states = createEmptyList();
  add(final_states, shifteado.k->size - 1);
  add(&new_delta[0][LAMBDA], shifteado.k->size - 1);
  return createAutomata(new_k, new_alphabet, new_delta, new_initialState, final_states);
}


List_List *createEmptyListList()
{
  List_List *list = (List_List *)malloc(sizeof(List_List));
  list->next = NULL;
  list->size = 0;
  return list;
}

List* getList(List_List *list, int index){
  int size = list->size;
 
  while (index > size)
  {
     
    list = list->next;
   
  }
  if (list == NULL)
  {
  }
  return list->list;
}

void print_list_list(List_List *list)
{
  int size = list->size;
  List_List* curr = list->next;
   for (int i = 0; i < size; i++)
  {
    printList(curr->list);
    curr = curr->next;
  }  
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
  List *final_states = createEmptyList();
  int size = equiv_class->size;

  List_List *curr = equiv_class->next;
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < curr->list->size; j++)
    {
      if (contains(automaton.finalStates, getData(curr->list, j)))
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
  List_List *P = createEmptyListList();
  List_List *P_prime = createEmptyListList();
  bool partition_change = false;
  bool same_equivalence;
  List *K_F = createEmptyList();
  List *F = createEmptyList();
  for (int i = 0; i < automaton.k->size; i++)
  {
    if (!contains(automaton.finalStates, i))
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
        int e = getData(X_i, j);
        if (marked[e])
        {
          continue;
        }

        marked[e] = true;
        List *X_prime = createEmptyList();

        add(X_prime, e);

        for (int k = 0; k < X_i->size; k++)
        {
          int e_prime = getData(X_i, k);

          if (marked[e_prime])
          {
            continue;
          }
          same_equivalence = true;

          for (int r = 0; r < automaton.alphabet->size; r++)
          {

            int symbol = getData(automaton.alphabet, r);
            int dest_e = getData(&automaton.delta[e][symbol], 0);
            int dest_e_prime = getData(&automaton.delta[e_prime][symbol], 0);

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
      P_prime = createEmptyListList();
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
      if (getData(curr->list, j) == state)
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

  List *K = createK(equiv_class->size);
  int initial_state = get_equivalent_index(equiv_class, automaton.initialState);
  List *final_states = get_final_state_minimize(automaton, equiv_class);

  int maxTransitions = 1000;
  int transitionsCount = 0;
  Transition *transitions = (Transition *)malloc(maxTransitions * sizeof(Transition));

  int size = equiv_class->size;
  List_List *curr = equiv_class->next;
  for (int i = 0; i < size; i++)
  {
    int from = get_equivalent_index(equiv_class, getData(curr->list, 0));
    for (int j = 0; j < automaton.alphabet->size; j++)
    {
      int symbol = getData(automaton.alphabet, j);
      int to = get_equivalent_index(equiv_class, getData(&automaton.delta[getData(curr->list, 0)][symbol], 0));
      Transition temp = createTransition(from, symbol, createFrom((int[]){to}, 1));
      if (transitionsCount == maxTransitions)
      {
        maxTransitions *= 2;
        transitions = (Transition *)realloc(
            transitions, maxTransitions * sizeof(Transition));
      }
      transitions[transitionsCount] = temp;
      transitionsCount++;
    }
    curr = curr->next;
  }

  transitions[transitionsCount] = createTransition(-1, -1, NULL);
  List **delta = getDelta(transitions, K->size);

  return createAutomata(K, automaton.alphabet, delta, initial_state, final_states);
}



Automata unionA(Automata automaton_1, Automata automaton_2)
{
  int i = 0;

  List *new_k = createK(automaton_1.k->size + automaton_2.k->size + 2);

  List *new_alphabet = unionAlphabet(automaton_1.alphabet, automaton_2.alphabet);

  List *final_state = createEmptyList();

  add(final_state, new_k->size - 1);

  Automata shifteado_1 = renameStates(automaton_1, 1, new_k);

  Automata shifteado_2 = renameStates(automaton_2, automaton_1.k->size + 1, new_k);

  List **new_delta = (List **)malloc(sizeof(List) * (new_k->size));

  for (int i = 0; i < new_k->size; i++)
  {
    new_delta[i] = (List *)malloc(sizeof(List) * ALPHABET_SIZE);
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      new_delta[i][j] = *createEmptyList();
    }
  }

  add(&new_delta[0][LAMBDA], shifteado_1.initialState);
  add(&new_delta[0][LAMBDA], shifteado_2.initialState);

  for (int i = 1; i < automaton_1.k->size + 1; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < shifteado_1.delta[i][j].size; k++)
      {
        add(&new_delta[i][j], getData(&shifteado_1.delta[i][j], k));
      }
    }
  }

  int shift = automaton_1.k->size;

  for (int i = shift; i < shift + automaton_2.k->size; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < shifteado_2.delta[i][j].size; k++)
      {
        add(&new_delta[i][j], getData(&shifteado_2.delta[i][j], k));
      }
    }
  }

  for (int i = 0; i < automaton_1.finalStates->size; i++)
  {
    add(&new_delta[getData(shifteado_1.finalStates, i)][LAMBDA], new_k->size - 1);
  }

  for (int i = 0; i < shifteado_2.finalStates->size; i++)
  {
    add(&new_delta[getData(shifteado_2.finalStates, i)][LAMBDA], new_k->size - 1);
  }

  return createAutomata(new_k, new_alphabet, new_delta, 0, final_state);
}



Automata concat(Automata automaton_1, Automata automaton_2)
{

  List *new_k = createK(automaton_1.k->size + automaton_2.k->size);
  List *new_alphabet = unionAlphabet(automaton_1.alphabet, automaton_2.alphabet);
  int new_initialState = automaton_1.initialState;
  Automata automata_temp = renameStates(automaton_2, automaton_1.k->size, new_k);
  int shift = automaton_1.k->size;
  List *final_states = automata_temp.finalStates;
  printf("New size delta automata temp: %d\n", automata_temp.k->size);
  List **new_delta = (List **)malloc(sizeof(List) * (automaton_1.k->size + shift));

  for (int i = 0; i < automaton_1.k->size + shift; i++)
  {
    new_delta[i] = (List *)malloc(sizeof(List) * ALPHABET_SIZE);
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      new_delta[i][j] = *createEmptyList();
    }
  }

  for (int i = 0; i < automaton_1.k->size; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < automaton_1.delta[i][j].size; k++)
      {
        add(&new_delta[i][j], getData(&automaton_1.delta[i][j], k));
      }
    }
  }

  for (int i = shift; i < automaton_1.k->size + shift; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      for (int k = 0; k < automata_temp.delta[i][j].size; k++)
      {
        printf("Valores de i: %d, j: %d, k: %d\n", i, j, k);
        add(&new_delta[i][j], getData(&automata_temp.delta[i][j], k));
      }
    }
  }


  for (int i = 0; i < automaton_1.finalStates->size; i++)
  {
    add(&new_delta[getData(automaton_1.finalStates, i)][LAMBDA], automata_temp.initialState);
  }
  Automata new = createAutomata(new_k, new_alphabet, new_delta, new_initialState, final_states);
  printAutomata(new);

  return new;
}

List *lambdaClousure(Automata a, List *states)
{
  int visited[a.k->size][2];
  int visited_size = 0;
  List *reached = states;

  for (int i = 0; i < reached->size; i++)
  {
    int state = getData(reached, i);
    if (!isVisited(visited, state, LAMBDA, visited_size))
    {
      visited[visited_size][0] = state;
      visited[visited_size][1] = LAMBDA;
      visited_size++;

      List nextStates = a.delta[state][LAMBDA];

      for (int j = 0; j < nextStates.size; j++)
      {
        int next_data = getData(&nextStates, j);
        append(reached, next_data);
      }
    }
  }
  return reached;
}

void printAutomata(Automata a)
{
  printf("-------Automata-------\n");
  printf("K: ");
  printList(a.k);
  printf("Alphabet: ");
  printList(a.alphabet);
  printf("Delta: \n");
  for (int i = 0; i < a.k->size; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      if (a.delta[i][j].size)
      {
        printf("From %d with %c to ", i, chr(j));
        printList(&a.delta[i][j]);
      }
    }
  }
  printf("Initial state: %d\n", a.initialState);
  printf("Final states: ");
  printList(a.finalStates);
  printf("---------------------\n");
}

Automata transformAFNDtoAFD(Automata a)
{

  List *states = a.k;
  List **T = (List **)malloc(100 * sizeof(List *));

  List *Q = lambdaClousure(a, createFrom((int[]){a.initialState}, 1));

  T[0] = Q;

  List **explored = (List **)malloc(100 * sizeof(List *));
  explored[0] = Q;

  int exploredCount = 1;
  int tSize = 1;
  int delta_count = 0;
  int maxTransitions = 100;

  Transition *newTransitions =
      (Transition *)malloc(maxTransitions * sizeof(Transition));

  for (int tIndex = 0; tIndex < tSize; tIndex++)
  {
    List *s = T[tIndex];
    int alphabetSize = a.alphabet->size;
    int j = 0;
    while (j < alphabetSize)
    {
      int symbol = getData(a.alphabet, j);
      List *mov = move(a, s, symbol);
      List *U = lambdaClousure(a, mov);

      int u_index = in(U, explored, exploredCount);
      if (u_index == -1)
      {
        T[tSize] = U;
        explored[tSize] = U;
        exploredCount++;
        tSize++;
        u_index = tSize - 1;
      }
      if (symbol == LAMBDA)
      {
        j++;
        continue;
      }
      Transition temp =
          createTransition(tIndex, symbol, createFrom((int[]){u_index}, 1));
      if (delta_count == maxTransitions)
      {
        maxTransitions *= 2;
        newTransitions = (Transition *)realloc(
            newTransitions, maxTransitions * sizeof(Transition));
      }
      newTransitions[delta_count] = temp;
      delta_count++;
      j++;
    }
  }

  newTransitions[delta_count] = createTransition(-1, -1, NULL);

  int newInitialState = 0;
  List *newAlphabet = a.alphabet;
  List *newK = createK(exploredCount);

  List **newDelta = getDelta(newTransitions, newK->size);
  List *oldFinalStates = a.finalStates;

  List *newFinalStates = createEmptyList();
  for (int i = 0; i < tSize; i++)
  {
    List *s = T[i];
    Node *curr = oldFinalStates->next;
    while (curr != NULL)
    {
      if (contains(s, curr->data))
      {
        append(newFinalStates, i);
        break;
      }
      curr = curr->next;
    }
  }

  printf("T: \n");
  for (int i = 0; i < tSize; i++)
  {
    printf("T[%d]: ", i);
    printList(T[i]);
  }

  return createAutomata(newK, newAlphabet, newDelta, newInitialState,
                        newFinalStates);
}

void parserTransitions(int from, int to, int *symbols, int sizeSymbols,
                       Transition *transitions, int *transitionCount)
{
  int already_symbol_exists = 0;
  for (int i = 0; i < sizeSymbols; i++)
  {
    int symbol = symbols[i];
    for (int j = 0; j < *transitionCount; j++)
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
      transitions[*transitionCount] =
          createTransition(from, symbol, createFrom((int[]){to}, 1));
      (*transitionCount)++;
    }
  }
}



Automata readAutomatafromDot(char *filename)
{
  FILE *file = fopen(filename, "r");
  Automata a;
  int num_states = 0;
  List *finalStates = createEmptyList();
  char line[1000];
  Transition *transitions = (Transition *)malloc(100 * sizeof(Transition));
  int transitionsCount = 0;
  List *states = createEmptyList();
  List *alphabet = createEmptyList();

  while (fgets(line, sizeof(line), file) != NULL)
  {

    if (strstr(line, "inic->") != NULL)
    {
      char *token = strtok(line, "->");
      token = strtok(NULL, "->");
      a.initialState = atoi(token);
    }

    if (strstr(line, "doublecircle") != NULL)
    {
      char *token = strtok(line, "[");

      int state = atoi(token);
      append(finalStates, state);
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

      int *symbolsInt = (int *)malloc(size * sizeof(int));

      char *symbol = strtok(symbols, ",");
      int i = 0;
      while (symbol != NULL)
      {

        symbolsInt[i] = ord(*symbol);
        if (symbolsInt[i] != LAMBDA)
          append(alphabet, symbolsInt[i]);

        symbol = strtok(NULL, ",");
        i++;
      }

      parserTransitions(from, to, symbolsInt, size, transitions,
                        &transitionsCount);
    }
  }

  transitions[transitionsCount] = createTransition(-1, -1, NULL);
  List **delta = getDelta(transitions, states->size);
  a = createAutomata(states, alphabet, delta, a.initialState, finalStates);

  fclose(file);

  return a;
}

void writeAutomataToDot(Automata a, char *filename)
{
  FILE *file = fopen(filename, "w");
  fprintf(file, "digraph{\n");
  fprintf(file, "rankdir=LR;\n");
  fprintf(file, "inic[shape=point];\n");
  fprintf(file, "inic->%d;\n", a.initialState);

  for (int i = 0; i < a.k->size; i++)
  {
    for (int j = 0; j < ALPHABET_SIZE; j++)
    {
      if (a.delta[i][j].size)
      {
        for (int k = 0; k < a.delta[i][j].size; k++)
        {
          int to = getData(&a.delta[i][j], k);
          fprintf(file, "%d->%d [label=\"%c\"];\n", i, to, chr(j));
        }
      }
    }
  }

  for (int i = 0; i < a.finalStates->size; i++)
  {
    int state = getData(a.finalStates, i);
    fprintf(file, "%d[shape=doublecircle];\n", state);
  }

  fprintf(file, "}");
  fclose(file);
}
