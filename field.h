#ifndef FIELD
#define FIELD

#include <iostream>
#include <set>
#include <queue>

#include "cell.h"
#include "pos.h"

using namespace std;

extern std::set<pos> g_not_paint_cell;

/* ---------------------------------------------------------------------[<]-
Class:      field
Synopsis:   The class includes the coordinates inside, whether it is shaded,
            the maximum possible length of the line of unpainted cells
            (if it is not, then it is filled with the result of multiplying
            the length of the field by its width), the number of crossed bold
            lines with a line of unpainted cells horizontally or vertically.
            It also includes whether it is surrounded by bold borders above,
            below, right and left. Methods for working with cell variables
            have also been added.
---------------------------------------------------------------------[>]-*/
class field{
    int height;
    int width;
    cell **p;

public:
    field(int h, int w);
    field(const field &other);
    ~field();

    cell &put(int h, int w);
    cell &get(int h, int w) const;
    bool is_inside_field(int h, int w) const;
    bool do_not_get_neighbors(int h, int w) const;
    int length_not_painted_line_in_area(int h, int w);
    int not_paint_area(int start_h, int start_w);
    pos find_one_not_painted_cell();

    int get_height() const { return height; }
    int get_width() const { return width; }


    friend ostream &operator<<(ostream &stream, const field &obj);
};

#endif