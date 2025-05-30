#ifndef INSTRUCTION
#define INSTRUCTION

#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include "global_state.h"

void start_print();
void task_print();
void marking_print();
void center_text_print(char *s, int ansi_sumbol = 0);
void menu_print();
void resources_print(std::chrono::duration<double> duration);

#endif
