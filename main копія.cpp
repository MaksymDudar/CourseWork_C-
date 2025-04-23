#include <iostream>
#include <iomanip>

using namespace std;

class borderCell
{
    bool isBold;

public:
    borderCell()
    {
        isBold = false;
    }
    borderCell(bool p)
    {
        isBold = p;
    }
    bool getBorder() { return isBold; }
};

class cell
{
    bool isPainted;
    int lenghtLine;
    borderCell *top;
    borderCell *bottom;
    borderCell *right;
    borderCell *left;

public:
    cell()
    {
        borderCell obj;
        top = &obj;
        bottom = &obj;
        right = &obj;
        left = &obj;

        isPainted = false;
        lenghtLine = -1;
    }

    void setcell(int t, borderCell topparams, borderCell bottomparams, borderCell rightparams, borderCell leftparams)
    {
        top = &topparams;
        bottom = &bottomparams;
        right = &rightparams;
        left = &leftparams;
        lenghtLine = t;
    }
    void setPaited(bool painted) { isPainted = painted; }

    bool getPainted() { return isPainted; }
    int getLenght() { return lenghtLine; }
    bool getLeftPaint() { return left->getBorder(); }
    bool getBottomPaint() { return bottom->getBorder(); }

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
            stream << "――";
        }
        stream << endl;
        for (int i = 0; i < obj.height; i++)
        {
            stream << "│";

            for (int t = 0; t < obj.width; t++)
            {
                char paint = obj.get(i, t).getPainted() ? '#' : ' ';
                string line = obj.get(i, t).getLeftPaint() ? "│" : "┆";

                stream << paint << line;
            }
            stream << endl;
            for (int t = 0; t < obj.width; t++)
            {
                string line = obj.get(i, t).getBottomPaint() ? "――" : "┄┄";
                stream << line;
            }
            stream << endl;
        }
        return stream;
    }
};


int main()
{
    borderCell bodrerbold(true);
    borderCell bodrernotbold(false);
    field field(10, 10);

    field.put(0, 0).setcell(4, bodrerbold, bodrerbold, bodrerbold, bodrerbold);

    cout << field;

    return 0;
}