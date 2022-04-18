#pragma once
#include"Utilities.h"

//int insert_data(Course_data data, Node** head);

int insertNewData(CourseData data, Node** head);

void copySecondaryData(CourseData data, Node* node);

void deleteDataLinkedList(Node* head);

Node* createNode();

void addNode(Node* newNode, Node** head);

Node* findByID(int ID, Node* head);

void copyStudentData(Node* studentNode, CourseData data);

void replaceStudentData(Node* studentNode, CourseData data);
