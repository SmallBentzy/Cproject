#pragma once
#include "Templates.h"

void lowerCaseString(char* str);

int strcicmp(char const* a, char const* b);

int strcincmp(char const* a, char const* b, int n);

void eraseEndSpace(char* str);

char* eraseSpace(char* str);

CourseData createCourseData();

void eraseCourseData(CourseData* courseData);

int validatename(char* str);

int validateScore(char* str);

int validateID(char* str);

int isAlphaOnlyString(char* str);

int isNumericOnlyString(char* str);

Courses validCourse(char* str);

int spaceCounter(char* str);

void insertDegree(Courses course, char degree, CourseData* data);

float calAverage(char* arr);
