#pragma once

typedef enum t_fieldItem {
  BOMB,
  NOBOMB
} fieldItem;

typedef struct t_field_t {
  int w;
  int h;
  fieldItem* fieldItems;
} field_t;

field_t*  createField(int width, int height);
void      deleteField(field_t* field);
void      populateField(field_t* field, int amount);
fieldItem getFieldItem(field_t* field, int x, int y);
