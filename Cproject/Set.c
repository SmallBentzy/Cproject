#define _CRT_SECURE_NO_WARNINGS

#include "Set.h"
#include "UpdareFile.h"
#include "HandleDataList.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>


void do_set(Node** listHead, char* line) {
    char* took;
    Course_data data = reset_course_data();
    Courses course;
    Node* studentNode;
    took = strtok(NULL, "=");
    if (!took) {
        printf("invalid command! paremeters missing\n");
        return;
    }
    eraseSpace(took);                                                                 //erase begining apace
    took += space_counter(took);
    if (strcmp(took + space_counter(took), "first name")) {
        printf("invalid command! missing first name\n");
        return;
    }
    took = strtok(NULL, ",");
    if (!took || !validatename(took))
        return;
    strcpy(data.firstN, took);

    took = strtok(NULL, "=");
    eraseSpace(took);                                                                 //erase begining apace
    took += space_counter(took);
    if (!took || strcmp(took, "second name")) {
        printf("invalid command!\n");
        return;
    }

    took = strtok(NULL, ",");
    eraseSpace(took);                                                                 //erase begining apace
    took += space_counter(took);
    if (!took || !validatename(took))
        return;
    strcpy(data.lastN, took);

    took = strtok(NULL, "=");
    eraseSpace(took);                                                                 //erase begining apace
    took += space_counter(took);
    if (!took || strcmp(took, "ID")) {
        printf("invalid command!\n");
        return;
    }

    took = strtok(NULL, ",");
    eraseSpace(took);                                                                 //erase begining apace
    took += space_counter(took);
    if (!took || !validateID(took))
        return;
    data.ID = atoi(took);

    took = strtok(NULL, "=");
    eraseSpace(took);                                                                 //erase begining apace
    took += space_counter(took);
    if (!took) {
        printf("invalid command! name of course missing\n");
        return;
    }
    course = validCourse(took + space_counter(took));
    if (course == no_valid) {
        printf("invalid command! course '%s' not exist\n", took);
        return;
    }

    took = strtok(NULL, " ,");
    eraseSpace(took);                                                                 //erase begining apace
    took += space_counter(took);
    if (!took)
        printf("invalid command! course missing course grade\n");
    if (!validateScore(took))
        return;
    insert_degree(course, atof(took), &data);


    //insert: 
    studentNode = findByID(data.ID, *listHead);
    if (studentNode)
        copyStudentData(studentNode, data);
    else
        insert_data(data, listHead);


}