#define _CRT_SECURE_NO_WARNINGS
#include "Select.h"
#include "main.h"
#include <string.h>
#include"Utililities.h"

//#include<string.h> 


void do_select(Node** listHead, char* line) {
    char* took;
    char copy[MAX_ROW];
    Course_data data = reset_course_data();
    operator op;
    //Courses course;
    //Node* studentNode;
    // 
    //char* dup = _strdup(line);
    //printf("%s\n", dup);
    strcpy(copy, line);
    took = strtok(NULL, "=<>");
    if (!took) {
        printf("invalid command! parmetrer missing\n");
        return;
    }
    eraseSpace(took);
    took += space_counter(took);
    if ( !strcicmp(took, "first name")) {
        took = strtok(NULL, "");
        if (!took) {
            printf("invalid command! name mising\n");
            return;
        }
        took += space_counter(took);
        eraseSpace(took);
        if (!validatename(took)) {
            printf("Invalid name '%s'\n", took);
            return;
        }
        strcpy(data.firstN, took);
        print(*listHead, data, FirstNameFilter, equal);
        return;
    }
    if (!strcicmp(took , "second name")) {
        took = strtok(NULL, "");
        if (!took) {
            printf("invalid command! name mising\n");
            return;
        }
        took += space_counter(took);
        eraseSpace(took);
        if (!validatename(took)) {
            printf("Invalid name '%s'\n", took);
            return;
        }
        strcpy(data.lastN, took);
        print(*listHead, data, LastNameFilter, equal);
        return;
    }
    if(!strcicmp(took, "Average")) {

       printf("%c  %s %ld\n", copy[took - line + strlen(took)], copy, took - line + strlen(took));
        op = swichOperator(copy[took - line + strlen(took)+1]);
        //op = swichOperator(*(took+strlen(took)+2));
        if (!op ) {
            printf("invalid operand '%c'\n", copy[took - line + strlen(took)+1]);
            return;
        }
        took = strtok(NULL, " ");
        if (!took) {
            printf("invalid command! parameter mising\n");
            return;
        }
        //took += space_counter(took);
        //eraseSpace(took);
        if (!validateScore(took)) {
            return;
        }
        data.scores[0]= atof(took);
        print(*listHead, data, averageFilter, op);
        return;
    }

    //free(dup);
}



operator swichOperator(char c) {
    switch (c)
    {
    case'<':
        return less;
    case'>':
        return more;
    case'=':
        return equal;
    default:
        return invalid;
    }
}

int FirstNameFilter(Course_data model, Course_data data, operator op) {
    return( !strcicmp(model.firstN, data.firstN ) );
}

int LastNameFilter(Course_data model, Course_data data, operator op) {
    return(!strcicmp(model.lastN, data.lastN));
}

int averageFilter(Course_data model, Course_data data, operator op) {
    float ave = calAverage(data.scores);
    return calc(ave, op, model.scores[0]);
}

//call avaerage of degree aray. only valid listings consired.
float calAverage(char* arr) {
    int i, counter =0;
    float sum = 0;   
    for(i=0; i<NUM_OF_CPURSES; i++)
        if (arr[i] != -1) {
            sum += arr[i];
            counter++;
       }
    return sum / counter;
}

int calc(float ave, operator op, float model) {
    switch (op)
    {
    case less:
        return ave < model;
    case more:
        return ave > model;
    case equal:
        return ave == model;

    default:                                      // not in use;
        return 0;
    }
}