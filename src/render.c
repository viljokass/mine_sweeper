#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <math.h>

#include "render.h"
#include "veil.h"

#define colour_number "\033[97m"
#define colour_flag   "\033[92m"
#define colour_bomb   "\033[91m"
#define colour_reset  "\033[39m"

#define border_bg     "\033[47m"
#define cursor_bg     "\033[104m"
#define hidden_bg     "\033[100m"
#define reset_bg      "\033[49m"

int min(int a, int b) {
  if ( a < b ) return a;
  return b;
}

void renderVeil(veil_t* veil, int curs_x, int curs_y) {
  printf("\033[2J");
  struct winsize wind_size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &wind_size);
  int w = min(wind_size.ws_col - 2, veil->w);
  int h = min(wind_size.ws_row - 2, veil->h);
  for (int x = 0; x < w + 2; ++x) printf(border_bg " " reset_bg);
  for (int y = 0; y < h; ++y) {
    printf(border_bg " " reset_bg);
    for (int x = 0; x < w; ++x) {
      int item = getVeilItem(veil, x, y);
      if (item == HIDDEN) printf(hidden_bg);
      if (x == curs_x && y == curs_y) printf(cursor_bg);
      if (item == HIDDEN) printf(" ");
      else if (item == FLAGGED) printf(colour_flag "F" colour_reset);
      else if (item == -1) printf(colour_bomb "B" colour_reset);
      else if (item == 0) printf(" ");
      else if (item != HIDDEN) printf(colour_number "%d" colour_reset, item);
      printf(reset_bg);
    }
    printf(border_bg " " reset_bg "\n");
  }
  for (int x = 0; x < w + 2; ++x) printf(border_bg " " reset_bg);
  printf("\n");

}
