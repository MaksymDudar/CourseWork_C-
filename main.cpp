#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <set>

using namespace std;

int g_painted = 0;

class pos
{
    int h;
    int w;
public:
    pos(int t, int p){
        h = t;
        w = p;
    }
    bool operator<(const pos &other) const
    {
        if (h == other.h)
            return w < other.w;
        return h < other.h;
    }
};
set<pos> g_not_paint_cells;

class cell
{
    bool isPainted;

public:
    int lenghtLine;
    int paintedLine;
    bool top;
    bool bottom;
    bool right;
    bool left;

    cell()
    {
        top = false;
        bottom = false;
        right = false;
        left = false;

        isPainted = false;
        lenghtLine = -1;
        paintedLine = 0;
    }

    void setcell(int t, bool topparams, bool bottomparams, bool rightparams, bool leftparams)
    {
        top = topparams;
        bottom = bottomparams;
        right = rightparams;
        left = leftparams;
        lenghtLine = t;
        paintedLine = t;
    }
    void setPaited() { isPainted = true; }

    bool getPainted() { return isPainted; }
    int getLenght() { return lenghtLine; }
    bool getLeftPaint() { return left; }
    bool getBottomPaint() { return bottom; }

    friend ostream &operator<<(ostream &stream, const cell &odj)
    {
        stream << odj.isPainted;
        return stream;
    }
};

class field
{
    int height;
    int width;
    cell **p;

public:
    field(int h, int w)
    {
        p = new cell *[h];
        for (int i = 0; i < h; ++i)
        {
            p[i] = new cell[w];
        }
        if (!p)
        {
            cout << "Allocation error\n";
            exit(1);
        }
        height = h;
        width = w;
    }

    ~field()
    {
        for (int i = 0; i < height; ++i)
        {
            delete[] p[i];
        }
        delete[] p;
    }
    cell &put(int h, int w)
    {
        if (h < 0 || h >= height || w < 0 || w >= width)
        {
            cout << "Bounds error!\n";
            exit(1);
        }
        return p[h][w];
    };
    cell &get(int h, int w) const
    {
        if (h < 0 || h >= height || w < 0 || w >= width)
        {
            cout << "Bounds error!\n";
            exit(1);
        }
        return p[h][w];
    };

    friend ostream &operator<<(ostream &stream, const field &obj)
    {
        for (int w = 0; w < obj.width; w++)
        {
            stream << "\033[1;93m――――\033[0m";
        }
        stream << endl;
        for (int i = 0; i < obj.height; i++)
        {
            stream << "\033[1;93m|\033[0m";

            for (int t = 0; t < obj.width; t++)
            {
                string paint = obj.get(i, t).getPainted() ? "\033[1;31;41m###\033[0m" : "   ";
                string line = obj.get(i, t).getLeftPaint() ? "\033[1;93m|\033[0m" : "┆";

                stream << paint << line;
            }
            stream << endl;
            for (int t = 0; t < obj.width; t++)
            {
                string line = obj.get(i, t).getBottomPaint() ? "\033[1;93m――――\033[0m" : "┄┄┄┄";
                stream << line;
            }
            stream << endl;
        }
        return stream;
    }

    friend int not_paint_area(field &fiel, int h, int w)
    {
        int count = 0;

        if (h >= 0 && h < fiel.height && w >= 0 && w < fiel.width)
        {
            pos obj(h, w);

            if (!fiel.get(h, w).getPainted() && g_not_paint_cells.find(obj) != g_not_paint_cells.end())
            {
                count++;
                g_not_paint_cells.insert(obj);
                not_paint_area(fiel, h + 1, w);
                not_paint_area(fiel, h, w + 1);
            }
            not_paint_area(fiel, h - 1, w);
            not_paint_area(fiel, h, w - 1);
        }
        return count;
    }

    friend bool border_cell(field &fiel, int h, int w)
    {
        bool isPaintNeighborTop, isPaintNeighborBottom, isPaintNeighborLeft, isPaintNeighborRight;

        if (h > 0)
        {
            isPaintNeighborTop = fiel.get(h - 1, w).getPainted();
        }
        else
        {
            isPaintNeighborTop = false;
        }
        if (h < fiel.height - 1)
        {
            isPaintNeighborBottom = fiel.get(h + 1, w).getPainted();
        }
        else
        {
            isPaintNeighborBottom = false;
        }
        if (w > 0)
        {
            isPaintNeighborLeft = fiel.get(h, w - 1).getPainted();
        }
        else
        {
            isPaintNeighborLeft = false;
        }
        if (w < fiel.width - 1)
        {
            isPaintNeighborRight = fiel.get(h, w + 1).getPainted();
        }
        else
        {
            isPaintNeighborRight = false;
        }
        if (!isPaintNeighborTop && !isPaintNeighborBottom && !isPaintNeighborLeft && !isPaintNeighborRight)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    friend bool paint(field &fiel, int h, int w)
    {
      
    }
};

int main()
{
    field field(10, 10);

    bool vert[10][11] = {
        {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1},
        {1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1}};

    bool gor[11][10] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 1, 1, 1},
        {1, 1, 1, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int num[10][10] = {
        {4, 4, 3, 3, 3, 3, 3, 3, 3, 3},
        {4, 4, 3, 3, 3, 3, 3, 3, 3, 3},
        {4, 4, 99, 99, 99, 3, 3, 99, 4, 4},
        {99, 99, 99, 99, 99, 1, 99, 99, 4, 4},
        {99, 99, 99, 1, 1, 1, 99, 99, 4, 4},
        {3, 3, 4, 4, 1, 1, 1, 99, 99, 99},
        {3, 3, 4, 4, 1, 99, 99, 99, 99, 99},
        {3, 3, 4, 2, 2, 99, 99, 99, 4, 4},
        {3, 3, 3, 2, 2, 3, 3, 3, 4, 4},
        {3, 3, 3, 2, 2, 3, 3, 3, 4, 4}};

    for (int i = 0; i < 10; i++)
    {
        for (int t = 0; t < 10; t++)
        {
            field.put(i, t).setcell(num[i][t], gor[i][t], gor[i + 1][t], vert[i][t], vert[i][t + 1]);
        }
    }
    cout << field;

    paint(field, 0, 0);

    cout << field;

    return 0;
}