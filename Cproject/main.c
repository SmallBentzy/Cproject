#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "Select.h"
#include "MargeSortList.h"
//#define KNRM  "\x1B[0m"


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
    print(listHead, reset_course_data(), UnFilter, equal);
    if(!valid_flag)
        printf("There was a mismatch or failure to receive the data. \n"\
            "If you make an update, the input file will be replaced with the recorded data only.\n");
    listen(&listHead);
    fclose(file);
    delete_data_linked_list(listHead);

}

void listen(Node** listHead) {
    char line[MAX_ROW],*pcommand;
   char start_flag = 1;

   while(start_flag) {
       prompet(line);
       int len = strlen(line);
       if (line[len - 1] == '\n')
           line[len - 1] = '\0';
       if (strlen(line) == 0)
           continue;
       pcommand = strtok(line, " ");
       //strcpy(command, strtok(line, " "));
       if (!pcommand)
           continue;
       
       if (strcmp(pcommand, "quit")==0) {
           start_flag = 0;
           continue;
       }
       if (len == MAX_ROW-1) {
           printf("You enterd to long command. please enter a valid command, acording to rools\n");
           while (getchar()!='\n');
           continue;
       }
       if (strcmp(pcommand, "set")==0) {
           do_set(listHead, line);
           MergeSort(listHead);
           continue;
       }
       if (strcmp(pcommand, "print") == 0) {
           print(*listHead, reset_course_data(), UnFilter, equal);
           continue;
       }
       if (strcicmp(pcommand, "select") == 0) {
           do_select(listHead, line);
           continue;
       }
       printf("Invalid command!\n");                            //if it no mach any command.
   }
}

void do_set(Node** listHead, char* line) {
    char *took;
    Course_data data = reset_course_data();
    Courses course;
    Node* studentNode;
    took=strtok(NULL, "=");
    if (!took || strcmp(took + space_counter(took), "first name")) {
        printf("invalid command!\n");
        return;
    }
    took = strtok(NULL, "=,");
    if (!took || !validatename(took))
        return;
    strcpy(data.firstN ,took);

    took = strtok(NULL, ",=");
    if ( !took || strcmp(took+ space_counter(took), "second name")) {
        printf("invalid command!\n");
        return;
    }

    took = strtok(NULL, ",=");
    if (!took || !validatename(took))
        return ;
    strcpy(data.lastN, took);

    took = strtok(NULL, ", =");
    if (!took || strcmp(took+ space_counter(took), "ID")) {
        printf("invalid command!\n");
        return;
    }

    took = strtok(NULL, ", =");
    if (!took || !valisateID(took))
        return 0;
    data.ID = atoi(took);

    for (Courses c = 0; c < NUM_OF_CPURSES; c++) {

        took = strtok(NULL, ",=\n");
        if (!took) {
            //printf("invalid command! \n");
            //return;
            break;
        }
        course = validCourse(took + space_counter(took));
        if (course == no_valid) {
            printf("invalid command! course '%s' not exist\n", took);
            return;
        }


        took = strtok(NULL, " ,");
        if (!took)
            printf("invalid command! course missing course grade\n");
        if (!validateScore(took))
            return 0;
        insert_degree(course, atof(took), &data);

    }


//insert: 
    studentNode = findByID(data.ID, *listHead);
    if (studentNode)
        copyStudentData(studentNode, data);
    else
        insert_data(data, listHead);

}

void copyStudentData(Node* studentNode, Course_data data) {
    strcpy(studentNode->course_data->firstN, data.firstN);
    strcpy(studentNode->course_data->lastN, data.lastN);
    for (Courses c = 0; c < NUM_OF_CPURSES; c++)
        if (data.scores[c] != -1)
            studentNode->course_data->scores[c] = data.scores[c];
}


void prompet(char* line) {
    printf("->");
    fgets(line, MAX_ROW, stdin);
}


int readData(FILE* file, Node** head) {
    char line[MAX_ROW+1];
    char valid_flag = 1;
    int index = 0;
    Course_data data;

   //fgets(line, MAX_ROW + 1, file);
    while (fgets(line, MAX_ROW + 1, file) ) {
        index++;
        //if(line[strlen(line)-1]=='\0')
        data = reset_course_data();
        if (!getData(line, &data)) {
            printf("line %d no entered\n", index);
            valid_flag = 0;
           // goto next;
        }
        else
            if (!insert_data(data, head)) {
                valid_flag = 0;
                printf("line %d is no valid\n", index);
            }
 //next:   //fgets(line, MAX_ROW + 1, file);
        //printf("\n%s\n", line);
    }
    MergeSort(head);
    return valid_flag;
}

void print(Node* head, Course_data model, filter fil, operator op) {
    COURSES_ARRAY
        if (head) {
            for (Courses c = 0; c < NUM_OF_CPURSES +2; c++)
                printf("-------------------------");
            printf("\n");
            printf(" %-25s %-25s ", "first name", "last name");
            for (Courses c = 0; c < NUM_OF_CPURSES; c++)
                printf(" %-25s ", courses[c]);

            printf("\n");
            for (Courses c = 0; c < NUM_OF_CPURSES + 2; c++)
                printf("=========================");
            printf("\n");
            while (head) {
                if (fil( model, *(head->course_data), op)==1) {
                    printf(" %-25s %-25s ", head->course_data->firstN, head->course_data->lastN);
                    for (Courses c = 0; c < NUM_OF_CPURSES; c++)
                        if (head->course_data->scores[c] != -1)
                            printf(" %-25.0f ", head->course_data->scores[c]);
                        else
                            printf(" %-25s ", "---");

                    printf("\n");
                }
                head = head->next;
            }
            for (Courses c = 0; c < NUM_OF_CPURSES + 2; c++)
                printf("=========================");
            printf("\n");
        }
}


int UnFilter(Course_data model, Course_data data, operator op) {
    return(1);
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
            printf("Two names, with the same ID number, '%d' ", data.ID);
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
/*counts and returns the apaces begin the given str
*/
int space_counter(char* str) {
    int counter = 0;
    while ( str && *str == ' ') {
        counter++;
        str++;
    }
    return counter;
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
    if (!validatename(temp))
        return 0;
    strcpy(data->firstN, temp);

    strcpy(temp, strtok(NULL, ","));
    if (!validatename(temp))
        return 0;
    strcpy(data->lastN, temp);

    strcpy(temp, strtok(NULL, ","));   
    if (!valisateID(temp))
        return 0;
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
    if (!validateScore(temp))
        return 0;
    float degree = atof(temp);
    insert_degree(course, degree, data);

    return 1;
}

int validatename(char* str) {
    if (strlen(str) > MAX_NAME) {
        printf("the name '%s' is to long. Name should be shorter than %d\n.", str, MAX_NAME);
        return 0;
    }
    if (!isAlphaOnlyString(str)) {
        printf("the name '%s' is non-standard. Name have contain letters only\n.", str);
        return 0;
    }
    return 1;
}

int validateScore(char* str) {
    if (!isNumericOnlyString(str)) {
        printf("the degree '%s' is no valid. it have contain digits only.\n", str);
        return 0;
    }
    float degree = atof(str);
    if (degree< MIN_SCORE || degree >MAX_SCORE) {
        printf("the ID '%s' is no valid. it have be between %d to %d.\n", str, MAX_SCORE, MIN_SCORE);
        return 0;
    }
    return 1;
}

int valisateID(char* str) {
    if (!isNumericOnlyString(str)) {
        printf("the ID '%s' is no valid. it have contain digits only.\n", str);
        return 0;
    }
    if (strlen(str) != 9) {
        printf("the ID '%s' is no valid. it have be 9 digits.\n", str);
        return 0;
    }
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
