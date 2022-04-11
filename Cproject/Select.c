#define _CRT_SECURE_NO_WARNINGS
#include "Select.h"
#include "HandleDataList.h"
#include <string.h>
#include <stdio.h>
#include "Print.h"


#include"Utililities.h"

//#include<string.h> 


void do_select(Node** listHead, char* line) {
    char* took;
    char* ch=NULL;
    char* copy = line + 7;//                                    the offset of 'select'
    Course_data data = reset_course_data();
    operato op;
    Courses course =no_valid;
    
    if ((ch = strchr(copy, '<')) || (ch = strchr(copy, '>')) || (ch = strchr(copy, '='))) {
        //ch -= strlen(line);
        op = swichoperato(*ch);
    }
    took = strtok(NULL, "=<>");
    if (!took) {
        printf("invalid command! parmetrer missing\n");
        return;
    }
    eraseSpace(took);                                                                 //erase begining apace
    took += space_counter(took);                                                      //erase ending space
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
    }                                                                       //calc select by course score or average
    if(!strcicmp(took, "Average") || (course = validCourse(took))!= no_valid) {
        took = strtok(NULL, " \n");
        if (!took) {
            printf("invalid command! parameter mising\n");
            return;
        }
        took += space_counter(took);
        eraseSpace(took);
        if (!validateScore(took)) {
            return;
        }
        if(course ==no_valid)
            data.average = (float)atof(took);
        else
            data.scores[course] = atoi(took);
        if(took = strtok(NULL, " "))
            printf("Unnecessary arguments in command line %s\n", took);
        if(course==no_valid)
            print(*listHead, data, averageFilter, op);
        else
            print(*listHead, data, gradeFilter, op);

        return;
    }
    //else
    printf("'%s' is not a parameter.\n", took);

}



operato swichoperato(char c) {
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

int FirstNameFilter(Course_data model, Course_data data, operato op) {
    return( !strcicmp(model.firstN, data.firstN ) );
}

int LastNameFilter(Course_data model, Course_data data, operato op) {
    return(!strcicmp(model.lastN, data.lastN));
}

int gradeFilter(Course_data model, Course_data data, operato op) {
    Courses i = 0;
    for (; i < NUM_OF_COURSES; i++)
        if (model.scores[i] != -1)
            break;
    return calc(data.scores[i], op, model.scores[i]);
}

int averageFilter(Course_data model, Course_data data, operato op) {
    float ave = calAverage(data.scores);
    return calc(ave, op, model.average);
}

//call avaerage of degree aray. only valid listings consired.
float calAverage(char* arr) {
    int i, counter =0;
    float sum = 0;   
    for(i=0; i<NUM_OF_COURSES; i++)
        if (arr[i] != -1) {
            sum += arr[i];
            counter++;
       }
    return (float)sum /counter;
}

int calc(float ave, operato op, float model) {
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