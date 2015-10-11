
#ifndef _SANDWICH_H
#define _SANDWICH_H

#include <stdbool.h>


enum _Filling {
  FILLING_HAM,
  FILLING_CHEESE,
  FILLING_BUTTER
};

enum _BreadSlice {
  SLICE_TOP,
  SLICE_BOTTOM
};

struct _Sandwich;

typedef enum _Filling Filling;
typedef enum _BreadSlice BreadSlice;
typedef struct _Sandwich Sandwich;

Sandwich * make_sandwich(Filling *fillings, int num_fillings);
Sandwich * free_sandwich(Sandwich *sandwich);
void add_filling(Sandwich *sandwich, Filling filling);
bool has_filling(Sandwich *sandwich, Filling filling);
char* describe_sandwich(Sandwich *sandwich);


#endif
