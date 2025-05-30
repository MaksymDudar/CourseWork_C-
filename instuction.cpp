#include "instuction.h"

using namespace std;

string name_file_with_rule = "task25.txt";
string empty_string = "";
string not_bold_vertical = "|";
string bold_vertical = "\033[1;93m|\033[0m";
string not_bold_horizontal = "―";
string bold_horizontal = "\033[1;93m―\033[0m";

/* ---------------------------------------------------------------------[<]-
Function:   center_text_print
Synopsis:   Prints a given string centered within a fixed width, surrounded by vertical borders
Arguments:  s - the string to print; ansi_sumbol - extra padding for ANSI escape sequences
---------------------------------------------------------------------[>]-*/
void center_text_print(const string &s, int ansi_sumbol = 0){
    int str_length = s.length();
    int padding_left = (WIDTH - str_length + ansi_sumbol) / 2;
    int padding_right = WIDTH - str_length - padding_left + ansi_sumbol;

    cout << bold_vertical;
    cout << string(padding_left, ' ') << s << string(padding_right, ' ');
    cout << bold_vertical << endl;
}

/* ---------------------------------------------------------------------[<]-
Function:   line_print
Synopsis:   Prints a horizontal line representing the top or bottom border of a block
---------------------------------------------------------------------[>]-*/
void line_print(){
    for (int i = 0; i < WIDTH + 2; i++){
        cout << bold_horizontal;
    }
    cout << endl;
}

/* ---------------------------------------------------------------------[<]-
Function:   start_print
Synopsis:   Displays the welcome screen with title, author, and group information
---------------------------------------------------------------------[>]-*/
void start_print() {
    string welcome = "Welcome! This is Task 25";
    string author = "Creat by: Maksym Dudarchuk";
    string tv_41 = "Group: TV-41";

    line_print();
    center_text_print(empty_string);
    center_text_print(welcome);
    center_text_print(author);
    center_text_print(tv_41);
    center_text_print(empty_string);
    line_print();
};

/* ---------------------------------------------------------------------[<]-
Function:   task_print
Synopsis:   Reads and prints the task description from a file in a formatted layout
Note:       Exits the program if the file cannot be opened
---------------------------------------------------------------------[>]-*/
void task_print() {
    string task_text = "\033[1mTask\033[0m";
    ifstream file(name_file_with_rule);
    if (!file){
        cerr << "Не вдалося відкрити файл!" << endl;
        exit(1);
    }

    line_print();
    center_text_print(empty_string);

    center_text_print(task_text, 8);
    center_text_print(empty_string);

    string buffer;
    while (getline(file, buffer)){
        center_text_print(buffer);
    }

    center_text_print(empty_string);
    line_print();
};

/* ---------------------------------------------------------------------[<]-
Function:   marking_print
Synopsis:   Displays the legend for interpreting field markings and symbols
---------------------------------------------------------------------[>]-*/
void marking_print(){
    string marking_text = "\033[1m Marking\033[0m";
    string not_bold_vertical_text = "Not bold vertical: ";
    string bold_vertical_text = "Bold vertical: ";
    string not_bold_horizontal_text = "Not bold horizontal: ";
    string bold_horizontal_text = "Bold horizontal: ";
    string border_text = "Border";
    string is_painted_text = "Is painted";
    string painted_text = "Painted: ";
    string not_painted_text = "Not painted: ";
    string painted = "\033[1;41m   \033[0m";
    string not_painted = "  ";
    string max_lenght_of_not_paunted_line_text = "Max lenght of not paunted line marking: 4";

    line_print();
    center_text_print(empty_string);

    center_text_print(marking_text, 8);

    center_text_print(empty_string);
    center_text_print(border_text);
    center_text_print(not_bold_vertical_text + not_bold_vertical);
    center_text_print(bold_vertical_text + bold_vertical, 11);
    center_text_print(not_bold_horizontal_text + not_bold_horizontal, 2);
    center_text_print(bold_horizontal_text + bold_horizontal, 13);
    center_text_print(empty_string);

    center_text_print(is_painted_text);
    center_text_print(painted_text + painted, 11);
    center_text_print(not_painted_text + not_painted);
    center_text_print(empty_string);

    center_text_print(max_lenght_of_not_paunted_line_text);

    center_text_print(empty_string);
    line_print();
};

/* ---------------------------------------------------------------------[<]-
Function:   menu_print
Synopsis:   Prints the menu options for interacting with the program
---------------------------------------------------------------------[>]-*/
void menu_print() {
    string menu_text = "\033[1m Menu\033[0m";
    string a_text = "\033[1m A.\033[0m Print task        ";
    string b_text = "\033[1m B.\033[0m Print marking     ";
    string c_text = "\033[1m C.\033[0m Print empty field ";
    string d_text = "\033[1m D.\033[0m Print filled field";
    string e_text = "\033[1m E.\033[0m Exit              ";

    line_print();
    center_text_print(empty_string);

    center_text_print(menu_text, 8);
    center_text_print(empty_string);
    center_text_print(a_text, 8);
    center_text_print(b_text, 8);
    center_text_print(c_text, 8);
    center_text_print(d_text, 8);
    center_text_print(e_text, 8);    

    center_text_print(empty_string);
    line_print();
};

/* ---------------------------------------------------------------------[<]-
Function:   resources_print
Synopsis:   Prints execution statistics including iteration count and elapsed time
Arguments:  duration - the total time taken by the algorithm
---------------------------------------------------------------------[>]-*/
void resources_print(chrono::duration<double> duration){
    string count_iteration = "Iterations were made: ";
    string count_time = "Time spent: ";

    line_print();
    center_text_print(empty_string);
    center_text_print(name_file_with_rule);
    center_text_print(count_iteration + to_string(g_counter_iteration));
    center_text_print(count_time + to_string(duration.count()));
    center_text_print(empty_string);
    line_print();
};
