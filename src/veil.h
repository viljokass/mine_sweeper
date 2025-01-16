#pragma once

#include "field.h"

static const int HIDDEN  = 2112;
static const int FLAGGED = 3113;

typedef struct t_veil_t {
  int w, h;
  int* veilItems;
  field_t* field;
} veil_t;

veil_t* createVeil(int w, int h, field_t* field);
void    deleteVeil(veil_t* veil);
void    printVeil(veil_t* veil);
int     pokeVeil(veil_t* veil, int x, int y);
void    flagVeil(veil_t* veil, int x, int y);
int     getVeilItem(veil_t* veil, int x, int y);
