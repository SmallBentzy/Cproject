#pragma once
#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "D:new 2.txt"
#define MAX_NAME 25
#define MAX_COURSE_NAME 25
#define MAX_ROW 95
#define COURSES_ARRAY char* courses[] = {[no_valid]="no_valid", [C_language] = "C language",\
[Computer_Networks] = "Computer Networks",[CS_Fundamentals] = "CS Fundamentals" };
#define NUM_OF_CPURSES 3
#define MAX_SCORE 100
#define MIN_SCORE 0


typedef struct Course_data {
    char firstN[MAX_NAME];
    char lastN[MAX_NAME];
    int ID;
    float scores[NUM_OF_CPURSES];
}Course_data;

typedef struct Node {
    Course_data* course_data;
    struct Node* next;
}Node;

typedef enum operator{
   invalid, equal, less, more, e_less, e_more, different
}operator;

typedef enum Courses { C_language, Computer_Networks, CS_Fundamentals, no_valid}Courses;

typedef int (*filter)(Course_data, Course_data, operator);

void listen(Node** listHead);

void do_set(Node** listHead, char* line);

void copyStudentData(Node* studentNode, Course_data data);

void prompet(char* line);

int readData(FILE* file, Node**);

void print(Node* head, Course_data model, filter fil, operator op);

int UnFilter(Course_data model, Course_data data, operator op);

void delete_data_linked_list(Node* head);

int insert_data(Course_data data, Node** head);

int space_counter(char* str);

Node* create_node();

void addNode(Node* newNode, Node** head);

Node* findByID(int ID, Node* head);

Course_data reset_course_data();

void error_exit(char*, Node*);

int getData(char* one, Course_data* data);

int validatename(char* str);

int validateScore(char* str);

int valisateID(char* str);

int isAlphaOnlyString(char* str);

int isNumericOnlyString(char* str);
Courses validCourse(char* str);
void insert_degree(Courses course, float degree, Course_data* data);