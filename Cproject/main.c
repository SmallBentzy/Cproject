#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "main.h"

#define KNRM  "\x1B[0m"


int readData(FILE*, Node**);
void print(Node* head);
void delete_data_linked_list(Node* head);
int insert_data(Course_data data, Node** head);
Node* create_node();
void addNode(Node* newNode, Node** head);
Node* findByID(int ID, Node* head);
Course_data reset_course_data();
void error_exit(char*, Node*);


int main() {
    Node *listHead=NULL;
     //open file to read
    int valid_flag=1;
    FILE* file = fopen(INPUT_FILE, "r+");
    if (!file){
        printf("error to open file");
        exit(1);
    }
    valid_flag = readData(file, &listHead);
        //error_exit("error at read file", listHead);
    print(listHead);
    if(!valid_flag)
        printf("There was a mismatch or failure to receive the data. \n"\
            "If you make an update, the input file will be replaced with the recorded data only.\n");
    fclose(file);
    delete_data_linked_list(listHead);

}

int readData(FILE* file, Node** head) {
    char line[MAX_ROW+1];
    char valid_flag = 1;
    int index = 0;
    Course_data data;
    fgets(line, MAX_ROW + 1, file);
    while (strlen(line) > 30) {
        index++;
        data = reset_course_data();
        if (!getData(line, &data)) {
            printf("line %d is no valid\n", index);
            valid_flag = 0;
            goto next;
        }
        else
            if (!insert_data(data, head)) {
                valid_flag = 0;
                printf("line %d is no valid\n", index);
            }
 next:   fgets(line, MAX_ROW + 1, file);
        //printf("\n%s\n", line);
    }
    return valid_flag;
}

void print(Node* head) {
    COURSES_ARRAY
    while (head) {
        printf(" %-25s %-25s ",head->course_data->firstN, head->course_data->lastN);
        for (Courses c = 0; c < NUM_OF_CPURSES; c++)
            if(head->course_data->scores[c]!= -1)
                printf("%-3d     ", head->course_data->scores[c]);
            else
                printf("---     ");

        printf("\n");
        head = head->next;
    }
}

void delete_data_linked_list(Node* head) {
    while (head) {

        free(head->course_data);
        Node* temp = head;
        head = head->next;
        free(temp);

    }
}
int insert_data(Course_data data, Node** head) {
#ifdef DEBUG
    printf(KNRM " line %d in func  %s file %s\n", __LINE__, __func__, __FILE__);
#endif // DEBUG
    Node* node;
    node = findByID(data.ID, *head);
    if (node == NULL){
#ifdef DEBUG
        printf(KNRM " line %d in func  %s file %s\n", __LINE__, __func__,  __FILE__);
#endif // DEBUG
        node = create_node();
        if (!node || !(node->course_data) ) {
            printf("Failed to allocate memory");
            return 0;
        }
        addNode(node, head);
        *(node->course_data) = data;
    }
    else
    {
#ifdef DEBUG
        printf(KNRM " line %d in func  %s file %s\n", __LINE__, __func__,  __FILE__);
#endif // DEBUG

        if (strcmp(node->course_data->firstN, data.firstN) || strcmp(node->course_data->lastN, data.lastN)) {
            printf("Two names, with the same ID number, '%d' \n", data.ID);
            return 0;
        }
        
        for (Courses course = 0; course < NUM_OF_CPURSES; course++)
            if (data.scores[course] >= 0)
                if (node->course_data->scores[course] >= 0) {
                    COURSES_ARRAY
                    printf("the score of course '%s' of %d ID is Redefined",courses[course], data.ID);
                    return 0;
                }
                else
                    node->course_data->scores[course]= data.scores[course];
    }   
#ifdef DEBUG
    for (Courses course = 0; course < NUM_OF_CPURSES; course++)
        printf("%d %d, ", data.scores[course], node->course_data->scores[course]);
    printf("\n");
#endif // DEBUG
    return 1;
}

Node* create_node() {
#ifdef DEBUG
    printf(KNRM " line %d in func  %s file %s\n", __LINE__, __func__, __FILE__);
#endif // DEBUG

    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->next = NULL;
        newNode->course_data = (Course_data*)malloc(sizeof(Course_data));
    }
    return newNode;
}

void addNode(Node* newNode, Node** head) {
#ifdef DEBUG
    printf(KNRM " line %d in func  %s file %s\n", __LINE__, __func__, __FILE__);
#endif // DEBUG
    if (*head == NULL)
        *head = newNode;
    else {
        Node* temp = *head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

Node* findByID(int ID, Node* head) {
#ifdef DEBUG
    printf(KNRM " line %d in func  %s file %s\n", __LINE__, __func__, __FILE__);
#endif // DEBUG
    while (head && head->course_data->ID != ID)
        head = head->next;
#ifdef DEBUG
    printf(" line %d in func  %s file %s\n", __LINE__, __func__, __FILE__);
#endif // DEBUG

    return head;
}

Course_data reset_course_data() {
#ifdef DEBUG
    printf(KNRM " line %d in func  %s file %s\n", __LINE__, __func__, __FILE__);
#endif // DEBUG

    Course_data new;
    for (int i = 0; i < NUM_OF_CPURSES; i++)
        new.scores[i]=-1;
    return new;

}
void error_exit(char* msg, Node* list)
{
    if (list) {
        delete_data_linked_list(list);
    }
    printf("%s\n", msg);
}

//data in string format is to be supplied to get_ledger and it will store that in structure, after string parsing, strtok will tokenize string from each “,”
int getData(char* one, Course_data* data) {
#ifdef DEBUG
    printf(KNRM " line %d in func  %s file %s\n", __LINE__, __func__, __FILE__);
#endif // DEBUG
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
    if ( (course=validCourse(temp))==NUM_OF_CPURSES ) {
        printf("the course '%s' is no valid.\n", temp);
        return 0;
    }
#ifdef DEBUG
    printf(" %d ", course);
#endif // DEBUG


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
#ifdef DEBUG
        printf("%s\n ", str);
#endif // DEBUG
        for (Courses i = 0; i < NUM_OF_CPURSES; i++)
            if (!strcmp(courses[i], str))
                return i;
    return no_valid;
}

void insert_degree(Courses course, float degree, Course_data *data) {
    data->scores[course] = degree;
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