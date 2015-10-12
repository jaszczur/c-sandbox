#include <stdlib.h>
#include <Eina.h>
#include "sandwich.h"

/**********************
 * Private prototypes *
 **********************/

static void get_bread_top(BreadSlice *slice);
static void get_bread_bottom(BreadSlice *slice);
static const char* describe_filling(Filling *filling);
static inline Sandwich * sandwich_malloc();
static inline void initialize_fillings(Sandwich *s, Filling *fs, int fc);

#define TOTAL_FILLINGS 3
static const char* Fillings_strings[] = {"ham", "cheese", "butter"};


/**********************
 * Struct definitions *
 **********************/

struct _Sandwich {
  enum _BreadSlice top_slice;
  enum _BreadSlice bottom_slice;
  Eina_Inarray *fillings;
};


/**********************
 * Public definitions *
 **********************/

Sandwich * make_sandwich(Filling *fillings, int fillings_count) {
  Sandwich *result = sandwich_malloc();
  get_bread_top(&(result->top_slice));
  get_bread_bottom(&(result->bottom_slice));
  initialize_fillings(result, fillings, fillings_count);
  return result;
}

Sandwich * free_sandwich(Sandwich *sandwich) {
  EINA_SAFETY_ON_NULL_RETURN_VAL(sandwich, NULL);
  eina_inarray_free(sandwich->fillings);
  free(sandwich);
  return NULL;
}

bool has_filling(Sandwich *sandwich, Filling filling) {
  EINA_SAFETY_ON_NULL_RETURN_VAL(sandwich, false);

  Filling *f;
  EINA_INARRAY_FOREACH(sandwich->fillings, f)
    if(*f == filling)
      return true;
  return false;
}

void add_filling(Sandwich *sandwich, Filling filling) {
  EINA_SAFETY_ON_NULL_RETURN(sandwich);
  eina_inarray_push(sandwich->fillings, &filling);
}

char* describe_sandwich(Sandwich *s) {
  EINA_SAFETY_ON_NULL_RETURN_VAL(s, NULL);
  
  Eina_Strbuf *buff = eina_strbuf_new();
  Filling *f;
  const int fc = eina_inarray_count(s->fillings);
  
  eina_strbuf_append(buff, "A tasty sandwich with ");
  for(int i=0; i < fc; i++) {
    f = eina_inarray_nth(s->fillings, i);
    eina_strbuf_append(buff, describe_filling(f));
    if (i < fc - 2)
      eina_strbuf_append(buff, ", ");
    if (i == fc - 2)
      eina_strbuf_append(buff, " and ");
  }
  
  char* result = eina_strbuf_string_steal(buff);
  eina_strbuf_free(buff);
  
  return result;
}


/***********************
 * Private definitions *
 ***********************/

Sandwich * sandwich_malloc() {
  Sandwich *result = malloc(sizeof(Sandwich));
  EINA_SAFETY_ON_NULL_RETURN_VAL(result, NULL);
  
  result->fillings = eina_inarray_new(sizeof(Filling), TOTAL_FILLINGS);
  if (!result->fillings) {
    free(result);
    return NULL;
  }

  return result;
}

void initialize_fillings(Sandwich *s, Filling *fs, int fc) {
  for (int i=0; i<fc; ++i) {
    eina_inarray_push(s->fillings, fs + i);
  }
}

void get_bread_top(BreadSlice *slice) {
  *slice = SLICE_TOP;
}

void get_bread_bottom(BreadSlice *slice) {
  *slice = SLICE_BOTTOM;
}

const char* describe_filling(Filling *filling) {
  return Fillings_strings[*filling];
}

