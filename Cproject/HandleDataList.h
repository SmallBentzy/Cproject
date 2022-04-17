#pragma once
#include"Utilities.h"

int insert_data(Course_data data, Node** head);

void delete_data_linked_list(Node* head);

Node* create_node();

void addNode(Node* newNode, Node** head);

Node* findByID(int ID, Node* head);

void copyStudentData(Node* studentNode, Course_data data);
