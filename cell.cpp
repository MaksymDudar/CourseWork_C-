#include "cell.h"

/* ---------------------------------------------------------------------[<]-
Function:   cell
Synopsis:   defult constructor class cell
---------------------------------------------------------------------[>]-*/
cell::cell(){
    top = false;
    bottom = false;
    right = false;
    left = false;

    painted_border_vertical = 0;
    painted_border_horizontal = 0;

    is_painted = false;
    length_line = 99;
}

/* ---------------------------------------------------------------------[<]-
Function:   set_cell
Synopsis:   set some parameters of cell
---------------------------------------------------------------------[>]-*/
void cell::set_cell(int t, bool topparams, bool bottomparams, bool rightparams, bool leftparams){
    top = topparams;
    bottom = bottomparams;
    right = rightparams;
    left = leftparams;
    length_line = t;
}