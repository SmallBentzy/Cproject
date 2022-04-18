#pragma once
#include "Templates.h"


void doSelect(Node** listHead, char* line);

operato swichoperato(char *c);

int FirstNameFilter(CourseData model, CourseData data, operato op);

int LastNameFilter(CourseData model, CourseData data, operato op);

int gradeFilter(CourseData model, CourseData data, operato op);

int averageFilter(CourseData model, CourseData data, operato op);


int calc(float ave, operato op, float model);

int calcString(char* str, operato op, char* model);
