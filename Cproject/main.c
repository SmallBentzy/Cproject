#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "main.h"
#include "Select.h"
#include "MargeSortList.h"
#include "Print.h"
#include "Set.h"
#include "Print.h"
#include "ReadFile.h"
#include "UpdareFile.h"
#include "HandleDataList.h"


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
       int len = (int)strlen(line);
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




void prompet(char* line) {
    printf("->");
    fgets(line, MAX_ROW, stdin);
}


//void error_exit(char* msg, Node* list)
//{
//    if (list) {
//        delete_data_linked_list(list);
//    }
//    printf("%s\n", msg);
//}

