#define _CRT_SECURE_NO_WARNINGS
#include "ReadFile.h"
#include "HandleDataList.h"
#include "MargeSortList.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



//data in string format is to be supplied to Cource data and it will store that in structure, after string parsing, strtok will tokenize string from each �,�
int getData(char* one, Course_data* data) {
    char* tokP = NULL;
    tokP = strtok(one, ",");
    if (!validatename(tokP))
        return 0;
    data->firstN =(char*)malloc(strlen(tokP) + 1);
    strcpy(data->firstN, tokP);

    tokP = strtok(NULL, ",");
    if (!validatename(tokP))
        return 0;
    data->lastN = (char*)malloc(strlen(tokP) + 1);
    strcpy(data->lastN, tokP);

    tokP = strtok(NULL, ",");
    if (!validateID(tokP))
        return 0;
    data->ID = atoi(tokP);

    tokP = strtok(NULL, ",");
    Courses course;
    if ((course = validCourse(tokP)) == NUM_OF_COURSES) {
        printf("the course '%s' is no valid.\n", tokP);
        return 0;
    }

    tokP = strtok(NULL, ", \n");
    if (!validateScore(tokP))
        return 0;
    char degree = (char)atoi(tokP);
    insert_degree(course, degree, data);

    return 1;
}

int readData(/*FILE* file,*/ Node** head) {
    char line[MAX_ROW + 2];
    char validFlag = 1, tooLongFlag=0;
    int index = 0;
    Course_data data ;
    FILE* file = fopen(INPUT_FILE, "r");
    if (!file) {
        printf("error to open read file");
        exit(1);
    }
    while (fgets(line, MAX_ROW + 2, file)) {
        index++;
        //printf("line %d \n", index);
        tooLongFlag = 0;
        data = createCourseData();
        int len = (int)strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        else {
            while (fgetc(file) != '\n');
            tooLongFlag = 1;
        }

        if (!getData(line, &data)) {
            eraseCourseData(&data);
            printf("line %d no entered\n", index);
            validFlag = 0;
        }
        else {
            if (!insert_data(data, head)) {
                validFlag = 0;
                eraseCourseData(&data);
                printf("line %d is no valid\n", index);
            }
            else {                                                      //a valid data added
                char* trash = strtok(NULL, " ");
                if (trash || tooLongFlag)
                    printf("Unnecessary arguments in line %d\n", index);
            }
        }
    }
    fclose(file);
    MergeSort(head);
    return validFlag;
}



