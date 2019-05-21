#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#define MAXLENGTH 100 

void reset_map(int ar[], int size) { 
  int i; 
  for (i = 0; i < size; i++) { 
    ar[i] = 0; 
  } 
}

void state(int ar[], int size, char S[]) { 
  int j, k = 0; 
  for (j = 0; j < size; j++) { 
    if (ar[j] != 0) 
      S[k++] = (char)(65 + j); 
  } 
  S[k] = '\0'; 
} 


void check_closure(int ar[], char S[]) { 
  int i, j; 
  int len = strlen(S); 
  for (i = 0; i < len; i++) { 
    j = ((int)(S[i]) - 65); 
    ar[j]++; 
  } 
} 

char NFA_LIST[MAXLENGTH]; 
char buffer[MAXLENGTH]; 
int zz = 0; 

  
typedef struct DFA { 
  char *states; 
  int flag; 
} dfa; 

int last_index = 0; 
FILE *fp; 
int symbols; 

int indexing(struct DFA *dfa) { 
  int i; 
  
  for (i = 0; i < last_index; i++) { 
    if (dfa[i].flag == 0) 
      return 1; 
  } 
  return -1; 
} 

int closure(int ar[], int size) { 
  int i; 
  for (i = 0; i < size; i++) { 
    if (ar[i] == 1) 
      return i; 
  } 
  return (100); 
} 
  
void Display_closure(int states, int closure_ar[], 
                     char *closure_table[], 
                     char *NFA_TABLE[][symbols + 1], 
                     char *DFA_TABLE[][symbols]) { 
  int i; 
  for (i = 0; i < states; i++) { 
    reset_map(closure_ar, states); 
    closure_ar[i] = 2; 
  
    if (strcmp(&NFA_TABLE[i][symbols], "-") != 0) { 
   
      strcpy(buffer, &NFA_TABLE[i][symbols]); 
      check_closure(closure_ar, buffer); 
      int z = closure(closure_ar, states); 
  
      while (z != 100) 
      { 
        if (strcmp(&NFA_TABLE[z][symbols], "-") != 0) { 
          strcpy(buffer, &NFA_TABLE[z][symbols]); 
          check_closure(closure_ar, buffer); 
        } 
        closure_ar[z]++; 
        z = closure(closure_ar, states); 
      } 
    } 
  
    printf("\n e-Closure (%c) :\t", (char)(65 + i)); 
  
    bzero((void *)buffer, MAXLENGTH); 
    state(closure_ar, states, buffer); 
    strcpy(&closure_table[i], buffer); 
    printf("%s\n", &closure_table[i]); 
  } 
} 
  
int new_states(struct DFA *dfa, char S[]) { 
  
  int i;  
  for (i = 0; i < last_index; i++) { 
    if (strcmp(&dfa[i].states, S) == 0) 
      return 0; 
  } 
  strcpy(&dfa[last_index++].states, S); 
  dfa[last_index - 1].flag = 0; 
  return 1; 
} 
 
void trans(char S[], int M, char *clsr_t[], int st, 
               char *NFT[][symbols + 1], char TB[]) { 
  int len = strlen(S); 
  int i, j, k, g; 
  int arr[st]; 
  int sz; 
  reset_map(arr, st); 
  char temp[MAXLENGTH], temp2[MAXLENGTH]; 
  char *buff; 
  
  for (i = 0; i < len; i++) { 
  
    j = ((int)(S[i] - 65)); 
    strcpy(temp, &NFT[j][M]); 
  
    if (strcmp(temp, "-") != 0) { 
      sz = strlen(temp); 
      g = 0; 
  
      while (g < sz) { 
        k = ((int)(temp[g] - 65)); 
        strcpy(temp2, &clsr_t[k]); 
        check_closure(arr, temp2); 
        g++; 
      } 
    } 
  } 
  
  bzero((void *)temp, MAXLENGTH); 
  state(arr, st, temp); 
  if (temp[0] != '\0') { 
    strcpy(TB, temp); 
  } else
    strcpy(TB, "-"); 
} 
  
void Display_DFA(int last_index, struct DFA *dfa_states, 
                 char *DFA_TABLE[][symbols]) { 
  int i, j; 
  printf("\n\n********************************************************\n\n"); 
  printf("\t\t DFA TRANSITION STATE TABLE \t\t \n\n"); 
  printf("\n STATES OF DFA :\t\t"); 
  
  for (i = 1; i < last_index; i++) 
    printf("%s, ", &dfa_states[i].states); 
  printf("\n"); 
  printf("\n GIVEN SYMBOLS FOR DFA: \t"); 
  
  for (i = 0; i < symbols; i++) 
    printf("%d, ", i); 
  printf("\n\n"); 
  printf("STATES\t"); 
  
  for (i = 0; i < symbols; i++) 
    printf("|%d\t", i); 
  printf("\n"); 
  
  printf("--------+-----------------------\n"); 
  for (i = 0; i < zz; i++) { 
    printf("%s\t", &dfa_states[i + 1].states); 
    for (j = 0; j < symbols; j++) { 
      printf("|%s \t", &DFA_TABLE[i][j]); 
    } 
    printf("\n"); 
  } 
} 
  

int main() { 
  int i, j, states; 
  char T_buf[MAXLENGTH]; 
  struct DFA *dfa_states = malloc(MAXLENGTH * (sizeof(dfa))); 
  scanf("%d",&states);
  scanf("%d",&symbols);
  char state[states];
  char symbol[symbols];
  for (i = 0; i < states; i++) 
    scanf(" %c",&state[i]);
  printf("\n"); 
  
  for (i = 0; i < symbols; i++) 
    scanf(" %c",&symbol[i]);
  printf("\n\n"); 
  char *NFA_TABLE[states][symbols + 1]; 

  char *DFA_TABLE[MAXLENGTH][symbols];
  char str[1000];
  for (int i=0;i<states;++i){
  for(int j=0;j<symbols+1;++j){
    scanf(" %s",str);
    strcpy(&NFA_TABLE[i][j], str);
}
}
  printf("\n NFA STATE TRANSITION TABLE \n\n\n"); 
  printf("STATES\t"); 
  
  for (i = 0; i < symbols; i++) 
    printf("|%c\t", symbol[i]);  
  printf("|eps\t");
  
  printf("--------+------------------------------------\n"); 
  for (i = 0; i < states; i++) { 
    printf("%c\t",state[i]); 
  
    for (j = 0; j <= symbols; j++) { 
      printf("|%s \t", &NFA_TABLE[i][j]); 
    } 
    printf("\n"); 
  }
  int closure_ar[states]; 
  char *closure_table[states]; 
  
  Display_closure(states, closure_ar, closure_table, NFA_TABLE, DFA_TABLE); 
  strcpy(&dfa_states[last_index++].states, "-"); 
  
  dfa_states[last_index - 1].flag = 1; 
  bzero((void *)buffer, MAXLENGTH); 
  
  strcpy(buffer, &closure_table[0]); 
  strcpy(&dfa_states[last_index++].states, buffer); 
  
  int Sm = 1, ind = 1; 
  int start_index = 1; 
    while (ind != -1) { 
    dfa_states[start_index].flag = 1; 
    Sm = 0; 
    for (i = 0; i < symbols; i++) { 
  
      trans(buffer, i, closure_table, states, NFA_TABLE, T_buf); 
  
      strcpy(&DFA_TABLE[zz][i], T_buf); 
      Sm = Sm + new_states(dfa_states, T_buf); 
    } 
    ind = indexing(dfa_states); 
    if (ind != -1) 
      strcpy(buffer, &dfa_states[++start_index].states); 
    zz++; 
  } 
  Display_DFA(last_index, dfa_states, DFA_TABLE); 
  
  return 0; 
}
