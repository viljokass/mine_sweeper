#include <stdlib.h>
#include <time.h>
#include "field.h"

/* Field creator function.
PARAMS:
  int width - the width of the field
  int height - the height of the field
RETURNS:
  pointer to the field struct, which hold the bombs or no-bomb fields.
*/
field_t* createField(int width, int height) {
  field_t* field = malloc(sizeof(field));
  field->w = width;
  field->h = height;
  field->fieldItems = malloc(width * height * sizeof(fieldItem));
  for (int i = 0; i < width*height; ++i) {
    field->fieldItems[i] = NOBOMB;
  }
  return field;
}

/* Field deletor function.
PARAMS:
  field_t* field - pointer to the field that is to be deleted.
RETURNS:
  none
*/
void deleteField(field_t* field) {
  free(field->fieldItems);
  free(field);
}

/* Field populator function
PARAMS:
  field_t* field - field to be populated with MINES
  int amount - the amount of mines to be thrown on the field
RETURNS:
  none
*/
void populateField(field_t* field, int amount) {
  // Seed the random generator with time
  srand(time(NULL));
  int amount_left = amount;
  int x, y;
  while (amount_left > 0) {
    // Modulo operator forces the items to be within bounds.
    x = rand()%field->w;
    y = rand()%field->h;
    if (getFieldItem(field, x, y) == NOBOMB) {
      --amount_left;
      field->fieldItems[x + y * field->w] = BOMB;
    }
  } 
}

/* FieldItem getter
PARAMS:
  field_t* field - field to be gotten from
  int x, y - coords.
RETURNS:
  the gotten fielditem.
*/
fieldItem getFieldItem(field_t* field, int x, int y) {
  if (x < 0 || x > field->w - 1) return NOBOMB;
  if (y < 0 || y > field->h - 1) return NOBOMB;
  return field->fieldItems[x + y * field->w];
}

/* Poke the field
PARAMS:
  field_t* field - field to be poked
  int x, y - poke coords
RETURNS:
  -1 if poked a bomb
  otherwise, the count of bombs in the items surrounding it
*/
int pokeField(field_t* field, int x, int y) {
  if (getFieldItem(field, x, y) == BOMB) return -1;
  int bombs = 0;
  for (int dy = -1; dy < 2; ++dy) {
    for (int dx = -1; dx < 2; ++dx) {
      if (getFieldItem(field, x+dx, y+dy) == BOMB) bombs++;
    }
  }
  return bombs;
}
