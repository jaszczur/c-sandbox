#include <stdlib.h>
#include <Eina.h>
#include "sandwich.h"

static void get_bread_top(BreadSlice *slice);
static void get_bread_bottom(BreadSlice *slice);
static const char* describe_filling(Filling *filling);

#define TOTAL_FILLINGS 3
static const char* Fillings_strings[] = {"ham", "cheese", "butter"};

struct _Sandwich {
  enum _BreadSlice top_slice;
  enum _BreadSlice bottom_slice;
  Eina_Inarray *fillings;
 };

Sandwich * make_sandwich(Filling *fillings, int num_fillings) {
  Sandwich *result = malloc(sizeof(Sandwich));
  if (!result) {
    return NULL;
  }

  get_bread_top(&(result->top_slice));
  get_bread_bottom(&(result->bottom_slice));
  
  result->fillings = eina_inarray_new(sizeof(Filling), TOTAL_FILLINGS);
  if (!result->fillings) {
    free(result);
    return NULL;
  }

  for (int i=0; i<num_fillings; ++i) {
    eina_inarray_push(result->fillings, fillings + i);
  }
  
  return result;
}

Sandwich * free_sandwich(Sandwich *sandwich) {
  eina_inarray_free(sandwich->fillings);
  free(sandwich);
  return NULL;
}

void get_bread_top(BreadSlice *slice) {
  *slice = SLICE_TOP;
}

void get_bread_bottom(BreadSlice *slice) {
  *slice = SLICE_BOTTOM;
}

bool has_filling(Sandwich *sandwich, Filling filling) {
  if (sandwich == NULL)
    return false;

  Filling *f;
  EINA_INARRAY_FOREACH(sandwich->fillings, f)
    if(*f == filling)
      return true;
  return false;
}

void add_filling(Sandwich *sandwich, Filling filling) {
  eina_inarray_push(sandwich->fillings, &filling);
}

char* describe_sandwich(Sandwich *s) {
  Eina_Strbuf* buff = eina_strbuf_new();
  Filling *f;
  int num_fillings = eina_inarray_count(s->fillings);
  
  eina_strbuf_append(buff, "A tasty sandwich with ");
  for(int i=0; i < num_fillings; i++) {
    f = eina_inarray_nth(s->fillings, i);
    eina_strbuf_append(buff, describe_filling(f));
    if (i < num_fillings - 2)
      eina_strbuf_append(buff, ", ");
    if (i == num_fillings - 2)
      eina_strbuf_append(buff, " and ");
  }
  
  char* result = eina_strbuf_string_steal(buff);
  eina_strbuf_free(buff);
  
  return result;
}

const char* describe_filling(Filling *filling) {
  return Fillings_strings[*filling];
}

