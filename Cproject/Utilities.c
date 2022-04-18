
#include <stdio.h>
#include <ctype.h> 
//#include<stralign.h>
#include<string.h>
#include <stdlib.h>

#include "Utilities.h"

void lowerCaseString(char* str) {
	while (*str)
	{
		//printf("%c", *str);
		if (isupper(*(str)))
			*str= tolower(*str);
		str++;
	}
	
}

//insensitive compares insensitive strings a b
int strcicmp(char const* a, char const* b)
{
	for (;; a++, b++) {
		int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
		if (d != 0 || !*a)
			return d;
	}
}
int strcincmp(char const* a, char const* b, int n)
{
	for ( ;n>=0; n--, a++, b++) {
		int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
		if (d != 0 || !*a)
			return d;
	}
	return 0;
}
void eraseEndSpace(char* str) {
	int i, index = -1;
	for (i = 0; str[i]; i++) {
		if (str[i] != ' ')
			index = -1;
		else if (index == -1)
			index = i;
	}
	if (index != -1)
		str[index] = '\0';
}

char* eraseSpace(char* str) {
    eraseEndSpace(str);
    return str + spaceCounter(str);
}

CourseData createCourseData() {
	CourseData new;
    new.firstN = NULL;
    new.lastN = NULL;
    new.ID = 0;
	for (int i = 0; i < NUM_OF_COURSES; i++)
		new.scores[i] = -1;
	return new;
}

void eraseCourseData(CourseData *courseData) {
    if (courseData->firstN)
        free(courseData->firstN);
    if (courseData->lastN)
        free(courseData->lastN);
    for (Courses i = 0; i < NUM_OF_COURSES; i++)
        courseData->scores[i] = -1;
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
    float degree = (float)atof(str);
    if (degree< MIN_SCORE || degree >MAX_SCORE) {
        printf("the score '%s' is no valid. it have be between %d to %d.\n", str, MAX_SCORE, MIN_SCORE);
        return 0;
    }
    return 1;
}

int validateID(char* str) {
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
        if (!isalpha(*str) && !isspace(*str) )
            return 0;
        str++;
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
    for (Courses i = 0; i < NUM_OF_COURSES; i++)
        if (!strcmp(courses[i], str))
            return i;
    return no_valid;
}

/*counts and returns the apaces begin the given str
*/
int spaceCounter(char* str) {
    int counter = 0;
    while (str && *str == ' ') {
        counter++;
        str++;
    }
    return counter;
}

void insertDegree(Courses course, char degree, CourseData* data) {
    data->scores[course] = degree;
}

//call avaerage of degree aray. only valid listings consired.
float calAverage(char* arr) {
    int i, counter = 0;
    float sum = 0;
    for (i = 0; i < NUM_OF_COURSES; i++)
        if (arr[i] != -1) {
            sum += arr[i];
            counter++;
        }
    return (float)sum / counter;
}