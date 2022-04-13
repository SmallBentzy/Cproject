#pragma once
//#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>


#define INPUT_FILE "D:new 2.txt"
#define MAX_NAME 25
#define MAX_COURSE_NAME 25
#define MAX_ROW 95
#define COURSES_ARRAY char* courses[] = {[no_valid]="no_valid", [C_language] = "C language",\
[Computer_Networks] = "Computer Networks",[CS_Fundamentals] = "CS Fundamentals" };
#define NUM_OF_COURSES 3
#define MAX_SCORE 100
#define MIN_SCORE 0


typedef struct Course_data {
    char firstN[MAX_NAME];
    char lastN[MAX_NAME];
    int ID;
    union score
    {
        char scores[NUM_OF_COURSES];
        float average;
    };
    
}Course_data;

typedef struct Node {
    Course_data* course_data;
    struct Node* next;
}Node;

typedef enum operato{
   invalid, equal, less, more, e_less, e_more, different
}operato;

typedef enum Courses { C_language, Computer_Networks, CS_Fundamentals, no_valid }Courses;

typedef int (*filter)(Course_data, Course_data, operato);