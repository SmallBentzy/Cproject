#pragma once
#include "Templates.h"

void lowerCaseString(char* str);

int strcicmp(char const* a, char const* b);

int strcincmp(char const* a, char const* b, int n);

void eraseSpace(char* str);

Course_data reset_course_data();

int validatename(char* str);

int validateScore(char* str);

int validateID(char* str);

int isAlphaOnlyString(char* str);

int isNumericOnlyString(char* str);

Courses validCourse(char* str);

int space_counter(char* str);

void insert_degree(Courses course, float degree, Course_data* data);