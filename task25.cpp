/* --------------------------------------------------------------------------------<Header>-
Name:       task25.cpp
Title:      Paint the field according to certain rules

Group:      TB-41
Student:    Dudarchuk M.V.
Written:    2025-04-20
Revised:    2025-06-10

Description: Write a program in which - paint over some lethins on the playing field,
            two painted lethins should not stick together with each other, and all 
            unpainted lethins form a single continuous area. Cells with numbers can 
            be painted over, or you can leave unpainted, the numbers in blocks denote 
            the maximum size of a continuous line of unpainted litelitins within a 
            given block. The unpainted region does not necessarily have to be equal to
            this number, but a continuous line of unpainted litites is not may exceed 
            this value. Any continuous horizontal or vertical line of unpainted lethitins 
            cannot cross more than one bold line.
----------------------------------------------------------------------------------</Header>-*/

#include "paint_method.h"
#include "instuction.h"

using namespace std;

/* ---------------------------------------------------------------------[<]-
Function:   put_cell_to_field
Synopsis:   Fills the created field with bold lines and numbers in blocks from
            arrays (which are in the file global_state.h)
---------------------------------------------------------------------[>]-*/
void put_cell_to_field(field &fiel){
    for (int i = 0; i < fiel.get_height(); i++){
        for (int t = 0; t < fiel.get_width(); t++){
            if (num10x10[i][t] == -1){
                num10x10[i][t] = fiel.get_height() * fiel.get_width();
            }
            fiel.put(i, t).set_cell(num10x10[i][t], gor10x10[i][t], gor10x10[i + 1][t], vert10x10[i][t], vert10x10[i][t + 1]);
            
        }
    }
}

/* ---------------------------------------------------------------------[<]-
Function:   main
Synopsis:   Main method of program
---------------------------------------------------------------------[>]-*/
int main(void){
    field field_10(FIELD_SIZE_10, FIELD_SIZE_10);
    put_cell_to_field(field_10);
    field field_10_copy = field_10;

    auto start = chrono::high_resolution_clock::now();
    paint(field_10_copy, 0, 0);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    start_print();
    char choise;
    while (true)
    {
        menu_print();
        cout << "Enter choice:";
        cin >> choise;
        tolower(choise);
        switch (choise){
        case 'a':{
            task_print();
        }
            break;
            
        case 'b':{
            marking_print();
        }
        break;
        case 'c':{
            cout << field_10;
        }
        break;
        case 'd':{
            cout << field_10_copy;
            resources_print(duration);
        }
        break;
        case 'e':{
            field_10.~field();
            field_10_copy.~field();
            return 0;
        }
        default:{
            cout << "Input error. Try again" << endl;
        }
        break;
        }
    }
        return 0;
    }
