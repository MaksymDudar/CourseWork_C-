#include <iostream>

#include "task_field.h"
#include "paint_method.h"

using namespace std;

void put_cell_to_firld(field &fiel){
    for (int i = 0; i < fiel.get_height(); i++)
    {
        for (int t = 0; t < fiel.get_width(); t++)
        {
            fiel.put(i, t).set_cell(num[i][t], gor[i][t], gor[i + 1][t], vert[i][t], vert[i][t + 1]);
        }
    }
}

int main(void){
    field field(10, 10);

    put_cell_to_firld(field);

    paint(field, 0, 0);
    
    cout << field;

    return 0;
}
