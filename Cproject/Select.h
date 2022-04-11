#pragma once
#include "Templates.h"


void do_select(Node** listHead, char* line);

operato swichoperato(char c);

int FirstNameFilter(Course_data model, Course_data data, operato op);

int LastNameFilter(Course_data model, Course_data data, operato op);

int gradeFilter(Course_data model, Course_data data, operato op);

int averageFilter(Course_data model, Course_data data, operato op);

float calAverage(char* arr);

int calc(float ave, operato op, float model);
