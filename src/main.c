#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "field.h"
#include "veil.h"
#include "render.h"

void end_game(veil_t* veil, int curs_x, int curs_y) {
  for (int x = 0; x < veil->w; ++x) {
    for (int y = 0; y < veil->h; ++y) {
      pokeVeil(veil, x, y);
    }
  }
  renderVeil(veil, curs_x, curs_y);
  printf("Unfortunately you have poked a bomb.\n");
  char ch;
  while(1) {
    ch = getchar();
    if (ch == 'K') break;
  }
  exit(0);
}

// Currently creates a field, populates it, prints it and deletes it.
int main(int argc, const char** argv) {
  struct winsize wind_size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &wind_size);
  int w = wind_size.ws_col - 2;
  int h = wind_size.ws_row - 5;

  field_t* field = createField(w, h);
  populateField(field, w*h/7);
  veil_t* veil = createVeil(w, h, field);
  char ch;
  int curs_x = 0;
  int curs_y = 0;
  while(1) {
    renderVeil(veil, curs_x, curs_y);
    printf("wasd to move cursor, p to poke and f to flag.\n");
    while(1) {
      ch = getchar();
      if (ch == 'w') {
        if (curs_y > 0) {
          curs_y--;
          break;
        }
      } 
      else if (ch == 's') {
        if (curs_y < h - 1) {
          curs_y++;
          break;
        }
      }
      else if (ch == 'a') {
        if (curs_x > 0) {
          curs_x--;
          break;
        }
      }
      else if (ch == 'd') {
        if (curs_x < w - 1) {
          curs_x++;
          break;
        }
      }
      else if (ch == 'p') {
        int poke = pokeVeil(veil, curs_x, curs_y);
        if (poke == -1) end_game(veil, curs_x, curs_y);
        break;
      }
      else if (ch == 'f') {
        flagVeil(veil, curs_x, curs_y);
        break;
      }
      else break;
    }
    usleep(125*1000);
  }
  /*
  flagVeil(veil, 5, 5);
  for (int x = 0; x < 10; ++x) {
    for (int y = 0; y < 10; ++y) {
      pokeVeil(veil, x, y);
    }
  }
  */
  deleteVeil(veil);
  deleteField(field);
  return 0;
}
