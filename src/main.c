#include <stdio.h>
#include <stdlib.h>
#include "sandwich.h"

int main() {
  printf("Yo niggaz!\n");

  Filling one_filling[] = {FILLING_CHEESE};
  Filling two_fillings[] = {FILLING_HAM, FILLING_CHEESE};
  Filling three_filings[] = {FILLING_BUTTER, FILLING_CHEESE, FILLING_HAM};

  Sandwich* sandwiches[] = {
    make_sandwich(one_filling, 1),
    make_sandwich(two_fillings, 2),
    make_sandwich(three_filings, 3)
  };
  
  for (int i=0; i<3; ++i) {
    Sandwich* s = sandwiches[i];
    char* description = describe_sandwich(s);
    printf("Ha Haaaaa. I've made a sandwich #%d: %s\n", i, description);
    free(description);    
    sandwiches[i] = free_sandwich(s);
  }
  //getchar();
  return 0;
}

