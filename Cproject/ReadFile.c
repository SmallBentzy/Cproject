#define _CRT_SECURE_NO_WARNINGS
#include "ReadFile.h"
#include "HandleDataList.h"
#include "MargeSortList.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



//data in string format is to be supplied to Cource data and it will store that in structure, after string parsing, strtok will tokenize string from each “,”
int getData(char* one, Course_data* data) {
    char* ptook = NULL;
    ptook = strtok(one, ",");
    if (!validatename(ptook))
        return 0;
    strcpy(data->firstN, ptook);

    ptook = strtok(NULL, ",");
    if (!validatename(ptook))
        return 0;
    strcpy(data->lastN, ptook);

    ptook = strtok(NULL, ",");
    if (!validateID(ptook))
        return 0;
    data->ID = atoi(ptook);

    ptook = strtok(NULL, ",");
    Courses course;
    if ((course = validCourse(ptook)) == NUM_OF_COURSES) {
        printf("the course '%s' is no valid.\n", ptook);
        return 0;
    }

    ptook = strtok(NULL, ", \n");
    if (!validateScore(ptook))
        return 0;
    char degree = (char)atoi(ptook);
    insert_degree(course, degree, data);

    return 1;
}

int readData(/*FILE* file,*/ Node** head) {
    char line[MAX_ROW + 2];
    char valid_flag = 1, to_longFlag=0;
    int index = 0;
    Course_data data;
    FILE* file = fopen(INPUT_FILE, "r");
    if (!file) {
        printf("error to open read file");
        exit(1);
    }
    while (fgets(line, MAX_ROW + 2, file)) {
        index++;
        int len = (int)strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        else {
            while (getchar() != '\n');
            to_longFlag = 1;
        }

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
                char* trash = strtok(NULL, " ");
                if (trash || to_longFlag)
                    printf("Unnecessary arguments in line %d\n", index);
            }
        }
        //next:   //fgets(line, MAX_ROW + 1, file);
               //printf("\n%s\n", line);
        
    }
    fclose(file);
    MergeSort(head);
    return valid_flag;
}



