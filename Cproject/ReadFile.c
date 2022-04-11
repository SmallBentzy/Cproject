#define _CRT_SECURE_NO_WARNINGS
#include "ReadFile.h"
#include "HandleDataList.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



//data in string format is to be supplied to Cource data and it will store that in structure, after string parsing, strtok will tokenize string from each “,”
int getData(char* one, Course_data* data) {
    //char temp[MAX_ROW + 1];
    char* ptook = NULL;
    //strcpy(temp, strtok(one, ","));
    ptook = strtok(one, ",");
    if (!validatename(ptook))
        return 0;
    strcpy(data->firstN, ptook);

    //strcpy(temp, strtok(NULL, ","));
    ptook = strtok(NULL, ",");
    if (!validatename(ptook))
        return 0;
    strcpy(data->lastN, ptook);

    //strcpy(temp, strtok(NULL, ","));
    ptook = strtok(NULL, ",");
    if (!validateID(ptook))
        return 0;
    data->ID = atoi(ptook);

    //strcpy(temp, strtok(NULL, ","));
    ptook = strtok(NULL, ",");
    Courses course;
    if ((course = validCourse(ptook)) == NUM_OF_COURSES) {
        printf("the course '%s' is no valid.\n", ptook);
        return 0;
    }

    //strcpy(temp, strtok(NULL, ", \n"));
    ptook = strtok(NULL, ", \n");
    if (!validateScore(ptook))
        return 0;
    float degree = atof(ptook);
    insert_degree(course, degree, data);

    return 1;
}

int readData(FILE* file, Node** head) {
    char line[MAX_ROW + 1];
    char valid_flag = 1;
    int index = 0;
    Course_data data;

    while (fgets(line, MAX_ROW + 1, file)) {
        index++;
        int len = strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        if (len == MAX_ROW - 1)
            while (getchar() != '\n');

        data = reset_course_data();
        if (!getData(line, &data)) {
            printf("line %d no entered\n", index);
            valid_flag = 0;
            // goto next;0
        }
        else {
            if (!insert_data(data, head)) {
                valid_flag = 0;
                printf("line %d is no valid\n", index);
            }
            else {
                char trash = strtok(NULL, " ");
                if (trash)
                    printf("Unnecessary arguments in line %d\n", index);
            }
        }
        //next:   //fgets(line, MAX_ROW + 1, file);
               //printf("\n%s\n", line);
    }
    MergeSort(head);
    return valid_flag;
}



