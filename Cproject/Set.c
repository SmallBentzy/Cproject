#define _CRT_SECURE_NO_WARNINGS

#include "Set.h"
#include "UpdareFile.h"
#include "HandleDataList.h"
#include"Utilities.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void do_set(/*FILE** file,*/ Node** listHead, char* line) {
    char* tokP;
    Course_data data = createCourseData();
    Courses course;
    Node* studentNode;
    tokP = strtok(NULL, "=");
    if (!tokP) {
        printf("invalid command! paremeters missing\n");
        return;
    }
    eraseSpace(tokP);                                                                 //erase begining apace
    tokP += space_counter(tokP);
    if (strcmp(tokP + space_counter(tokP), "first name")) {
        printf("invalid command! missing first name\n");
        return;
    }
    tokP = strtok(NULL, ",");
    if (!tokP || !validatename(tokP))
        return;
    data.firstN = (char*)malloc(strlen(tokP) + 1);
    if (!(data.firstN)) {
        printf("Failed to allocate memory");
        eraseCourseData(&data);
        return;
    }
    strcpy(data.firstN, tokP);

    tokP = strtok(NULL, "=");
    eraseSpace(tokP);                                                                 //erase begining space
    tokP += space_counter(tokP);
    if (!tokP || strcmp(tokP, "second name")) {
        printf("invalid command! parameter '%s' not identified\n", tokP);
        eraseCourseData(&data);
        return;
    }

    tokP = strtok(NULL, ",");
    eraseSpace(tokP);                                                                 //erase begining space
    tokP += space_counter(tokP);
    if (!tokP || !validatename(tokP)) {
        eraseCourseData(&data);
        return;
    }
    data.lastN = (char*)malloc(strlen(tokP) + 1);
    if (!(data.firstN)) {
        printf("Failed to allocate memory");
        eraseCourseData(&data);
        return;
    }
    strcpy(data.lastN, tokP);

    tokP = strtok(NULL, "=");
    eraseSpace(tokP);                                                                 //erase begining apace
    tokP += space_counter(tokP);
    if (!tokP || strcicmp(tokP, "ID")) {
        printf("invalid command! ID missing.\n");
        eraseCourseData(&data);
        return;
    }

    tokP = strtok(NULL, ",");
    eraseSpace(tokP);                                                                 //erase begining apace
    tokP += space_counter(tokP);
    if (!tokP || !validateID(tokP)) {
        eraseCourseData(&data);
        return;
    }
    data.ID = atoi(tokP);

    tokP = strtok(NULL, "=");
    eraseSpace(tokP);                                                                 //erase begining apace
    tokP += space_counter(tokP);
    if (!tokP) {
        printf("invalid command! name of course missing\n");
        eraseCourseData(&data);
        return;
    }
    course = validCourse(tokP + space_counter(tokP));
    if (course == no_valid) {
        printf("invalid command! course '%s' not exist\n", tokP);
        eraseCourseData(&data);
        return;
    }

    tokP = strtok(NULL, " ,");
    
    if (!tokP) {
        printf("invalid command! course missing course grade\n");
        eraseCourseData(&data);
        return;
    }
    eraseSpace(tokP);                                                                 //erase begining apace
    tokP += space_counter(tokP);
    if (!validateScore(tokP)) {
        eraseCourseData(&data);
        return;
    }
    insert_degree(course, atoi(tokP), &data);


    //insert: 
    studentNode = findByID(data.ID, *listHead);
    if (studentNode) {
        copyStudentData(studentNode, data);
        eraseCourseData(&data);
    }
    else
        insert_data(data, listHead);
    updateData(/*file,*/ *listHead);


}