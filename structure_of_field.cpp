#include "structure_of_field.h"
#include "paint_method.h"

#include <set>

using namespace std;

cell::cell(){
    top = false;
    bottom = false;
    right = false;
    left = false;

    painted_border_vertical = false;
    painted_border_horizontal = false;

    is_painted = false;
    length_line = 99;
    length_not_painted_line_in_area = 0;
}

void cell::set_cell(int t, bool topparams, bool bottomparams, bool rightparams, bool leftparams){
    top = topparams;
    bottom = bottomparams;
    right = rightparams;
    left = leftparams;
    length_line = t;
}

ostream &operator<<(ostream &stream, const cell &odj){
    stream << odj.is_painted;
    return stream;
}


// Field

field::field(int h, int w)  {
    p = new cell *[10];
    if (!p){
        cout << "Allocation error\n";
        exit(1);
    }
    for (int i = 0; i < h; ++i){
        p[i] = new cell[10];
        if (!p[i]){
            cout << "Allocation error\n";
            exit(1);
        }
    }
    height = h;
    width = w;
}

field::~field(){
    for (int i = 0; i < height; ++i){
        delete[] p[i];
    }
    delete[] p;
}



cell& field::put(int h, int w){
    if (!is_inside_field(h, w)){
        cout << "Bounds error!\n";
        exit(1);
    }
    return p[h][w];
};

cell &field::get(int h, int w) const {
    if (!is_inside_field(h, w)){
        cout << "Bounds error!\n";
        exit(1);
    }
    return p[h][w];
}

ostream &operator<<(ostream &stream, const field &obj){
    for (int w = 0; w < obj.width; w++){
        stream << "\033[1;93m――――\033[0m";
    }
    stream << endl;
    for (int i = 0; i < obj.height; i++){
        stream << "\033[1;93m|\033[0m";
        for (int t = 0; t < obj.width; t++){
            string paint = obj.get(i, t).get_is_painted() ? "\033[1;31;41m###\033[0m" : "   ";
            string line = obj.get(i, t).get_left() ? "\033[1;93m|\033[0m" : "┆";
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


bool field::is_inside_field(int h, int w) const {
    return (h >= 0 && h < height && w >= 0 && w < width) ? true : false;
}

bool field::do_not_get_neighbors(int h, int w) const{
    bool top_neighbors = (h > 0) ? get(h - 1, w).get_is_painted() : false;
    bool bottom_neighbors = (h < height - 1) ? get(h + 1, w).get_is_painted() : false;
    bool left_neighbors = (w > 0) ? get(h, w - 1).get_is_painted() : false;
    bool right_neighbors = (w < width - 1) ? get(h, w + 1).get_is_painted() : false;

    return !top_neighbors && !bottom_neighbors && !left_neighbors && !right_neighbors;
}

bool field::do_not_get_bold_border(int h, int w) const{
    return !get(h, w).get_right() && !get(h, w).get_left() && !get(h, w).get_top() && !get(h, w).get_bottom();
}

bool field::one_bold_border_check(int h, int w){
    if(is_inside_field(h,w)){
        if (get(h, w).get_left() && get(h, w).get_painted_border_horizontal() && w != width - 1) {
            return false;
        } else if (get(h, w).get_bottom() && get(h, w).get_painted_border_vertical() && h != height - 1) {
            return false;
        } else {
            return true;
        }
    }else{
        cout << "Bounds error!\n";
        exit(1);
    }
}

int field::length_not_painted_line_in_area(int h, int w)
{
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

        for (int dir = 0; dir < 4; dir++)
        {
            int nh = current.get_h() + dh[dir];
            int nw = current.get_w() + dw[dir];
            pos neighbor(nh, nw);

            if (!is_inside_field(nh, nw))
                continue;
            if (get(nh, nw).get_is_painted())
                continue;
            if(!not_paint_cell.count(neighbor))
                continue;
            if (visited.find(neighbor) != visited.end())
                continue;

            bool can_pass = false;
            switch (dir)
            {
            case 0:
                can_pass = !get(current.get_h(), current.get_w()).get_top();
                break; // вверх
            case 1:
                can_pass = !get(current.get_h(), current.get_w()).get_bottom();
                break; // вниз
            case 3:
                can_pass = !get(current.get_h(), current.get_w()).get_left();
                break; // вліво
            case 2:
                can_pass = !get(current.get_h(), current.get_w()).get_right();
                break; // вправо
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

bool field::limit_of_lenght_line(int h, int w){
    set<pos> visited;

    int counter = 0;
    int right_not_paint_line_update = w, top_not_paint_line_update = h;
    while (!get(top_not_paint_line_update, w).get_top() && !get(top_not_paint_line_update, w).get_is_painted()){
        int rw = w, lw = w;
        while (!get(top_not_paint_line_update, rw).get_left() && !get(top_not_paint_line_update, rw).get_is_painted()){
            pos cell(top_not_paint_line_update, rw);
            if (!visited.count(cell)){
                visited.insert(cell);
                counter++;
                rw++;
            }
        }
        while (!get(top_not_paint_line_update, lw).get_right() && !get(top_not_paint_line_update, lw).get_is_painted()){
            pos cell(top_not_paint_line_update, lw);
            if (!visited.count(cell))
            {
                visited.insert(cell);
                counter++;
                lw--;
            }
        }
        top_not_paint_line_update--;
    }
    while (!get(h, right_not_paint_line_update).get_top() && !get(h, right_not_paint_line_update).get_is_painted()){
        int rh = h, lh = h;
        while (!get(rh, right_not_paint_line_update).get_left() && !get(rh, right_not_paint_line_update).get_is_painted()){
            pos cell(rh, right_not_paint_line_update);
            if (!visited.count(cell)){
                visited.insert(cell);
                counter++;
                rh++;
            }
        }
        while (!get(lh, right_not_paint_line_update).get_right() && !get(lh, right_not_paint_line_update).get_is_painted()){
            pos cell(lh, right_not_paint_line_update);
            if (!visited.count(cell)){
                visited.insert(cell);
                counter++;
                lh--;
            }
        }
        right_not_paint_line_update--;
    }

    return counter <= get(h, w).get_length_line();
}