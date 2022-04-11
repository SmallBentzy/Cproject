#pragma once

#define INPUT_FILE "D:input.txt"
#define MAX_NAME 25
#define MAX_COURSE_NAME 25
#define MAX_ROW 95
#define COURSES_ARRAY char* courses[] = {[no_valid]="no_valid", [C_language] = "C_language",[Computer_Networks] = "Computer_Networks",[CS_Fundamentals] = "CS_Fundamentals" };
#define NUM_OF_CPURSES 3
#define MAX_SCORE 100
#define MIN_SCORE 0


typedef struct Course_data {
    char firstN[MAX_NAME];
    char lastN[MAX_NAME];
    int ID;
    char C_language_dedree;
    char Computer_Networks_dedree;
    char CS_Fundamentals_degree;
}Course_data;

typedef struct Node {
    Course_data* course_data;
    struct Node* next;
}Node;


typedef enum Courses { no_valid, C_language, Computer_Networks, CS_Fundamentals }Courses;


int getData(char* one, Course_data* data);

int isAlphaOnlyString(char* str);

int isNumericOnlyString(char* str);
Courses validCourse(char* str);
void insert_degree(Courses course, float degree, Course_data* data);