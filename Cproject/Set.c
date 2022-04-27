#define _CRT_SECURE_NO_WARNINGS

#include "Set.h"
#include "UpdareFile.h"
#include "HandleDataList.h"
#include"Utilities.h"
#include "MargeSortList.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void doSet(/*FILE** file,*/ Node** listHead, char* line) {
    char* tokP;
    CourseData data = createCourseData();
    Courses course;
    Node* studentNode;
    tokP = strtok(NULL, "=");
    if (!tokP) {
        printf("invalid command! paremeters missing\n");
        return;
    }
    tokP = eraseSpace(tokP);
    if (strcmp(tokP + spaceCounter(tokP), "first name")) {
        printf("invalid command! missing first name\n");
        return;
    }
    tokP = strtok(NULL, ",");
    tokP = eraseSpace(tokP);
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
    tokP = eraseSpace(tokP);
    if (!tokP || strcmp(tokP, "second name")) {
        printf("invalid command! parameter '%s' not identified\n", tokP);
        eraseCourseData(&data);
        return;
    }

   tokP = strtok(NULL, ",");
   tokP = eraseSpace(tokP);
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
    tokP = eraseSpace(tokP);
    if (!tokP || strcicmp(tokP, "ID")) {
        printf("invalid command! ID missing.\n");
        eraseCourseData(&data);
        return;
    }

    tokP = strtok(NULL, ",");
    tokP = eraseSpace(tokP);
    if (!tokP || !validateID(tokP)) {
        eraseCourseData(&data);
        return;
    }
    data.ID = atoi(tokP);

    tokP = strtok(NULL, "=");
    tokP = eraseSpace(tokP);
    if (!tokP) {
        printf("invalid command! name of course missing\n");
        eraseCourseData(&data);
        return;
    }
    course = validCourse(tokP + spaceCounter(tokP));
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
    tokP = eraseSpace(tokP);
    if (!validateScore(tokP)) {
        eraseCourseData(&data);
        return;
    }
    insertDegree(course, atoi(tokP), &data);


    //insert: 
    studentNode = findByID(data.ID, *listHead);
    if (studentNode) {
        replaceStudentData(studentNode, data);
        //eraseCourseData(&data);
    }
    else
        insertNewData(data, listHead);
    MergeSort(listHead);
    updateData(/*file,*/ *listHead);


}