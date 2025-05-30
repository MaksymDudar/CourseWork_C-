#ifndef CELL
#define CELL

/* ---------------------------------------------------------------------[<]-
Class:      cell
Synopsis:   Represents a single cell in the puzzle grid. Stores its painted state, the maximum
            possible length of an unpainted line through the cell, the count of bold lines crossed
            horizontally and vertically, and flags for bold borders on each side. Provides setters
            and getters for managing these properties.
---------------------------------------------------------------------[>]-*/
class cell{
    bool is_painted;
    int length_line;

    int painted_border_vertical;
    int painted_border_horizontal;

    bool top;
    bool bottom;
    bool right;
    bool left;

public:
    cell();
    void set_cell(int t, bool top_params, bool bottom_params, bool right_params, bool left_params);
    void increment_painted_border_vertical() { painted_border_vertical++; }
    void increment_painted_border_horizontal() { painted_border_horizontal++; }

    void set_painted_border_vertical(int value) { painted_border_vertical = value; }
    void set_painted_border_horizontal(int value) { painted_border_horizontal = value; }

    void set_is_painted(bool value) { is_painted = value; }

    bool get_is_painted() const { return is_painted; }

    int get_length_line() const { return length_line; }

    int get_painted_border_vertical() const { return painted_border_vertical; }
    int get_painted_border_horizontal() const { return painted_border_horizontal; }

    bool get_top() const { return top; }
    bool get_bottom() const { return bottom; }
    bool get_right() const { return right; }
    bool get_left() const { return left; }
};

#endif
