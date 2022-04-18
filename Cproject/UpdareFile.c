#define _CRT_SECURE_NO_WARNINGS
#include"UpdareFile.h"

void updateData(/*FILE** file,*/ Node* listHead){
	FILE *outTemp = fopen("D:temp", "w");
	
	while (listHead) {
		writeCourseData(outTemp, *(listHead->course_data) );
		listHead = listHead->next;
	}
	
	fclose(outTemp);
	if (remove(INPUT_FILE) ) {
		printf("an Error occure by update sorce file\n");
	}
	if (rename("D:temp", INPUT_FILE)) {
		printf("an Error occure by update sorce file\n");
	}

}

void writeCourseData(FILE* file, CourseData data) {
	Courses course;
	COURSES_ARRAY
		for (course = 0; course < NUM_OF_COURSES; course++)
			if (data.scores[course] != -1)
				fprintf(file, "%s,%s,%d,%s,%d\n", data.firstN, data.lastN, data.ID, courses[course], data.scores[course]);

	
}
