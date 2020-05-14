#ifndef _HOMEWORK
#define _HOMEWORK
#include <stdio.h>
#include <time.h>

#define MAX_HOMEWORK_STRING_LEN 100
typedef struct HOMMEWORK{
    char course_id[MAX_HOMEWORK_STRING_LEN];        //作业编号
    char course_name[MAX_HOMEWORK_STRING_LEN];       //课程名
    char times[MAX_HOMEWORK_STRING_LEN];      //作业次数，第几次
    char details[MAX_HOMEWORK_STRING_LEN];     //作业内容
    char date[MAX_HOMEWORK_STRING_LEN];         //布置时间
    char deadline[MAX_HOMEWORK_STRING_LEN];     //截至时间
    char remark[MAX_HOMEWORK_STRING_LEN];       //备注
    struct HOMMEWORK *next;
}homework;


int getNowTime(char *nowTime)
{
	char acYear[5] = {0};
	char acMonth[5] = {0};
	char acDay[5] = {0};
	//char acHour[5] = {0};
	//char acMin[5] = {0};
	//char acSec[5] = {0};

	time_t now;
    struct tm* timenow;

    time(&now);
    timenow = localtime(&now);

    strftime(acYear,sizeof(acYear),"%Y",timenow);
    strftime(acMonth,sizeof(acMonth),"%m",timenow);
    strftime(acDay,sizeof(acDay),"%d",timenow);
    //strftime(acHour,sizeof(acHour),"%H",timenow);
    //strftime(acMin,sizeof(acMin),"%M",timenow);
    //strftime(acSec,sizeof(acSec),"%S",timenow);

	strncat(nowTime, acYear, 4);
	strncat(nowTime, acMonth, 2);
	strncat(nowTime, acDay, 2);
	//strncat(nowTime, acHour, 2);
	//strncat(nowTime, acMin, 2);
	//strncat(nowTime, acSec, 2);
	return 0;
}

void printHomework(homework *p) {
	printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\n", p->course_id, p->course_name, p->times,
		p->details, p->date, p->deadline, p->remark);
}

void readHomework(homework **head) {
    FILE * fp;
    if((fp = fopen("homework.txt","r")) == NULL)
    {
        printf("Read Error : homework.txt is not existed.");
        exit(-1);
    }

    *head = (homework*)malloc(sizeof(homework));

    printf("test\n");
    homework *p = *head, *tail;
    char str[MAX_HOMEWORK_STRING_LEN];
    while(fscanf(fp,"%s",str)!=EOF) {
        tail = (homework*)malloc(sizeof(homework));
        strcpy(tail->course_id, str);
        fscanf(fp, "%s", tail->course_name);

        fscanf(fp, "%s", tail->times);
        fscanf(fp, "%s", tail->details);
        //printf("%s%s%s\n", tail->course_id, tail->course_name, tail->details);
        fscanf(fp, "%s", tail->date);
        fscanf(fp, "%s", tail->deadline);
        fscanf(fp, "%s", tail->remark);

        tail->next = NULL;

        p->next = tail;
        p = p->next;

    }
    *head = (*head)->next;

}

homework* searchHomework(homework ** h, char *course_id) {
    homework *p = *h;
    while(p) {
        if (strcmp(course_id, p->course_id)==0) {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

int searchAndPrintHomework1(homework *h , char *course_name) {
    printf("Homework Information with course name %s is listed as follows.\n", course_name);
    homework *p = h;
    int flag = 0;
    while(p) {
        if(strcmp(course_name, p->course_name)==0) {
            /*printf("%s %s %s %s %s %s %s\n", p->course_id, p->course_name, p->times,
                    p->details, p->date, p->deadline, p->remark);*/
			printHomework(p);
            flag = 1;
        }
        p = p->next;
    }
    return flag;
}

int searchAndPrintHomework2(homework *h, char * start_date, char * end_date) {
    printf("Homework Information in date from %s to %s is listed as follows.\n", start_date, end_date);
    homework *p = h;
    int flag = 0;
    while(p) {
        if(strcmp(p->date, start_date)>=0 && strcmp(p->deadline, end_date)<=0) {
           /* printf("%s %s %s %s %s %s %s\n", p->course_id, p->course_name, p->times,
                    p->details, p->date, p->deadline, p->remark);*/
			printHomework(p);
            flag = 1;
        }
        p = p->next;
    }
    return flag;

}



int updateHomework(homework ** h, char * id, homework* t) {

    homework * p = searchHomework(h, id);
    if(p) {
        strcpy(p->course_id, t->course_id);
        strcpy(p->course_name, t->course_name);
        strcpy(p->times, t->times);
        //p->times = t->times;
        strcpy(p->details, t->details);
        strcpy(p->date, t->date);
        strcpy(p->remark, t->remark);
        strcpy(p->deadline, t->deadline);
        return 1;
    }
    return 0;
}
void deleteHomework(homework ** h, char *course_id) {

    homework *p = *h;
    if(strcmp(course_id, p->course_id)==0) {
        (*h) = (*h)->next;
        return;
    }
    //pre = h;
    //p = p->next;

    while(p->next) {
        if (strcmp(course_id, p->next->course_id)==0) {
            p->next = p->next->next;
        }
        else {
            p = p->next;
        }
    }

}

int addHomework(homework ** h, homework* t) {
    //printf("test\n");
    homework *p = *h;
    while(p->next) {
        p = p->next;
    }

    //t->next = NULL;
    homework *new_t;
    new_t = (homework*)malloc(sizeof(homework));

    strcpy(new_t->course_id, t->course_id);
    strcpy(new_t->course_name, t->course_name);
    //new_t->times = t->times;
    strcpy(new_t->times, t->times);
    strcpy(new_t->details, t->details);
    strcpy(new_t->date, t->date);
    strcpy(new_t->remark, t->remark);
    strcpy(new_t->deadline, t->deadline);

    new_t->next = NULL;
    p->next = new_t;
    //printf("%s\t%s\t%s\n", t->id, t->cls, t->name);

    return 1;
}

void printHomeworkInformation(homework * h){
    printf("Homework Information is listed as follows.\n");
    homework *p = h;
    while(p) {
        /*printf("%s %s %s %s %s %s %s\n", p->course_id, p->course_name, p->times,
                p->details, p->date, p->deadline, p->remark);*/
		printHomework(p);
        p = p->next;
    }
}


int courseIDCompare(homework* a, homework *b){
    if(strcmp(a->course_id,b->course_id)>0) return 1;
    else return 0;
}

int dateAscending(homework *a, homework * b) {
    if(strcmp(a->date,b->date)>0) return 1;
    else return 0;
}
int dateDescending(homework *a, homework * b) {
    if(strcmp(a->date,b->date)<0) return 1;
    else return 0;
}



// 1. 直接选择排序   ------直接交换数据
void selectSort(homework **head, int (*func_p)(homework* , homework* )) {
    homework *p = NULL;
    homework *q = NULL;
    homework *t = NULL;

    if(*head == NULL || (*head)->next == NULL) {
        return;
    }
    for (p=*head;p!=NULL;p = p->next) {
        t = p;
        for(q = p->next;q!=NULL;q = q->next) {
            if (func_p(q, t)>0) {
            //if (strcmp(q->course_id, t->course_id)>0) {
                t = q;
            }
        }
        if(t != p)
        {
            homework new_t;
            strcpy(new_t.course_id, p->course_id);
            strcpy(new_t.course_name, p->course_name);
            strcpy(new_t.times, p->times);
            strcpy(new_t.details, p->details);
            strcpy(new_t.date, p->date);
            strcpy(new_t.remark, p->remark);
            strcpy(new_t.deadline, p->deadline);

            strcpy(p->course_id, t->course_id);
            strcpy(p->course_name, t->course_name);
            strcpy(p->times, t->times);
            strcpy(p->details, t->details);
            strcpy(p->date, t->date);
            strcpy(p->remark, t->remark);
            strcpy(p->deadline, t->deadline);

            strcpy(t->course_id, new_t.course_id);
            strcpy(t->course_name, new_t.course_name);
            strcpy(t->times, new_t.times);
            strcpy(t->details, new_t.details);
            strcpy(t->date, new_t.date);
            strcpy(t->remark, new_t.remark);
            strcpy(t->deadline, new_t.deadline);
        }
    }

}

void saveHomeworkInformation(homework *h) {

	FILE * fp;
	if ((fp = fopen("homework.txt", "w")) == NULL)
	{
		printf("Write Error : students.txt is not existed.");
		exit(-1);
	}

	homework *p = h;

	while (p) {
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\n", p->course_id, p->course_name, p->times,
			p->details, p->date, p->deadline, p->remark);
		p = p->next;
	}
	fclose(fp);
}


#endif
