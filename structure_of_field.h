#ifndef STRUCTURE_OF_FIELD_H
#define STRUCTURE_OF_FIELD_H

#include <iostream>
#include <set>
using namespace std;


class pos{
    int h;
    int w;

public:
    pos() {};
    pos(int t, int p) : h(t), w(p) {};

    int get_h() { return h; };
    int get_w() const { return w; };
    void set_h(int t) { h = t; };
    void set_w(int t) { w = t; };

    bool operator<(const pos &other) const{
        return (h < other.h) || (h == other.h && w < other.w);
    }
};

class cell{
    bool is_painted;

    int length_line;
    int length_not_painted_line_in_area;

    bool painted_border_vertical;
    bool painted_border_horizontal;

    bool top;
    bool bottom;
    bool right;
    bool left;

public:
    cell();
    void set_cell(int t, bool top_params, bool bottom_params, bool right_params, bool left_params);
    friend ostream &operator<<(ostream &stream, const cell &odj);
    void increment_length_not_painted_line_in_area() { length_not_painted_line_in_area++; }
    void decrement_length_not_painted_line_in_area() { length_not_painted_line_in_area--; }

    // Getters
    bool get_is_painted() const{ return is_painted; }

    int get_length_line() const { return length_line; }
    int get_length_not_painted_line_in_area() const { return length_not_painted_line_in_area; }

    bool get_painted_border_vertical() const { return painted_border_vertical; }
    bool get_painted_border_horizontal() const { return painted_border_horizontal; }

    bool get_top() const { return top; }
    bool get_bottom() const { return bottom; }
    bool get_right() const { return right; }
    bool get_left() const { return left; }

    // Setters
    void set_is_painted(bool value) { is_painted = value; }

    void set_length_line(int value) { length_line = value; }
    void set_length_not_painted_line_in_area(int value) { length_not_painted_line_in_area = value; }

    void set_painted_border_vertical(bool value) { painted_border_vertical = value; }
    void set_painted_border_horizontal(bool value) { painted_border_horizontal = value; }

    void set_top(bool value) { top = value; }
    void set_bottom(bool value) { bottom = value; }
    void set_right(bool value) { right = value; }
    void set_left(bool value) { left = value; }
};

class field{
    int height;
    int width;
    cell **p;

    // int painted_cell_counter;

public:

    field(int h, int w);
    ~field();

    cell& put(int h, int w);
    cell& get(int h, int w) const;
    bool is_inside_field(int h, int w) const;
    bool do_not_get_neighbors(int h, int w) const;
    bool do_not_get_bold_border(int h, int w) const;
    int length_not_painted_line_in_area(int h, int w);
    bool one_bold_border_check(int h, int w);
    bool limit_of_lenght_line(int h, int w);

    int get_height() const { return height; }
    int get_width() const { return width; }

    friend ostream &operator<<(ostream &stream, const field &obj);
};

#endif 
