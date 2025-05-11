#ifndef CELL
#define CELL

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

    bool get_is_painted() const { return is_painted; }

    int get_length_line() const { return length_line; }

    int get_painted_border_vertical() const { return painted_border_vertical; }
    int get_painted_border_horizontal() const { return painted_border_horizontal; }

    bool get_top() const { return top; }
    bool get_bottom() const { return bottom; }
    bool get_right() const { return right; }
    bool get_left() const { return left; }

    void set_is_painted(bool value) { is_painted = value; }

    void set_painted_border_vertical(int value) { painted_border_vertical = value; }
    void set_painted_border_horizontal(int value) { painted_border_horizontal = value; }
};

#endif
