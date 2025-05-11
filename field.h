#ifndef FIELD
#define FIELD

#include <iostream>
#include <set>

#include "cell.h"
#include "pos.h"

using namespace std;

extern std::set<pos> g_not_paint_cell;

class field
{
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