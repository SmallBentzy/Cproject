#define _CRT_SECURE_NO_WARNINGS
#include"UpdareFile.h"
//#include <unistd.h>
//#include <sys/types.h>

void updateData(/*FILE** file,*/ Node* listHead){
	FILE *outTemp = fopen("D:temp", "w");
	//fseek(file, 0, SEEK_SET);
	while (listHead) {
		writeCourseData(outTemp, *(listHead->course_data) );
		listHead = listHead->next;
	}
	//fclose(*file);
	fclose(outTemp);
	if (remove(INPUT_FILE) || rename("D:temp", INPUT_FILE)) {
		printf("an Error occure by update sorce file\n");
	}
	//*file= fopen(INPUT_FILE, "r+");
	//eraseFileTail(file);

}

void writeCourseData(FILE* file, Course_data data) {
	Courses course;
	COURSES_ARRAY
		for (course = 0; course < NUM_OF_COURSES; course++)
			if (data.scores[course] != -1)
				fprintf(file, "%s,%s,%d,%s,%d\n", data.firstN, data.lastN, data.ID, courses[course], data.scores[course]);

	//fprintf(file,"I finishd\n");
}


//void eraseFileTail(FILE* file) {
	//int position = ftell(file);
	//ftruncate(_fileno(file), position);
	/*while (fgetc(file) >= 0) {
		fseek(file, -1, SEEK_CUR);
		fputc('\b', file);
	}*/
//}