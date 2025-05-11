#ifndef POS
#define POS

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