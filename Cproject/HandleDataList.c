#define _CRT_SECURE_NO_WARNINGS
#include "HandleDataList.h"
#include "Utililities.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int insert_data(Course_data data, Node** head) {
    Node* node;
    node = findByID(data.ID, *head);
    if (node == NULL) {
        node = create_node();
        if (!node || !(node->course_data)) {
            printf("Failed to allocate memory");
            return 0;
        }
        addNode(node, head);
        *(node->course_data) = data;
    }
    else
    {
        if (strcmp(node->course_data->firstN, data.firstN) || strcmp(node->course_data->lastN, data.lastN)) {
            printf("Two names, with the same ID number, '%d' ", data.ID);
            return 0;
        }

        for (Courses course = 0; course < NUM_OF_COURSES; course++)
            if (data.scores[course] >= 0)
                if (node->course_data->scores[course] >= 0) {
                    COURSES_ARRAY
                        printf("the score of course '%s' of %d ID is Redefined", courses[course], data.ID);
                    return 0;
                }
                else
                    node->course_data->scores[course] = data.scores[course];
    }
    return 1;
}


Node* create_node() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->next = NULL;
        newNode->course_data = (Course_data*)malloc(sizeof(Course_data));
    }
    return newNode;
}

void addNode(Node* newNode, Node** head) {
    if (*head == NULL)
        *head = newNode;
    else {
        Node* temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

void delete_data_linked_list(Node* head) {
    while (head) {

        free(head->course_data);
        Node* temp = head;
        head = head->next;
        free(temp);

    }
}

Node* findByID(int ID, Node* head) {
    while (head && head->course_data->ID != ID)
        head = head->next;
    return head;
}

void copyStudentData(Node* studentNode, Course_data data) {
    strcpy(studentNode->course_data->firstN, data.firstN);
    strcpy(studentNode->course_data->lastN, data.lastN);
    for (Courses c = 0; c < NUM_OF_COURSES; c++)
        if (data.scores[c] != -1)
            studentNode->course_data->scores[c] = data.scores[c];
}
