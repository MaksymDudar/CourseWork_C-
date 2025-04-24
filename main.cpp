#include <iostream>
#include <iomanip>

using namespace std;

class cell
{
    bool isPainted;
    int lenghtLine;
    int paintedLineVert;
    int paintedLineGor;
    bool top;
    bool bottom;
    bool right;
    bool left;

public:
    cell()
    {
        top = false;
        bottom = false;
        right = false;
        left = false;

        isPainted = false;
        lenghtLine = -1;
    }

    void setcell(int t, bool topparams, bool bottomparams, bool rightparams, bool leftparams)
    {
        top = topparams;
        bottom = bottomparams;
        right = rightparams;
        left = leftparams;
        lenghtLine = t;
    }
    void setPaited() { isPainted = true; }

    bool getPainted() { return isPainted; }
    int getLenght() { return lenghtLine; }
    bool getLeftPaint() { return left; }
    bool getBottomPaint() { return bottom; }

    friend ostream &operator<<(ostream &stream, cell odj)
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
    cell get(int h, int w) const
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
                string paint = obj.get(i, t).getPainted() ? "###" : "   ";
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
    friend void paint(field &fiel, int h, int w)
    {
        if (h >= 0 && h < fiel.height && w >= 0 && w < fiel.width)
        {
            bool isPaintNeighborTop = false, isPaintNeighborBottom = false, isPaintNeighborLeft = false, isPaintNeighborRight = false;

            if (h > 0)
            {
                isPaintNeighborTop = fiel.get(h - 1, w).getPainted();
            }
            if (h < fiel.height - 1)
            {
                isPaintNeighborBottom = fiel.get(h + 1, w).getPainted();
            }
            if (w > 0)
            {
                isPaintNeighborLeft = fiel.get(h, w - 1).getPainted();
            }
            if (w < fiel.width - 1)
            {
                isPaintNeighborRight = fiel.get(h , w + 1).getPainted();
            }

            if (!isPaintNeighborTop && !isPaintNeighborBottom && !isPaintNeighborLeft && !isPaintNeighborRight)
            {
                fiel.get(h, w).setPaited();
            }
        }
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
        {4, 4, -1, -1, -1, 3, 3, -1, 4, 4},
        {-1, -1, -1, -1, -1, 1, -1, -1, 4, 4},
        {-1, -1, -1, 1, 1, 1, -1, -1, 4, 4},
        {3, 3, 4, 4, -1, -1, -1, -1, -1, -1},
        {3, 3, 4, 4, -1, -1, -1, -1, -1, -1},
        {3, 3, 4, 2, 2, -1, -1, -1, 4, 4},
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

    return 0;
}