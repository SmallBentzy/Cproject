#define _CRT_SECURE_NO_WARNINGS
#include "Select.h"
#include "HandleDataList.h"
#include <string.h>
#include <stdio.h>
#include "Print.h"
//#include<math.h>
#include"Utilities.h"
#include <stdlib.h>

void do_select(Node** listHead, char* line) {
    char* tokP;
    char* ch=NULL;
    char* copy = line + 7 + space_counter(line);//   the offset of 'select'///macro
    Course_data data = createCourseData();
    operato op =invalid;
    Courses course =no_valid;
    
    if ((ch = strchr(copy, '<')) || (ch = strchr(copy, '>')) || (ch = strstr(copy, "!=")) || (ch = strchr(copy, '=')) ) {
        //ch -= strlen(line);
        op = swichoperato(ch);
    }
    else {
        printf("invalid command! operator missing\n");
         goto ret;
    }
    tokP = strtok(NULL, "=<>!");
    if (!tokP) {
        printf("invalid command! parmetrer missing\n");
         goto ret;
    }
    eraseSpace(tokP);                                                                 //erase begining apace
    tokP += space_counter(tokP);                                                      //erase ending space
    
    
    if ( !strcicmp(tokP, "first name")) {
        tokP = strtok(NULL, ",\n");
        if (!tokP) {
            printf("invalid command! name mising\n");
             goto ret;
        }
        if ((op == e_less || op == e_more || op == different))                  //need to jamp over the double operator
            tokP++;
        tokP += space_counter(tokP);     
        eraseSpace(tokP);

        if (!validatename(tokP)) {
            //printf("Invalid name '%s'\n", took);
             goto ret;
        }
        if (!(data.firstN = (char*)malloc(strlen(tokP) + 1))) {
            printf("Failed to allocate memory");
            return;
        }
        strcpy(data.firstN, tokP);
        if (tokP = strtok(NULL, ""))
            printf("Unnecessary arguments in command line. '%s'\n", tokP);
        print(*listHead, data, FirstNameFilter, op);

         goto ret;
    }

    if (!strcicmp(tokP , "second name")) {
        tokP = strtok(NULL, ", \n");
        if (!tokP) {
            printf("invalid command! name mising\n");
             goto ret;
        }
        if ((op == e_less || op == e_more || op == different))                  //need to jamp over the double operator
            tokP++;
        tokP += space_counter(tokP);
        eraseSpace(tokP);
        
        if (!validatename(tokP)) {
            printf("Invalid name '%s'\n", tokP);
             goto ret;
        }
        data.firstN = (char*)malloc(strlen(tokP) + 1);
        strcpy(data.lastN, tokP);
        if (tokP = strtok(NULL, ""))
            printf("Unnecessary arguments in command line. '%s'\n", tokP);
        print(*listHead, data, LastNameFilter, op);
         goto ret;
    }                                                                       //calc select by course score or average
   
    
    if(!strcicmp(tokP, "Average") || (course = validCourse(tokP))!= no_valid) {
        tokP = strtok(NULL, " ,\n");
        if (!tokP) {
            printf("invalid command! parameter mising\n");
             goto ret;
        }
        if ((op == e_less || op == e_more || op == different))                  //need to jamp over the double operator
            tokP++;
        tokP += space_counter(tokP);
        eraseSpace(tokP);

        if (!validateScore(tokP)) {
             goto ret;
        }
        if(course ==no_valid)
            data.average = (float)atof(tokP);
        else
            data.scores[course] = atoi(tokP);
        if(tokP = strtok(NULL, " "))
            printf("Unnecessary arguments in command line. '%s'\n", tokP);
        if(course==no_valid)
            print(*listHead, data, averageFilter, op);
        else
            print(*listHead, data, gradeFilter, op);

        goto ret;
    }
    //else
    printf("'%s' is not a parameter.\n", tokP);

ret: 
    eraseCourseData(&data);


}



operato swichoperato(char *c) {
    operato op;
    switch (*c)
    {
    case'<':
        if (*(c + 1) == '=')
            op = e_less;
        else
            op = less;
        break;

    case'>':
        if (*(c + 1) == '=')
            op = e_more;
        else
            op = more;
        break;

    case '!':
        if (*(c + 1) == '=')
            op = different;
        else
            op = invalid;
        break;

    case'=':
        op= equal;
        break;

    default:
        op = invalid;
    }
    return op;
}

int FirstNameFilter(Course_data model, Course_data data, operato op) {
    //return( !strcicmp(model.firstN, data.firstN ) 
    return calcString(data.firstN, op, model.firstN);
}

int LastNameFilter(Course_data model, Course_data data, operato op) {
    //return(!strcicmp(model.lastN, data.lastN));
    return calcString(data.lastN, op, model.lastN);

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


int calc(float ave, operato op, float model) {
    switch (op)
    {
    case less:
        return ave < model;
    case more:
        return ave > model;
    case equal:
        return ave == model;
    case e_less:
        return ave <= model;
    case e_more:
        return ave >= model;
    case different:
        return ave != model;

    default:                                      // not in use;
        return 0;
    }
}

int calcString(char *str, operato op, char* model) {
    switch (op)
    {
    case less:
        return strcicmp(str, model)<0;
    case more:
        return strcicmp(str, model) > 0;
    case equal:
        return strcicmp(str, model) == 0;
    case e_less:
        return strcicmp(str, model) <= 0;
    case e_more:
        return strcicmp(str, model) >= 0;
    case different:
        return strcicmp(str, model) != 0;

    default:                                      // not in use;
        return 0;
    }
}