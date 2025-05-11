
#include "paint_method.h"

int paint(field &fiel, int h, int w){
    counter_iteration++;
    if (fiel.is_inside_field(h,w)){
        if (fiel.get(h, w).get_painted_border_horizontal() < NUM_OF_BOLD_LINE_CAN_CROSS + 1 && fiel.get(h, w).get_painted_border_vertical() < NUM_OF_BOLD_LINE_CAN_CROSS + 1 && fiel.length_not_painted_line_in_area(h, w) <= fiel.get(h, w).get_length_line())
        {
            pos cell(h, w);
            if (!g_not_paint_cell.count(cell)){
                g_not_paint_cell.insert(cell);
            } else {
                cout << "not_paint_cell erro";
                exit(1);
            }

            if (fiel.get(h, w).get_left()){
                fiel.get(h, w).increment_painted_border_horizontal();
            }
            if (fiel.get(h, w).get_bottom()){
                fiel.get(h, w).increment_painted_border_vertical();
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
                return 0;
            }
        }
        else
        {
            pos req;
            req = paint_cell(fiel, h, w);
            if (h == fiel.get_height() - 1 && w == fiel.get_width() - 1){
                return 0;
            }
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

    if (fiel.is_inside_field(h, w)){
        if (!fiel.get(h, w).get_is_painted() && fiel.do_not_get_neighbors(h, w)){
            pos cell(h, w);
            if (g_not_paint_cell.count(cell)){
                g_not_paint_cell.erase(cell);
            }

            fiel.get(h, w).set_is_painted(true);
            g_paint_counter++;
            pos one_not_painted = fiel.find_one_not_painted_cell();
            if(one_not_painted.get_h() == -1){
                cout << "one_not_painted error";
                exit(1);
            }

            if ((fiel.not_paint_area(one_not_painted.get_h(), one_not_painted.get_w()) + g_paint_counter) != fiel.get_height() * fiel.get_width()){
                fiel.get(h, w).set_is_painted(false);
                g_paint_counter--;
                clear_cell(fiel, h, w);
                if (g_not_paint_cell.count(cell)){
                    g_not_paint_cell.erase(cell);
                }
                if (w > 0){
                    req = paint_cell(fiel, h, w - 1);
                } else if(h > 0){
                    req = paint_cell(fiel, h - 1, fiel.get_width() - 1);
                } else {
                    cout << "paint fiel size error";
                    exit(1);
                }
            }
            else
            {
                if (h < fiel.get_height() - 1){
                    fiel.get(h + 1, w).set_painted_border_vertical(0);
                }
                if (w < fiel.get_width() - 1){
                    fiel.get(h, w + 1).set_painted_border_horizontal(0);
                }

                if (w == fiel.get_width() - 1){
                    req.set_h(h + 1);
                    req.set_w(0);
                } else {
                    req.set_h(h);
                    req.set_w(w + 1);
                }
            }
        } else if (w > 0) {
            counter_iteration++;
            clear_cell(fiel, h, w);
            req = paint_cell(fiel, h, w - 1);

        } else if (h > 0) {
            counter_iteration++;
            clear_cell(fiel, h, w);
            req = paint_cell(fiel, h - 1, fiel.get_width() - 1);
        } else {
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

void clear_cell(field &fiel, int h, int w){
    pos cell(h, w);
    if (h > 0 && !fiel.get(h - 1, w).get_is_painted()){
        fiel.get(h, w).set_painted_border_vertical(fiel.get(h - 1, w).get_painted_border_vertical());
    } else {
        fiel.get(h, w).set_painted_border_vertical(0);
    }
    fiel.get(h, w).set_painted_border_horizontal(0);

    if (fiel.get(h, w).get_is_painted()){
        fiel.get(h, w).set_is_painted(false);
        g_paint_counter--;
    } else {
        if (g_not_paint_cell.count(cell)){
            g_not_paint_cell.erase(cell);
        }
    }
}