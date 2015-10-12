#include <stdlib.h>
#include <glib.h>
#include "sandwich.h"

static void get_bread_top(BreadSlice *slice);
static void get_bread_bottom(BreadSlice *slice);
static inline Sandwich * sandwich_malloc(int fillings_count);
static inline void initialize_with_fillings(Sandwich *s, Filling *fs, int fc);
static const char* describe_filling(Filling *filling);

#define TOTAL_FILLINGS 3
static const char* Fillings_strings[] = {"ham", "cheese", "butter"};

struct _Sandwich {
  enum _BreadSlice top_slice;
  enum _BreadSlice bottom_slice;
  GArray *fillings;
  guint fillings_count;
 };

Sandwich * make_sandwich(Filling *fillings, int fillings_count) {
  Sandwich *result = sandwich_malloc(fillings_count);
  get_bread_top(&(result->top_slice));
  get_bread_bottom(&(result->bottom_slice));
  initialize_with_fillings(result, fillings, fillings_count);  
  return result;
}

Sandwich * sandwich_malloc(int fillings_count) {
  Sandwich *result = g_malloc(sizeof(Sandwich));
  result->fillings = g_array_sized_new(false, false, sizeof(Filling), fillings_count);
  return result;
}
  
void initialize_with_fillings(Sandwich *s, Filling *fs, int fc) {
  for (int i=0; i<fc; ++i) {
    g_array_append_val(s->fillings, *(fs + i));
  }
  s->fillings_count = fc;
}

Sandwich * free_sandwich(Sandwich *sandwich) {
  g_return_val_if_fail(sandwich, NULL);
  g_array_free(sandwich->fillings, true);
  g_free(sandwich);
  return NULL;
}

void get_bread_top(BreadSlice *slice) {
  *slice = SLICE_TOP;
}

void get_bread_bottom(BreadSlice *slice) {
  *slice = SLICE_BOTTOM;
}

bool has_filling(Sandwich *sandwich, Filling filling) {
  g_return_val_if_fail(sandwich, NULL);
  
  for (int i=0; i < sandwich->fillings_count; ++i)
    if(g_array_index(sandwich->fillings, Filling, i) == filling)
      return true;
  return false;
}

void add_filling(Sandwich *sandwich, Filling filling) {
  g_return_if_fail(sandwich);
  g_array_append_val(sandwich->fillings, filling);
  ++sandwich->fillings_count;
}

char* describe_sandwich(Sandwich *s) {
  const int fc = s->fillings_count;
  GString* buff = g_string_new(NULL);
  Filling *f;
  
  g_string_append(buff, "A tasty sandwich with ");
  for(int i=0; i < fc; i++) {
    f = &g_array_index(s->fillings, Filling, i);
    g_string_append(buff, describe_filling(f));
    if (i < fc - 2)
      g_string_append(buff, ", ");
    if (i == fc - 2)
      g_string_append(buff, " and ");
  }
  
  return g_string_free(buff, false);
}

const char* describe_filling(Filling *filling) {
  return Fillings_strings[*filling];
}

