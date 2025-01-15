#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "field.h"

// Currently creates a field, populates it, prints it and deletes it.
int main(int argc, const char** argv) {
  struct winsize wind_size;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &wind_size);
  int w = wind_size.ws_col;
  int h = wind_size.ws_row - 5;

  field_t* field = createField(w, h);
  populateField(field, w*h/7);
  for (int y = 0; y < h; ++y) {
    for (int x = 0; x < w; ++x) {
      fieldItem fi = getFieldItem(field, x, y);
      if (fi == NOBOMB) printf(".");
      else printf("B");
    }
    printf("\n");
  }
  deleteField(field);

  return 0;
}
