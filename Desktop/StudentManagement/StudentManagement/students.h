#ifndef _STUDENTS
#define _STUDENTS
#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENTS_STRING_LEN 100
typedef struct STUDENT{
    char id[MAX_STUDENTS_STRING_LEN];        //学号
    char cls[MAX_STUDENTS_STRING_LEN];       //班级
    char name[MAX_STUDENTS_STRING_LEN];      //姓名
    struct STUDENT *next;
}student;

void readStudents(student **head) {
    FILE * fp;
    if((fp = fopen("students.txt","r")) == NULL)
    {
        printf("Read Error : students.txt is not existed.");
        exit(-1);
    }

    *head = (student*)malloc(sizeof(student));

    student *p = *head, *tail;
    char str[MAX_STUDENTS_STRING_LEN];
    while(fscanf(fp,"%s",str)!=EOF) {
        tail = (student*)malloc(sizeof(student));
        strcpy(tail->id, str);
        fscanf(fp, "%s", tail->cls);
        fscanf(fp, "%s", tail->name);
        //printf("%s%s%s\n", tail->id, tail->cls, tail->name);
        tail->next = NULL;

        p->next = tail;
        p = p->next;

    }
    *head = (*head)->next;

}

student* searchStudent(student ** h, char *id) {
    student *p = *h;
    while(p) {
        if (strcmp(id, p->id)==0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
//将学号为id的学生信息，修改为t对应的信息
int updateStudent(student ** h, char * id, student* t) {

    student * p = searchStudent(h, id);
    if(p) {
        strcpy(p->id, t->id);
        strcpy(p->cls, t->cls);
        strcpy(p->name, t->name);
        return 1;
    }
    return 0;
}
void deleteStudent(student ** h, char *id) {

    student *p = *h;
    if(strcmp(id, p->id)==0) {
        (*h) = (*h)->next;
        return;
    }
    //pre = h;
    //p = p->next;

    while(p->next) {
        if (strcmp(id, p->next->id)==0) {
            p->next = p->next->next;
        }
        else {
            p = p->next;
        }
    }

}

int addStudent(student ** h, student* t) {
    //printf("test\n");
    student *p = *h;
    while(p->next) {
        p = p->next;
    }

    //t->next = NULL;
    student *new_t;
    new_t = (student*)malloc(sizeof(student));
    strcpy(new_t->id, t->id);
    strcpy(new_t->cls, t->cls);
    strcpy(new_t->name, t->name);

    new_t->next = NULL;
    p->next = new_t;
    //printf("%s\t%s\t%s\n", t->id, t->cls, t->name);

    return 1;
}

void printStudentsInformation(student * h){
    printf("Students Information is listed as follows.\n");
    student *p = h;
    while(p) {
        printf("%s\t%s\t%s\n", p->id, p->cls, p->name);
        p = p->next;
    }
}


void saveStudentInformation(student *h) {

	FILE * fp;
	if ((fp = fopen("students.txt", "w")) == NULL)
	{
		printf("Write Error : students.txt is not existed.");
		exit(-1);
	}

	student *p = h;

	while (p) {
		fprintf(fp,"%s\t%s\t%s\n", p->id, p->cls, p->name);
		p = p->next;
	}
	fclose(fp);
}


#endif
