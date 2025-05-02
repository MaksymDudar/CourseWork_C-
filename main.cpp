#include <iostream>
#include <iomanip>
#include <set>

using namespace std;

int g_painted = 0;

int g_iteretions = 0;

class pos
{
public:
    int h;
    int w;
    pos(int t, int p)
    {
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
    int paintedLineVertical;
    int paintedLineHorizontal;

    bool paintedBorderVertical;
    bool paintedBorderHorizontal;

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

        paintedBorderVertical = false;
        paintedBorderHorizontal = false;

        isPainted = false;
        lenghtLine = 99;
        paintedLineVertical = 0;
        paintedLineHorizontal = 0;
    }

    void setcell(int t, bool topparams, bool bottomparams, bool rightparams, bool leftparams)
    {
        top = topparams;
        bottom = bottomparams;
        right = rightparams;
        left = leftparams;
        lenghtLine = t;
        paintedLineVertical = t;
        paintedLineHorizontal = t;
    }
    void setPaited() { isPainted = true; }
    void setPaited(bool t) { isPainted = t; }

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

    // friend int not_paint_area(field &fiel, int h, int w)
    // {
    //     int count = 0;

    //     if (h >= 0 && h < fiel.height && w >= 0 && w < fiel.width)
    //     {
    //         pos obj(h, w);

    //         if (!fiel.get(h, w).getPainted() && g_not_paint_cells.find(obj) != g_not_paint_cells.end())
    //         {
    //             count++;
    //             g_not_paint_cells.insert(obj);
    //             not_paint_area(fiel, h + 1, w);
    //             not_paint_area(fiel, h, w + 1);
    //         }
    //         not_paint_area(fiel, h - 1, w);
    //         not_paint_area(fiel, h, w - 1);
    //     }
    //     return count;
    // }

    friend int not_paint_area(field &fiel, int start_h, int start_w)
    {
        queue<pos> q;
        set<pos> visited;
        int count = 0;

        if (fiel.get(start_h, start_w).getPainted())
            return 0;

        q.push(pos(start_h, start_w));
        visited.insert(pos(start_h, start_w));

        while (!q.empty())
        {
            pos current = q.front();
            q.pop();
            count++;

            // 4 напрями
            int dh[] = {-1, 1, 0, 0};
            int dw[] = {0, 0, -1, 1};

            for (int dir = 0; dir < 4; dir++)
            {
                int nh = current.h + dh[dir];
                int nw = current.w + dw[dir];
                pos neighbor(nh, nw);

                if (nh >= 0 && nh < fiel.height && nw >= 0 && nw < fiel.width)
                {
                    if (!fiel.get(nh, nw).getPainted() && visited.find(neighbor) == visited.end())
                    {
                        visited.insert(neighbor);
                        q.push(neighbor);
                    }
                }
            }
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
            return true;
        }
        else
        {
            return false;
        }
    }

    friend int paint(field &fiel, int h, int w)
    {
        g_iteretions++;
        if (h >= 0 && h < fiel.height && w >= 0 && w < fiel.width)
        {
            bool borderCanPaint;

            if (fiel.get(h, w).left && fiel.get(h, w).paintedBorderHorizontal && w != fiel.width - 1)
            {
                borderCanPaint = false;
            }
            else if (fiel.get(h, w).bottom && fiel.get(h, w).paintedBorderVertical && h != fiel.height - 1)
            {
                borderCanPaint = false;
            }
            else
            {
                borderCanPaint = true;
            }
            
            if (fiel.get(h, w).paintedLineHorizontal != 0 && fiel.get(h, w).paintedLineVertical != 0 && borderCanPaint)
            {

                cout << h << " : " << w << endl;

                fiel.get(h, w).paintedLineVertical--;
                fiel.get(h, w).paintedLineHorizontal--;

                if (fiel.get(h, w).left)
                {
                    fiel.get(h, w).paintedBorderHorizontal = true;
                }
                if (fiel.get(h, w).bottom)
                {
                    fiel.get(h, w).paintedBorderVertical = true;
                }
                if (w < fiel.width - 1)
                {
                    fiel.get(h, w + 1).paintedBorderHorizontal = fiel.get(h, w).paintedBorderHorizontal;
                }
                if (h < fiel.height - 1)
                {
                    fiel.get(h + 1, w).paintedBorderVertical = fiel.get(h, w).paintedBorderVertical;
                }

                if (w < fiel.width - 1 && !fiel.get(h, w).left)
                {
                    fiel.get(h, w + 1).paintedLineHorizontal = min(fiel.get(h, w).paintedLineHorizontal, fiel.get(h, w + 1).lenghtLine);
                }

                if (h < fiel.height - 1 && !fiel.get(h, w).bottom)
                {
                    fiel.get(h + 1, w).paintedLineVertical = min(fiel.get(h, w).paintedLineVertical, fiel.get(h + 1, w).lenghtLine);
                }

                if (w < fiel.width - 1)
                {
                    paint(fiel, h, w + 1);
                }
                else if (h < fiel.height - 1)
                {
                    paint(fiel, h + 1, 0);
                }
                else
                {
                    cout << "Sucsesful paint.\n";
                    return 0;
                }
            }
            else
            {
                cout << h << " : " << w << endl;

                pos ret(-1, -1);
                ret = paint_cell(fiel, h, w);
                if (ret.h == -1 || ret.w == -1)
                {
                    cout << "paint_cell return error";
                    exit(1);
                }
                else
                {
                    h = ret.h;
                    w = ret.w;
                }
                paint(fiel, h, w);
            }
        }
        else
        {
            cout << "paint fiel size error";
            exit(1);
        }
        return 1;
    };

    friend pos paint_cell(field &fiel, int h, int w)
    {
        pos ret(-1, -1);
        int countNotPaintCell = not_paint_area(fiel, 0, 0);
        int countCell = countNotPaintCell + g_painted;
        int sizeArea = fiel.height * fiel.width;
        if (h >= 0 && h < fiel.height && w >= 0 && w < fiel.width)
        {
            if (!fiel.get(h, w).getPainted() && border_cell(fiel, h, w) && countCell == sizeArea)
            {
                fiel.get(h, w).setPaited();
                g_painted++;

                if (h < fiel.height - 1)
                {
                    fiel.get(h + 1, w).paintedLineVertical = fiel.get(h + 1, w).lenghtLine;
                    fiel.get(h + 1, w).paintedBorderVertical = false;
                }
                if (w < fiel.width - 1)
                {
                    fiel.get(h, w + 1).paintedLineHorizontal = fiel.get(h, w + 1).lenghtLine;
                    fiel.get(h, w + 1).paintedBorderHorizontal = false;
                }

                if (w == fiel.width - 1)
                {
                    ret.h = h + 1;
                    ret.w = 0;
                }
                else
                {
                    ret.h = h;
                    ret.w = w + 1;
                }
                cout << h << " : " << w << endl;
                cout << fiel.get(h, w).paintedBorderHorizontal << " ? " << fiel.get(h, w).paintedBorderVertical << endl;

                cout << fiel.get(h, w).paintedLineHorizontal << " | " << fiel.get(h, w).paintedLineVertical << endl;

                cout << "Paint cell" << endl;
                cout << fiel;
            }
            else if (w > 0)
            {

                if (h > 0 && !fiel.get(h - 1, w).getPainted())
                {
                    fiel.get(h, w).paintedLineVertical = min(fiel.get(h - 1, w).paintedLineVertical, fiel.get(h, w).lenghtLine);
                    fiel.get(h, w).paintedBorderVertical = fiel.get(h - 1, w).paintedBorderVertical;
                }
                else
                {
                    fiel.get(h, w).paintedLineVertical = fiel.get(h, w).lenghtLine;
                    fiel.get(h, w).paintedBorderVertical = false;
                }

                fiel.get(h, w).paintedLineHorizontal = fiel.get(h, w).lenghtLine;
                fiel.get(h, w).paintedBorderHorizontal = false;
                if (fiel.get(h, w).getPainted())
                {
                    g_painted--;
                    fiel.get(h, w).setPaited(false);
                }
                cout << "Repaint cell w" << endl;
                cout << h << " : " << w << endl;
                cout << fiel.get(h, w).paintedBorderHorizontal << " ? " << fiel.get(h, w).paintedBorderVertical << endl;

                cout << fiel.get(h, w).paintedLineHorizontal << " | " << fiel.get(h, w).paintedLineVertical << endl;

                ret = paint_cell(fiel, h, w - 1);
            }
            else if (h > 0)
            {
                if (!fiel.get(h - 1, w).getPainted())
                {
                    fiel.get(h, w).paintedLineVertical = min(fiel.get(h - 1, w).paintedLineVertical, fiel.get(h, w).lenghtLine);
                    fiel.get(h, w).paintedBorderVertical = fiel.get(h - 1, w).paintedBorderVertical;
                }
                else
                {
                    fiel.get(h, w).paintedLineVertical = fiel.get(h, w).lenghtLine;
                    fiel.get(h, w).paintedBorderVertical = false;
                }
                fiel.get(h, w).paintedLineHorizontal = fiel.get(h, w).lenghtLine;
                fiel.get(h, w).paintedBorderHorizontal = false;
                if (fiel.get(h, w).getPainted())
                {
                    g_painted--;
                    fiel.get(h, w).setPaited(false);
                }
                cout << "Repaint cell h" << endl;
                cout << h << " : " << w << endl;
                cout << fiel.get(h, w).paintedLineHorizontal << " | " << fiel.get(h, w).paintedLineVertical << endl;

                ret = paint_cell(fiel, h - 1, fiel.width - 1);
            }
            else
            {
                cout << fiel;
                cout << "No more cells to paint 364.\n";
                exit(1);
            }
        }
        else
        {
            cout << "paint_cell error";
            exit(1);
        }
        return ret;
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

    paint(field, 0, 0);

    cout << field;

    cout << g_iteretions;

    return 0;
}