#ifndef PAINT_METHOD
#define PAINT_METHOD

#include "structure_of_field.h"

extern std::set<pos> not_paint_cell;

int paint(field &fiel, int h, int w);
pos paint_cell(field &fiel, int h, int w);

#endif
