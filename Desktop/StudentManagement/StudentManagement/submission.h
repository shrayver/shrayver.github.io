#ifndef _SUBMISSION
#define _SUBMISSION
#include <stdio.h>

#define MAX_SUBMISSION_STRING_LEN 100
typedef struct SUBMISSION{
    char id[MAX_SUBMISSION_STRING_LEN];        //学号
    char cls[MAX_SUBMISSION_STRING_LEN];       //班级
    char course_name[MAX_SUBMISSION_STRING_LEN];    //课程名
    char course_id[MAX_SUBMISSION_STRING_LEN];      //作业编号
    char submission_time[MAX_SUBMISSION_STRING_LEN]; //提交时间
    char submission_count[MAX_SUBMISSION_STRING_LEN]; //提交次数
    char remark[MAX_SUBMISSION_STRING_LEN];     //备注
    struct SUBMISSION* next;
}submission;
void readSubmission(submission **head) {
    FILE * fp;
    if((fp = fopen("submission.txt","r")) == NULL)
    {
        printf("Read Error : submission.txt is not existed.");
        exit(-1);
    }

    *head = (submission*)malloc(sizeof(submission));

    //printf("test\n");
    submission *p = *head, *tail;
    char str[MAX_SUBMISSION_STRING_LEN];
    while(fscanf(fp,"%s",str)!=EOF) {
        tail = (submission*)malloc(sizeof(submission));
        strcpy(tail->id, str);
        fscanf(fp, "%s", tail->cls);

        fscanf(fp, "%s", tail->course_name);
        fscanf(fp, "%s", tail->course_id);
        fscanf(fp, "%s", tail->submission_time);
        fscanf(fp, "%s", tail->submission_count);
        fscanf(fp, "%s", tail->remark);

        tail->next = NULL;

        p->next = tail;
        p = p->next;

    }
    *head = (*head)->next;

}

submission* searchSubmission(submission ** h,char *stu_id, char *course_id) {
    submission *p = *h;
    while(p) {
        if (strcmp(course_id, p->course_id)==0 && strcmp(stu_id, p->id)==0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

void printSubmission(submission * p) {
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", p->id, p->cls, p->course_name,
		p->course_id, p->submission_time, p->submission_count, p->remark);
}

int searchAndPrintSubmissionInTime(submission *h, char *start_date, char * end_date) {
	printf("Homework Information in date from %s to %s is listed as follows.\n", start_date, end_date);
	submission *p = h;
	int flag = 0;
	while (p) {
		if (strcmp(p->submission_time, start_date) >= 0 && strcmp(p->submission_time, end_date) <= 0) {
			//printf("%s %s %s %s %s %s %s\n", p->id, p->cls, p->course_name,
			//	p->course_id, p->submission_time, p->submission_count, p->remark);
			printSubmission(p);
			flag = 1;
		}
		p = p->next;
	}
	return flag;
}

int searchAndPrintSubmissionInCourseName(submission *h, char* course_name) {
	printf("Homework Information with course name %s is listed as follows.\n", course_name);
	submission *p = h;
	int flag = 0;
	while (p) {
		if (strcmp(course_name, p->course_name) == 0) {
			//printf("%s %s %s %s %s %s %s\n", p->id, p->cls, p->course_name,
			//	p->course_id, p->submission_time, p->submission_count, p->remark);
			printSubmission(p);
			flag = 1;
		}
		p = p->next;
	}
	return flag;

}
int searchAndPrintSubmissionInStudentID(submission *h, char* id) {
	printf("Homework Information with student id %s is listed as follows.\n", id);
	submission *p = h;
	int flag = 0;
	while (p) {
		if (strcmp(id, p->id) == 0) {
			//printf("%s %s %s %s %s %s %s\n", p->id, p->cls, p->course_name,
			//	p->course_id, p->submission_time, p->submission_count, p->remark);
			printSubmission(p);
			flag = 1;
		}
		p = p->next;
	}
	return flag;

}

int updateSubmission(submission ** h, char * stu_id, char * course_id, submission* t) {

    submission * p = searchSubmission(h, stu_id, course_id);
    if(p) {
        strcpy(p->cls, t->cls);
        strcpy(p->course_id, t->course_id);
        strcpy(p->course_name, t->course_name);
        //p->times = t->times;
        strcpy(p->id, t->id);
        strcpy(p->submission_count, t->submission_count);
        strcpy(p->remark, t->remark);
        strcpy(p->submission_time, t->submission_time);
        return 1;
    }
    return 0;
}

void deleteSubmission(submission ** h, char *stu_id, char *course_id) {
    submission *p = *h;
    if(strcmp(course_id, p->course_id)==0 && strcmp(stu_id, p->id)==0) {
        (*h) = (*h)->next;
        return;
    }
    //pre = h;
    //p = p->next;

    while(p->next) {
        if (strcmp(course_id, p->next->course_id)==0&&
            strcmp(stu_id, p->next->id)==0) {
            p->next = p->next->next;
        }
        else {
            p = p->next;
        }
    }
}

int addSubmisson(submission ** h, submission* t) {
    //printf("test\n");
    submission *p = *h;
    while(p->next) {
        p = p->next;
    }

    //t->next = NULL;
    submission *new_t;
    new_t = (submission*)malloc(sizeof(submission));

    strcpy(new_t->cls, t->cls);
    strcpy(new_t->course_id, t->course_id);
    strcpy(new_t->course_name, t->course_name);
    //p->times = t->times;
    strcpy(new_t->id, t->id);
    strcpy(new_t->submission_count, t->submission_count);
    strcpy(new_t->remark, t->remark);
    strcpy(new_t->submission_time, t->submission_time);

    new_t->next = NULL;
    p->next = new_t;
    //printf("%s\t%s\t%s\n", t->id, t->cls, t->name);

    return 1;
}

int searchAndPrintSubmission(submission *h, char * student_id) {
	printf("Submission Information with course id %s is listed as follows.\n", student_id);
	submission *p = h;
	int flag = 0;
	while (p) {
		if (strcmp(p->id, student_id) == 0) {
			/* printf("%s %s %s %s %s %s %s\n", p->course_id, p->course_name, p->times,
					 p->details, p->date, p->deadline, p->remark);*/
			printSubmission(p);
			flag = 1;
		}
		p = p->next;
	}
	return flag;

}

void printSubmissionInformation(submission * h){
    printf("Submission Information is listed as follows.\n");
    submission *p = h;
    while(p) {
        //printf("%s %s %s %s %s %s %s\n", p->id, p->cls, p->course_name,
        //        p->course_id, p->submission_time, p->submission_count, p->remark);
		printSubmission(p);
        p = p->next;
    }
}


int ascendingDate(submission *a, submission * b) {
	if (strcmp(a->submission_time, b->submission_time) < 0) return 1;
	else return 0;
}
int descendingDate(submission *a, submission * b) {
	if (strcmp(a->submission_time, b->submission_time) > 0) return 1;
	else return 0;
}
int ascendingCount(submission *a, submission * b) {
	if (strcmp(a->submission_count, b->submission_count) < 0) return 1;
	else return 0;
}
int descendingCount(submission *a, submission * b) {
	if (strcmp(a->submission_count, b->submission_count) > 0) return 1;
	else return 0;
}
int ascendingID(submission *a, submission * b) {
	if (strcmp(a->id, b->id) < 0) return 1;
	else return 0;
}

// 1. 直接选择排序   ------直接交换数据
void selectSortSubmission(submission **head, int(*func_p)(submission*, submission*)) {
	submission *p = NULL;
	submission *q = NULL;
	submission *t = NULL;

	if (*head == NULL || (*head)->next == NULL) {
		return;
	}
	for (p = *head; p != NULL; p = p->next) {
		t = p;
		for (q = p->next; q != NULL; q = q->next) {
			if (func_p(q, t) > 0) {
				//if (strcmp(q->course_id, t->course_id)>0) {
				t = q;
			}
		}
		if (t != p)
		{
			submission new_t;
			strcpy(new_t.course_id, p->course_id);
			strcpy(new_t.course_name, p->course_name);
			strcpy(new_t.id, p->id);
			strcpy(new_t.submission_time, p->submission_time);
			strcpy(new_t.cls, p->cls);
			strcpy(new_t.remark, p->remark);
			strcpy(new_t.submission_count, p->submission_count);

			strcpy(p->course_id, t->course_id);
			strcpy(p->course_name, t->course_name);
			strcpy(p->id, t->id);
			strcpy(p->submission_time, t->submission_time);
			strcpy(p->cls, t->cls);
			strcpy(p->remark, t->remark);
			strcpy(p->submission_count, t->submission_count);

			strcpy(t->course_id, new_t.course_id);
			strcpy(t->course_name, new_t.course_name);
			strcpy(t->id, new_t.id);
			strcpy(t->submission_time, new_t.submission_time);
			strcpy(t->cls, new_t.cls);
			strcpy(t->remark, new_t.remark);
			strcpy(t->submission_count, new_t.submission_count);
		}
	}

}

void saveSubmissionInformation(submission *h) {

	FILE * fp;
	if ((fp = fopen("submission.txt", "w")) == NULL)
	{
		printf("Write Error : students.txt is not existed.");
		exit(-1);
	}

	submission *p = h;

	while (p) {
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n", p->id, p->cls, p->course_name,
			p->course_id, p->submission_time, p->submission_count, p->remark);
		p = p->next;
	}
	fclose(fp);
}

#endif
