#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"


int readData(FILE*, Node**);
Course_data reset_course_data();
void error_exit(char*, Node*);

//struct Ledger* get_Ledger(char*);
//void print_data_To_File(Course_data, FILE** );

int main() {
    Node *listHead=NULL;
     //open file to read
    FILE* file = fopen(INPUT_FILE, "r+");
    if (!file){
        printf("error to open file");
        exit(1);
    }
    if (!readData(file, &listHead))
        error_exit("error at read file", listHead);
    
    fclose(file);

}

int readData(FILE* file, Node** head) {
    char line[MAX_ROW+1];
    char valid_flag = 1;
    int index = 0;
    Course_data data= reset_course_data();
    fgets(line, MAX_ROW + 1, file);
    while (strlen(line) > 30) {
        index++;
        if (!getData(line, &data))
            printf("line %d is no valid", index);
        else
            if (!insert_data(data, head))
                valid_flag = 0;
        fgets(line, MAX_ROW + 1, file);
        //printf("\n%s\n", line);
    }
    return 1;
}

int insert_data(Course_data data, Node** head) {
    Node* node;
    node = findByID(data.ID, *head);
    if (node == NULL){
        node = create_node(*head);
        *(node->course_data) = data;
    }
    else
        node->course_data;
}

Course_data reset_course_data() {
    Course_data new;
    new.Computer_Networks_dedree = -1;
    new.CS_Fundamentals_degree = -1;
    new.C_language_dedree = -1;
    return new;

}
void error_exit(char* msg, Node* list)
{
    if (list) {
        //delete
    }
    printf("%s\n", msg);
}

//data in string format is to be supplied to get_ledger and it will store that in structure, after string parsing, strtok will tokenize string from each “,”
int getData(char* one, Course_data* data) {
    char temp[MAX_ROW+1];
    strcpy(temp, strtok(one, ","));
    if (strlen(temp) > MAX_NAME) {
        printf("the name '%s' is to long. Name should be shorter than %d\n", temp, MAX_NAME);
        return 0;
    }
    if (!(isAlphaOnlyString(temp))) {
        printf("the name '%s' is non-standard. Name have contain letters only %d\n", temp, MAX_NAME);
        return 0;
    }
    strcpy(data->firstN, temp);

    strcpy(temp, strtok(NULL, ","));
    if (strlen(temp) > MAX_NAME) {
        printf("the name '%s' is to long. Name should be shorter than %d\n.", temp, MAX_NAME);
        return 0;
    }
    if (!isAlphaOnlyString(temp)) {
        printf("the name '%s' is non-standard. Name have contain letters only\n.", temp);
        return 0;
    }
    strcpy(data->lastN, temp);

    strcpy(temp, strtok(NULL, ","));
    if (!isNumericOnlyString(temp)) {
        printf("the ID '%s' is no valid. it have contain digits only.\n", temp);
        return 0;
    }
    if (strlen(temp)!=9) {
        printf("the ID '%s' is no valid. it have be 9 digits.\n", temp);
        return 0;
    }
    data->ID = atoi(temp);

    strcpy(temp, strtok(NULL, ","));
        Courses course;
    if (!(course=validCourse(temp))) {
        printf("the course '%s' is no valid.\n", temp);
        return 0;
    }

    strcpy(temp, strtok(NULL, ","));
    if (temp[strlen(temp) - 1 == '\n'])
        temp[strlen(temp)- 1] = '\0';
    if (!isNumericOnlyString(temp)) {
        printf("the degree '%s' is no valid. it have contain digits only.\n", temp);
        return 0;
    }
    float degree = atof(temp);
    if (degree< MIN_SCORE || degree >MAX_SCORE) {
        printf("the ID '%s' is no valid. it have be between %d to %d.\n", temp, MAX_SCORE, MIN_SCORE);
        return 0;
    }
    insert_degree(course, degree, data);

    return 1;
}

int isAlphaOnlyString(char* str) {
    while (*str != 0) {
        if(!isalpha(*str++))
            return 0;
    }
    return 1;
}

int isNumericOnlyString(char* str) {
    while (*str != 0) {
        if (!isdigit(*str++))
            return 0;
    }
    return 1;
}

Courses validCourse(char* str) {
    COURSES_ARRAY
        for (Courses i = C_language; i <= NUM_OF_CPURSES; i++)
            if (!strcmp(courses[i], str))
                return i;
    return no_valid;
}

void insert_degree(Courses course, float degree, Course_data *data) {
    switch (course)
    {
    case C_language:
        data->C_language_dedree = degree;
        break;
    case Computer_Networks:
        data->Computer_Networks_dedree = degree;
        break;
    case CS_Fundamentals:
        data->CS_Fundamentals_degree = degree;
        break;
    default:
        break;
    }
}


//void print_ledger_To_File(struct Ledger* ledger, FILE* ofp) {
//    fprintf(ofp, "\n==================================================\n");
//    fprintf(ofp, "%s report - %s\n", ledger->quarter, ledger->business);
//    fprintf(ofp, "==================================================\n");
//    fprintf(ofp, "Income:    $ %4.2lf\tAssets:      $ %4.2lf\n", ledger->income, ledger->assets);
//    fprintf(ofp, "Expenses:  $ %4.2f\tLiabilities: $ %4.2f\n", ledger->expenses, ledger->liabilities);
//    fprintf(ofp, "--------------------------------------------------\n");
//    fprintf(ofp, "profits:   $ %4.2lf\tNet Worth:   $ %4.2lf \n", ledger->income - ledger->expenses, ledger->assets - ledger->liabilities);
//    fprintf(ofp, "--------------------------------------------------\n");
//
//
//}