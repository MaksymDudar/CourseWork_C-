#ifndef POS
#define POS

/* ---------------------------------------------------------------------[<]-
Class:     pos
Synopsis:  Represents a two-dimensional position with row (h) and column (w) coordinates.
           Provides basic getters, setters, and comparison operator for sorting or storing in containers.
Usage:     Used to identify or navigate positions on a grid (e.g., a game board or puzzle field).
---------------------------------------------------------------------[>]-*/
class pos
{
    int h, w;

public:
    pos() {};
    pos(int t, int p) : h(t), w(p) {};

    int get_h() { return h; };
    int get_w() const { return w; };
    void set_h(int t) { h = t; };
    void set_w(int t) { w = t; };

    bool operator<(const pos &other) const { return (h < other.h) || (h == other.h && w < other.w);}
};

#endif