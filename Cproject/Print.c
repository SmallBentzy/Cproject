#include "Print.h"


void print(Node* head, Course_data model, filter fil, operato op) {
    COURSES_ARRAY
        if (head) {
            printf("\n");
            for (Courses c = 0; c < NUM_OF_COURSES + 3; c++)
                printf("=========================");
            printf("\n");
            printf(" %-25s %-25s ", "first name", "last name");
            for (Courses c = 0; c < NUM_OF_COURSES; c++)
                printf(" %-25s ", courses[c]);
            printf(" %-25s ", "Average");
            printf("\n");
            for (Courses c = 0; c < NUM_OF_COURSES + 3; c++)
                printf("-------------------------");
            printf("\n");
            while (head) {
                if (fil(model, *(head->course_data), op) == 1) {
                    printf(" %-25s %-25s ", head->course_data->firstN, head->course_data->lastN);
                    for (Courses c = 0; c < NUM_OF_COURSES; c++)
                        if (head->course_data->scores[c] != -1)
                            printf(" %-25d ", head->course_data->scores[c]);
                        else
                            printf(" %-25s ", "---");
                    printf(" %-25g ", calAverage(head->course_data->scores) );

                    printf("\n");
                }
                head = head->next;
            }
            for (Courses c = 0; c < NUM_OF_COURSES + 3; c++)
                printf("=========================");
            printf("\n");
        }
}


int UnFilter(Course_data model, Course_data data, operato op) {
    return(1);
}
