#pragma once
#include "main.h"


void do_select(Node** listHead, char* line);

operator swichOperator(char c);

int FirstNameFilter(Course_data model, Course_data data, operator op);

int LastNameFilter(Course_data model, Course_data data, operator op);

int averageFilter(Course_data model, Course_data data, operator op);

int calc(float ave, operator op, float model);
