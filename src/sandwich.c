#include <stdlib.h>
#include <glib.h>
#include "sandwich.h"

static void get_bread_top(BreadSlice *slice);
static void get_bread_bottom(BreadSlice *slice);
static const char* describe_filling(Filling *filling);

#define TOTAL_FILLINGS 3
static const char* Fillings_strings[] = {"ham", "cheese", "butter"};

struct _Sandwich {
  enum _BreadSlice top_slice;
  enum _BreadSlice bottom_slice;
  GArray *fillings;
  guint fillings_len;
 };

Sandwich * make_sandwich(Filling *fillings, int num_fillings) {
  Sandwich *result = malloc(sizeof(Sandwich));
  if (!result) {
    return NULL;
  }

  get_bread_top(&(result->top_slice));
  get_bread_bottom(&(result->bottom_slice));
  
  result->fillings = g_array_sized_new(false, false, sizeof(Filling), num_fillings);
  if (!result->fillings) {
    free(result);
    return NULL;
  }

  for (int i=0; i<num_fillings; ++i) {
    g_array_append_val(result->fillings, *(fillings + i));
  }
  result->fillings_len = num_fillings;
  
  return result;
}

Sandwich * free_sandwich(Sandwich *sandwich) {
  g_array_free(sandwich->fillings, true);
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
  
  for (int i=0; i < sandwich->fillings_len; ++i)
    if(g_array_index(sandwich->fillings, Filling, i) == filling)
      return true;
  return false;
}

void add_filling(Sandwich *sandwich, Filling filling) {
  g_array_append_val(sandwich->fillings, filling);
  ++sandwich->fillings_len;
}

char* describe_sandwich(Sandwich *s) {
  GString* buff = g_string_new(NULL);
  Filling *f;
  int num_fillings = s->fillings_len;
  
  g_string_append(buff, "A tasty sandwich with ");
  for(int i=0; i < num_fillings; i++) {
    f = &g_array_index(s->fillings, Filling, i);
    g_string_append(buff, describe_filling(f));
    if (i < num_fillings - 2)
      g_string_append(buff, ", ");
    if (i == num_fillings - 2)
      g_string_append(buff, " and ");
  }
  
  return g_string_free(buff, false);
}

const char* describe_filling(Filling *filling) {
  return Fillings_strings[*filling];
}

