#ifndef GLOBAL_STATE
#define GLOBAL_STATE

#include <set>
#include "pos.h"

#define NUM_OF_BOLD_LINE_CAN_CROSS 1
#define FIELD_SIZE_6 6
#define FIELD_SIZE_10 10
#define WIDTH 70

extern std::set<pos> g_not_paint_cell;
extern int g_paint_counter;
extern int g_counter_iteration;

//Array 
// 10x10 Array
extern bool vert10x10[FIELD_SIZE_10][FIELD_SIZE_10 + 1];
extern bool gor10x10[FIELD_SIZE_10 + 1][FIELD_SIZE_10];
extern int num10x10[FIELD_SIZE_10][FIELD_SIZE_10];

#endif