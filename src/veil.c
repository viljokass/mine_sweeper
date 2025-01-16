#include "veil.h"
#include <stdio.h>
#include <stdlib.h>

void crawl(veil_t* veil, int x, int y);

/* Create a veil for a field
PARAMS:
  int width - the width of the veil
  int height - the height of the veil
  field_t* field - pointer to the field which we'll attach to the veil
RETURNS:
  pointer to the veil struct
*/
veil_t* createVeil(int w, int h, field_t* field) {
  veil_t* veil = malloc(sizeof(veil));
  veil->w = w;
  veil->h = h;
  veil->field = field;
  veil->veilItems = malloc(w * h * sizeof(int));
  for (int i = 0; i < w * h; ++i) veil->veilItems[i] = HIDDEN;
  return veil;
}

/* Delete veil
PARAMS:
  veil_t* veil - the veil to be deleted
RETURNS:
  none
*/
void deleteVeil(veil_t* veil) {
  free(veil->veilItems);
  free(veil);
}

/* Print veil
PARAMS:
  veil_t* veil - the veil to be printed.
RETURNS:
  none
*/
void printVeil(veil_t* veil) {
  int w = veil->w;
  int h = veil->h;
  for (int x = 0; x < w + 2; ++x) printf("#");
  for (int y = 0; y < h; ++y) {
    printf("#");
    for (int x = 0; x < w; ++x) {
      int item = veil->veilItems[x + w * y];
      if (item == HIDDEN) printf("X");
      else if (item == FLAGGED) printf("F");
      else if (item == -1) printf("B");
      else printf("%d", item);
    }
    printf("#\n");
  }
  for (int x = 0; x < w + 2; ++x) printf("#");
  printf("\n");
}

/* Poke the veil
PARAMS:
  veil_t* veil - the veil to be poked
  int x, y - the poke coords
RETURNS:
  -1 if poked a bomb
   1 if didn't poke a bomb
*/
int pokeVeil(veil_t* veil, int x, int y) {
  int index = x + veil->w * y;
  // We've poked this already, no reason to poke it again
  if (veil->veilItems[index] != HIDDEN) {
    return 1;
  }
  int res = pokeField(veil->field, x, y);
  // Oh no, we poked a bomb!
  if (res == -1) {
    veil->veilItems[index] = res;
    return -1;
  }
  // We didn't poke a bomb.
  if (res == 0) {
    crawl(veil, x, y);
    return 1;
  }
  veil->veilItems[index] = res;
  return 1;
}

/* Flag a veil item
PARAMS:
  veil to be flagged,
  coordinates of the flagging
RETURNS:
  none
*/
void flagVeil(veil_t* veil, int x, int y) {
  int index = x + veil->w * y;
  if (veil->veilItems[index] == HIDDEN) {
    veil->veilItems[index] = FLAGGED;
  }
  else if (veil->veilItems[index] == FLAGGED) {
    veil->veilItems[index] = HIDDEN;
  }
}

/* Getter for veil item
PARAMS:
  veil to be gotten from and coordinates of getting
RETURNS:
  none
*/
int getVeilItem(veil_t* veil, int x, int y) {
  if (x < 0 || x > veil->w - 1) return 0;
  if (y < 0 || y > veil->h - 1) return 0;
  return veil->veilItems[x + veil->w * y];
}

// Recursive crawler function to show large areas of empty field
void crawl(veil_t* veil, int x, int y) {
  int current_veil_index = x + veil->w * y;
  if (x < 0 || x > veil->w - 1) return;
  if (y < 0 || y > veil->h - 1) return;
  // No need to crawl on this one, we've already done that
  if (veil->veilItems[current_veil_index] != HIDDEN) return;
  int res = pokeField(veil->field, x, y);
  if (res == 0) {
    veil->veilItems[current_veil_index] = 0;
    crawl(veil, x-1, y);    crawl(veil, x+1, y);
    crawl(veil, x, y-1);    crawl(veil, x, y+1);
    crawl(veil, x-1, y-1);  crawl(veil, x-1, y+1);
    crawl(veil, x+1, y-1);  crawl(veil, x+1, y+1);
  }
  if (res != -1) {
    veil->veilItems[current_veil_index] = res;
  }
}
