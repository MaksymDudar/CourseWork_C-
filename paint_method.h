#ifndef PAINT_METHOD
#define PAINT_METHOD

#include "field.h"
#include "global_state.h"


int paint(field &fiel, int h, int w);
pos paint_cell(field &fiel, int h, int w);
void clear_cell(field &fiel, int h, int w);

#endif
