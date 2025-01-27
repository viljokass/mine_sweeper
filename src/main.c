#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#include "field.h"
#include "veil.h"
#include "render.h"

bool end_game(veil_t* veil, int curs_x, int curs_y) {
  revealAll(veil); 
  renderVeil(veil, curs_x, curs_y);
  printf("Unfortunately you have poked a mine.\n");
  return false;
}

bool check_win(veil_t* veil, int bomb_count, int curs_x, int curs_y) {
  int indexc = veil->w * veil->h;
  int flagged_bomb_incr = 0;
  int flag_incr = 0;
  for (int i = 0; i < indexc; ++i) {
    if (veil->veilItems[i] == FLAGGED) flag_incr++;
    if (veil->veilItems[i] == FLAGGED && veil->field->fieldItems[i] == BOMB) flagged_bomb_incr++;
  }
  if (flagged_bomb_incr != bomb_count || flag_incr != bomb_count) return true;
  revealAll(veil);
  renderVeil(veil, curs_x, curs_y);
  printf("You have flagged all the mines. Congratulations.\n");
  return false;
}

int main(int argc, const char** argv) {
  struct winsize wind_size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &wind_size);
  int w = wind_size.ws_col - 2;
  int h = wind_size.ws_row - 5;
  field_t* field = createField(w, h);
  int bomb_count = w*h/10;
  populateField(field, bomb_count);
  veil_t* veil = createVeil(w, h, field);
  char ch;
  int curs_x = 0;
  int curs_y = 0;
  renderVeil(veil, curs_x, curs_y);
  printf("wasd to move cursor, p to poke and f to flag, then enter\n");

  bool loop = true;
  while(loop) {
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
        if (poke == -1) loop = end_game(veil, curs_x, curs_y);
        break;
      }
      else if (ch == 'f') {
        flagVeil(veil, curs_x, curs_y);
        loop = check_win(veil, bomb_count, curs_x, curs_y);
        break;
      }
      else if (ch == '\n') {
        renderVeil(veil, curs_x, curs_y);
        printf("wasd to move cursor, p to poke and f to flag, then enter\n");
      }
    }
    // usleep(125*1000);
  }
  deleteVeil(veil);
  deleteField(field);
  return 0;
}
