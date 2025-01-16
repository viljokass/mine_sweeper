#pragma once

// Field item enum
typedef enum t_fieldItem {
  BOMB,
  NOBOMB
} fieldItem;

// Field type struct
typedef struct t_field_t {
  int w, h;               // Field width and height
  fieldItem* fieldItems;  // List of items in field
} field_t;

field_t*  createField(int width, int height);
void      deleteField(field_t* field);
void      populateField(field_t* field, int amount);
fieldItem getFieldItem(field_t* field, int x, int y);
int       pokeField(field_t* field, int x, int y);
