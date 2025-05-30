#include "field.h"
#include "global_state.h"

using namespace std;

/* ---------------------------------------------------------------------[<]-
Function:   field
Synopsis:   Constructs a field with the given height and width, allocates memory for cells
Arguments:  h - number of rows; w - number of columns
---------------------------------------------------------------------[>]-*/
field::field(int h, int w)
{
    p = new cell *[10];
    if (!p)
    {
        cout << "Allocation error\n";
        exit(1);
    }
    for (int i = 0; i < h; ++i)
    {
        p[i] = new cell[10];
        if (!p[i])
        {
            cout << "Allocation error\n";
            exit(1);
        }
    }
    height = h;
    width = w;
}

/* ---------------------------------------------------------------------[<]-
Function:   field (copy constructor)
Synopsis:   Creates a deep copy of another field object
Arguments:  other - the field object to copy
---------------------------------------------------------------------[>]-*/
field::field(const field &other){
    height = other.height;
    width = other.width;
    p = new cell *[height];
    for (int i = 0; i < height; ++i){
        p[i] = new cell[width];
        for (int j = 0; j < width; ++j){
            p[i][j] = other.p[i][j];
        }
    }
}

/* ---------------------------------------------------------------------[<]-
Function:   ~field
Synopsis:   Destructor, deallocates all dynamically allocated memory
---------------------------------------------------------------------[>]-*/
field::~field(){
    if (p != nullptr)
    {
        for (int i = 0; i < height; ++i)
        {
            delete[] p[i];
        }
        delete[] p;
        p = nullptr;
    }
}

/* ---------------------------------------------------------------------[<]-
Function:   put
Synopsis:   Returns a reference to the cell at (h, w) for modification
Arguments:  h - row index; w - column index
Returns:    Reference to the cell at the specified position
Note:       Exits if the position is out of bounds
---------------------------------------------------------------------[>]-*/
cell &field::put(int h, int w)
{
    if (!is_inside_field(h, w))
    {
        cout << "Bounds error!\n";
        exit(1);
    }
    return p[h][w];
};

cell &field::get(int h, int w) const
{
    if (!is_inside_field(h, w))
    {
        cout << "Bounds error!\n";
        exit(1);
    }
    return p[h][w];
}

/* ---------------------------------------------------------------------[<]-
Function:   operator<<
Synopsis:   Overloads the output stream operator to print the field
Arguments:  stream - output stream; obj - the field to print
Returns:    Modified output stream with field representation
---------------------------------------------------------------------[>]-*/
ostream &operator<<(ostream &stream, const field &obj){
    for (int w = 0; w < obj.width; w++){
        stream << "\033[1;93m――――\033[0m";
    }
    stream << endl;
    for (int i = 0; i < obj.height; i++){
        stream << "\033[1;93m|\033[0m";
        for (int t = 0; t < obj.width; t++){
            string line = obj.get(i, t).get_left() ? "\033[1;93m|\033[0m" : "┆";
            string paint;

            if (obj.get(i, t).get_is_painted()){
                paint = "\033[1;41m";
                if (obj.get(i, t).get_length_line() != obj.get_height() * obj.get_width()){
                    paint += to_string(obj.get(i, t).get_length_line()) + "  ";
                } else {
                    paint += "   ";
                }
                paint += "\033[0m";
            } else {
                if (obj.get(i, t).get_length_line() != obj.get_height() * obj.get_width())
                {
                    paint = to_string(obj.get(i, t).get_length_line()) + "  ";
                }
                else
                {
                    paint += "   ";
                }
            }
            stream << paint << line;
            }
        stream << endl;
        for (int t = 0; t < obj.width; t++){
            string line = obj.get(i, t).get_bottom() ? "\033[1;93m――――\033[0m" : "┄┄┄┄";
            stream << line;
        }
        stream << endl;
    }
    return stream;
}

/* ---------------------------------------------------------------------[<]-
Function:   is_inside_field
Synopsis:   Checks whether the given coordinates are within field boundaries
Arguments:  h - row index; w - column index
Returns:    true if inside, false otherwise
---------------------------------------------------------------------[>]-*/
bool field::is_inside_field(int h, int w) const
{
    return (h >= 0 && h < height && w >= 0 && w < width) ? true : false;
}

/* ---------------------------------------------------------------------[<]-
Function:   do_not_get_neighbors
Synopsis:   Checks whether the cell at (h, w) has any painted neighbors
Arguments:  h - row index; w - column index
Returns:    true if there are no painted neighbors, false otherwise
---------------------------------------------------------------------[>]-*/
bool field::do_not_get_neighbors(int h, int w) const
{
    bool top_neighbors = (h > 0) ? get(h - 1, w).get_is_painted() : false;
    bool bottom_neighbors = (h < height - 1) ? get(h + 1, w).get_is_painted() : false;
    bool left_neighbors = (w > 0) ? get(h, w - 1).get_is_painted() : false;
    bool right_neighbors = (w < width - 1) ? get(h, w + 1).get_is_painted() : false;

    return !top_neighbors && !bottom_neighbors && !left_neighbors && !right_neighbors;
}

/* ---------------------------------------------------------------------[<]-
Function:   length_not_painted_line_in_area
Synopsis:   Calculates the size of the unpainted area connected to cell (h, w)
Arguments:  h - row index; w - column index
Returns:    Number of connected unpainted cells
Note:       Only includes cells not marked as paintable in g_not_paint_cell
---------------------------------------------------------------------[>]-*/
int field::length_not_painted_line_in_area(int h, int w){
    queue<pos> q;
    set<pos> visited;
    int count = 0;

    if (!is_inside_field(h, w))
    {
        cout << "Bounds error!\n";
        return 0;
    }

    if (get(h, w).get_is_painted())
        return 0;

    q.push(pos(h, w));
    visited.insert(pos(h, w));

    while (!q.empty())
    {
        pos current = q.front();
        q.pop();
        count++;

        int dh[] = {-1, 1, 0, 0};
        int dw[] = {0, 0, -1, 1};

        for (int dir = 0; dir < 4; dir++){
            int nh = current.get_h() + dh[dir];
            int nw = current.get_w() + dw[dir];
            pos neighbor(nh, nw);

            if (!is_inside_field(nh, nw))
                continue;
            if (get(nh, nw).get_is_painted())
                continue;
            if (!g_not_paint_cell.count(neighbor))
                continue;
            if (visited.find(neighbor) != visited.end())
                continue;

            bool can_pass = false;
            switch (dir){
            case 0:
                can_pass = !get(current.get_h(), current.get_w()).get_top();
                break; // top
            case 1:
                can_pass = !get(current.get_h(), current.get_w()).get_bottom();
                break; // bottom
            case 3:
                can_pass = !get(current.get_h(), current.get_w()).get_left();
                break; // left
            case 2:
                can_pass = !get(current.get_h(), current.get_w()).get_right();
                break; // right
            }

            if (can_pass)
            {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }

    return count;
}

/* ---------------------------------------------------------------------[<]-
Function:   not_paint_area
Synopsis:   Counts the number of unpainted cells in a connected area
Arguments:  start_h - starting row; start_w - starting column
Returns:    Size of the unpainted connected component
---------------------------------------------------------------------[>]-*/
int field::not_paint_area(int start_h, int start_w){
    queue<pos> q;
    set<pos> visited;
    int count = 0;

    if (start_h < 0 || start_h >= height || start_w < 0 || start_w >= width)
    {
        cout << "122";
        return 0;
    }

    if (get(start_h, start_w).get_is_painted())
        return 0;

    q.push(pos(start_h, start_w));
    visited.insert(pos(start_h, start_w));

    while (!q.empty())
    {
        pos current = q.front();
        q.pop();
        count++;

        int dh[] = {-1, 1, 0, 0};
        int dw[] = {0, 0, -1, 1};

        for (int dir = 0; dir < 4; dir++)
        {
            int nh = current.get_h() + dh[dir];
            int nw = current.get_w() + dw[dir];
            pos neighbor(nh, nw);

            if (nh >= 0 && nh < height && nw >= 0 && nw < width)
            {
                if (!get(nh, nw).get_is_painted() && visited.find(neighbor) == visited.end()){
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
    }

    return count;
}

/* ---------------------------------------------------------------------[<]-
Function:   find_one_not_painted_cell
Synopsis:   Searches for the first unpainted cell in the field
Returns:    Position of the found cell or (-1, -1) if none found
---------------------------------------------------------------------[>]-*/
pos field::find_one_not_painted_cell(){
    pos req;
    for (int i = 0; i < get_height(); i++){
        for (int t = 0; t < get_width(); t++){
            if (!get(i, t).get_is_painted()){
                req.set_h(i);
                req.set_w(t);
                return req;
            }
        }
    }
    req.set_h(-1);
    req.set_w(-1);
    return req;
};