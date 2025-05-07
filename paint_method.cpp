
#include "paint_method.h"

set<pos> not_paint_cell;

int paint(field &fiel, int h, int w){
    if (fiel.is_inside_field(h,w)){
        cout << "h: " << h << " w: " << w << "lenght: " << fiel.length_not_painted_line_in_area(h, w)<< endl;
        if (fiel.one_bold_border_check(h, w) && fiel.length_not_painted_line_in_area(h, w) <= fiel.get(h, w).get_length_line()){
            pos cell(h, w);
            not_paint_cell.insert(cell);
            cout << fiel;
            // if (h == 8)
            //     exit(1);
            if (fiel.get(h, w).get_left())
            {
                fiel.get(h, w).set_painted_border_horizontal(true);
            }
            if (fiel.get(h, w).get_bottom()){
                fiel.get(h, w).set_painted_border_vertical(true);
            }
            if (w < fiel.get_width() - 1){
                fiel.get(h, w + 1).set_painted_border_horizontal(fiel.get(h, w).get_painted_border_horizontal());
            }
            if (h < fiel.get_height() - 1){
                fiel.get(h + 1, w).set_painted_border_vertical(fiel.get(h, w).get_painted_border_vertical());
            }

            if (w < fiel.get_width() - 1){
                paint(fiel, h, w + 1);
            } else if (h < fiel.get_height() - 1){
                paint(fiel, h + 1, 0);
            } else {
                cout << "Sucsesful paint.\n";
                return 0;
            }
        }
        else
        {
            pos req;
            req = paint_cell(fiel, h, w);
            if (req.get_h() == -1 || req.get_w() == -1){
                cout << "paint_cell return error";
                exit(1);
            } else {
                h = req.get_h();
                w = req.get_w();
            }
            paint(fiel, h, w);
        }
    } else {
        cout << "paint fiel size error";
        exit(1);
    }
    return 0;
};

pos paint_cell(field &fiel, int h, int w) {
    pos req;

    if(fiel.is_inside_field(h, w)){
        pos cell(h, w);
        if(!fiel.get(h, w).get_is_painted() && fiel.do_not_get_neighbors(h, w)){
            fiel.get(h, w).set_is_painted(true);

            if (h < fiel.get_height() - 1)
            {
                fiel.get(h + 1, w).set_painted_border_vertical(false);
            }
            if (w < fiel.get_width() - 1)
            {
                fiel.get(h, w + 1).set_painted_border_horizontal(false);
            }

            if (w == fiel.get_width() - 1)
            {
                req.set_h(h + 1);
                req.set_w(0);
            }
            else
            {
                req.set_h(h);
                req.set_w(w + 1);
            }
        } else if (w > 0){
            if (h > 0) {
                if (!fiel.get(h - 1, w).get_is_painted()){
                    fiel.get(h, w).set_painted_border_vertical(fiel.get(h - 1, w).get_painted_border_vertical());
                } else {
                    fiel.get(h, w).set_painted_border_vertical(false);
                }
            } else {
                fiel.get(h, w).set_painted_border_vertical(false);
            }

            fiel.get(h, w).set_painted_border_horizontal(false);
            if (fiel.get(h, w).get_is_painted())
            {
                fiel.get(h, w).set_is_painted(false);
            } else {
                not_paint_cell.
            }
            req = paint_cell(fiel, h, w - 1);
        } else if (h > 0) {
            if (!fiel.get(h - 1, w).get_is_painted())
            {
                fiel.get(h, w).set_painted_border_vertical(fiel.get(h - 1, w).get_painted_border_vertical());
            }
            else
            {
                fiel.get(h, w).set_painted_border_vertical(false);
            }
            fiel.get(h, w).set_painted_border_horizontal(false);
            if (fiel.get(h, w).get_is_painted())
            {
                fiel.get(h, w).set_is_painted(false);
            }
            req = paint_cell(fiel, h - 1, fiel.get_width() - 1);
        }
        else
        {
            cout << fiel;
            cout << "No more cells to paint.\n";
            exit(1);
        }
    } else {
        cout << "Bounds error!\n";
        exit(1);
    }
    return req;
};