#include <stdio.h>
#include <string.h>
#include "students.h"
#include "class.h"
#include "homework.h"
#include "submission.h"


int role = 0;  //0 管理员，1 学委 2 学生
char password[100];
char student_id[100];

student * student_list = NULL;
homework * homework_list = NULL;
submission * submission_list = NULL;



void initInformation() {
	readClasses();
	readStudents(&student_list);
	readHomework(&homework_list);
	readSubmission(&submission_list);
}

void saveInformation() {
	saveClassInformation();
	saveStudentInformation(student_list);
	saveHomeworkInformation(homework_list);
	saveSubmissionInformation(submission_list);
}

void administratorOperateClasses(){
    while(1) {
        printf("------------------------------------------------------------------------\n");
        printf("Please choose the class operation.\n");
        printf("Input 0 : Print class information.\n");
        printf("Input 1 : Create class.\n");
        printf("Input 2 : Delete class.\n");
        printf("Input 3 : Update class.\n");
        printf("Input 4 : Search class.\n");
        printf("Input 5 : Back to upper lever.\n");
        int buf;
        scanf("%d",&buf);
        char class_name[100];
        if(buf==0) {
            printClassesInformation();
        }
        else if(buf==1) {
            printf("Input the class name you want to create : ");

            scanf("%s", class_name);
            createClass(class_name);
            printf("The class %s has been created.\n", class_name);
        }
        //TODO
        else if(buf == 2) {
            printf("Input the class name you want to delete : ");
            scanf("%s", class_name);
            deleteClass(class_name);
            printf("The class %s has been deleted.\n", class_name);

        }
        //TODO
        else if(buf == 3) {
            printf("Input the class name you want to update : ");
            scanf("%s", class_name);
            char new_class_name[100];
            printf("Input new class name you want to update : ");
            scanf("%s", new_class_name);
            updateClass(class_name, new_class_name);
            printf("The class %s has been updated to %s.\n", class_name, new_class_name);
        }
        else if(buf == 4) {
            printf("Input the class name you want to search : ");
            scanf("%s", class_name);
            if(searchClass(class_name)>=0) {
                printf("The class %s is existed.\n", class_name);
            }
            else {
                printf("The class %s is not existed.\n", class_name);
            }
        }
        else if(buf == 5) {
            break;
        }
        else {
            printf("Input Error : Please input again.\n");
        }

    }

}

void administratorOperateStudents() {
    while(1) {
        printf("------------------------------------------------------------------------\n");
        printf("Please choose the students operation.\n");
        printf("Input 0 : Print students information.\n");
        printf("Input 1 : Add student.\n");
        printf("Input 2 : Delete student.\n");
        printf("Input 3 : Update student.\n");
        printf("Input 4 : Search student.\n");
        printf("Input 5 : Back to upper lever.\n");
        int buf;
        scanf("%d",&buf);
        char student_id[100];
        char student_name[100];
        char student_cls[100];
        student t;
        if(buf==0) {
            //printClassesInformation();
            printStudentsInformation(student_list);
        }
        else if(buf==1) {

            printf("Input the student id you want to add : ");
            scanf("%s", t.id);
            printf("Input the student class : ");
            scanf("%s", t.cls);
            printf("Input the student name you want to add : ");
            scanf("%s", t.name);
            //createClass(class_name);
            addStudent(&student_list, &t);
            printf("The student %s has been created.\n", t.id);
        }
        else if(buf == 2) {
            printf("Input the student id you want to delete : ");
            scanf("%s", t.id);
            deleteStudent(&student_list, t.id);
            //deleteClass(class_name);
            printf("The student %s has been deleted.\n", t.id);

        }
        else if(buf == 3) {
            printf("Input the student id you want to update : ");
            scanf("%s", t.id);
            printf("Input the student class you want to update : ");
            scanf("%s", t.cls);
            printf("Input new student name you want to update : ");
            scanf("%s", t.name);
            //updateClass(class_name, new_class_name);
            updateStudent(&student_list, t.id, &t);
            printf("The student %s has been updated.\n", t.id);
        }
        else if(buf == 4) {
            printf("Input the student name you want to search : ");
            scanf("%s", t.id);
            student * buf_s = searchStudent(&student_list, t.id);
            if(buf_s!=NULL) {
                printf("The student information is as follows : \n");
                printf("%s\t%s\t%s\n", buf_s->id, buf_s->cls, buf_s->name);
            }
            else {
                printf("The student %s is not existed.\n", t.id);
            }
        }
        else if(buf == 5) {
            break;
        }
        else {
            printf("Input Error : Please input again.\n");
        }

    }


}

void administratorOperateRoles() {
     while(1) {
        printf("------------------------------------------------------------------------\n");
        printf("Please choose the roles operation.\n");
        printf("Input 0 : Print the commissaries information.\n");
        //printf("Input 1 : Set commissary.\n");
        //printf("Input 2 : Delete commissary.\n");
        printf("Input 1 : Back to upper lever.\n");
        int buf;
        scanf("%d",&buf);

        if(buf==0) {
            //printClassesInformation();
            //printStudentsInformation(student_list);
            int i=0;
            printf("The commissary information is as follows : \nclass\tpassword\n");
            for(;i<classes_length;i++) {
                printf("%s\t123456\n",classes[i]);
            }
        }
        else if(buf==1) {

            break;
        }
        else {
            printf("Input Error : Please input again.\n");
        }
    }

}

void administratorOperation() {
    while(1) {

        printf("------------------------------------------------------------------------\n");
        printf("Please choose the administrator operation.\n");
        printf("Input 0 : Classes.\n");
        printf("Input 1 : Students.\n");
        printf("Input 2 : Roles.\n");
        printf("Input 3 : Exit.\n");

        int buf;
        scanf("%d",&buf);

        if(buf==0) {

            administratorOperateClasses();
            continue;
        }
        else if(buf == 1){
            administratorOperateStudents();
            //printf("------------------------------------------------------------------------\n");

            continue;
        }
        else if (buf == 2) {
            //printf("------------------------------------------------------------------------\n");
            administratorOperateRoles();
            continue;
        }
        else if( buf == 3) {
			saveInformation();
            printf("Exiting the system.\n");
            break;
        }
        else {
            printf("Input Error. Please input again.\n");
            continue;
        }
    }
}

void administratorLogin() {



    printf("------------------------------------------------------------------------\n");
    printf("You are ready to login with the role of administrator. Please input password.\n");
    printf("Password: ");
    char password[100];
    scanf("%s",password);

    if(strcmp(password, "123456")==0) {
        printf("Login successfully.\n");
        printf("------------------------------------------------------------------------\n");

        administratorOperation();

    }
    else {
        printf("Password Error. Login failed. Exiting the system.");
        exit(-1);
    }
}

void commissaryOperateHomeworkPrint() {
    while(1) {
        printf("------------------------------------------------------------------------\n");
        printf("Please choose the students operation.\n");
        printf("Input 0 : Print all homework information.\n");
        printf("Input 1 : Print homework limited with course name.\n");
        printf("Input 2 : Print homework limited with date.\n");
        printf("Input 3 : Sort and print in ascending order.\n");
        printf("Input 4 : Sort and print in descending order.\n");
        printf("Input 5 : Back to upper lever.\n");
        int buf;
        scanf("%d",&buf);
        if(buf==0) {
            //printClassesInformation();
            //printStudentsInformation(student_list);
            //homework_list = bubbleSort(homework_list);
            selectSort(&homework_list, courseIDCompare);
            printHomeworkInformation(homework_list);
            //commissaryOperateHomeworkPrint();
        }
        else if(buf==1) {
            char buf[100];
            printf("Input the course name you want to search : ");
            scanf("%s", buf);
            searchAndPrintHomework1(homework_list, buf);
        }
        else if(buf == 2) {
            char start_time[100], end_time[100];
            printf("Input the start date you want to filter (For example : 20200410): ");
            scanf("%s", start_time);

            printf("Input the end date you want to filter (For example : 20200610): ");
            scanf("%s", end_time);

            searchAndPrintHomework2(homework_list, start_time, end_time);

        }
        else if(buf == 3) {
            //homework_list = bubbleSort2(homework_list);
            selectSort(&homework_list, dateAscending);
            printHomeworkInformation(homework_list);
        }
        else if (buf == 4) {
            //homework_list = bubbleSort1(homework_list);
            selectSort(&homework_list, dateDescending);
            printHomeworkInformation(homework_list);
        }
        else if(buf == 5) {

            break;
        }
        else {
            printf("Input Error : Please input again.\n");
        }

    }
}

void commissaryOperateHomework() {
    while(1) {
        printf("------------------------------------------------------------------------\n");
        printf("Please choose the homework operation.\n");
        printf("Input 0 : Print homework information.\n");
        printf("Input 1 : Add homework.\n");
        printf("Input 2 : Delete homework.\n");
        printf("Input 3 : Update homework.\n");
        printf("Input 4 : Search homework.\n");
        printf("Input 5 : Back to upper lever.\n");
        int buf;
        scanf("%d",&buf);
        homework t;
        if(buf==0) {
            //printClassesInformation();
            //printStudentsInformation(student_list);

            commissaryOperateHomeworkPrint();
            //printHomeworkInformation(homework_list);
        }
        else if(buf==1) {

            printf("Input the homework id you want to add (For example : E01): ");
            scanf("%s", t.course_id);
            printf("Input the course name (For example : English): ");
            scanf("%s", t.course_name);
            printf("Input the times you want to add (For example : 3): ");
            scanf("%s", t.times);

            printf("Input the details you want to add (For example : job_1): ");
            scanf("%s", t.details);
            printf("Input the date you want to add (For example : 20200509): ");
            scanf("%s", t.date);
            printf("Input the deadline you want to add (For example : 20200610): ");
            scanf("%s", t.deadline);
            printf("Input the remark you want to add (For example : NO) : ");
            scanf("%s", t.remark);
            //createClass(class_name);
            //addStudent(&student_list, &t);
            addHomework(&homework_list, &t);
            printf("The homework %s has been created.\n", t.course_id);
        }
        else if(buf == 2) {
            printf("Input the homework id you want to delete : ");
            scanf("%s", t.course_id);
            //deleteStudent(&student_list, t.id);
            //deleteClass(class_name);
            deleteHomework(&homework_list, t.course_id);
            printf("The homework %s has been deleted.\n", t.course_id);

        }
        else if(buf == 3) {
            printf("Input the homework id you want to update (For example : E01): ");
            scanf("%s", t.course_id);
            printf("Input new course name you want to update (For example : English): ");
            scanf("%s", t.course_name);
            printf("Input new times you want to update (For example : 3): ");
            scanf("%s", t.times);

            printf("Input new details you want to update (For example : job_1): ");
            scanf("%s", t.details);
            printf("Input new date you want to update (For example : 20200509): ");
            scanf("%s", t.date);
            printf("Input new deadline you want to update (For example : 20200610): ");
            scanf("%s", t.deadline);
            printf("Input new remark you want to update (For example : NO) : ");
            scanf("%s", t.remark);
            //updateClass(class_name, new_class_name);
            updateHomework(&homework_list, t.course_id, &t);
            printf("The homework %s has been updated.\n", t.course_id);
        }
        else if(buf == 4) {
            printf("Input the homework id you want to search : ");
            scanf("%s", t.course_id);
            homework * p = searchHomework(&homework_list, t.course_id);
            if(p!=NULL) {
                printf("The homework information is as follows : \n");
                printf("%s %s %s %s %s %s %s\n", p->course_id, p->course_name, p->times,
                p->details, p->date, p->deadline, p->remark);
            }
            else {
                printf("The homework %s is not existed.\n", t.course_id);
            }
        }
        else if(buf == 5) {
            break;
        }
        else {
            printf("Input Error : Please input again.\n");
        }

    }

}

void commissaryOperateSubmissionSearch() {
	
	while (1) {
		printf("------------------------------------------------------------------------\n");
		printf("Please choose the submission searching operation.\n");
		printf("Input 0 : Search all submissions.\n");
		printf("Input 1 : Search all submissions within a time period.\n");
		printf("Input 2 : Search all submissions by course name.\n");
		printf("Input 3 : Search all submissions of a student by student id.\n");
		printf("Input 4 : Back to upper lever.\n");
		int buf;
		scanf("%d", &buf);
		submission t;
		if (buf == 0) {
			printSubmissionInformation(submission_list);
		}
		else if (buf == 1) {
			char start_time[100], end_time[100];
			printf("Input the start date you want to filter (For example : 20200410): ");
			scanf("%s", start_time);

			printf("Input the end date you want to filter (For example : 20200610): ");
			scanf("%s", end_time);

			searchAndPrintSubmissionInTime(submission_list, start_time, end_time);
		}
		else if (buf == 2) {
			printf("Input the course name you want to filter : ");
			scanf("%s", t.course_name);
			
			searchAndPrintSubmissionInCourseName(submission_list, t.course_name);
			
			printf("The homework %s has been deleted.\n", t.course_name);

		}
		else if (buf == 3) {
			printf("Input the course name you want to filter : ");
			scanf("%s", t.id);

			searchAndPrintSubmissionInStudentID(submission_list, t.id);
		}
		else if (buf == 4) {
			
			break;
		}
		else {
			printf("Input Error : Please input again.\n");
		}
	}

}


void commissaryOperateSubmissionPrint() {
	while (1) {
		printf("------------------------------------------------------------------------\n");
		printf("Please choose the submission printing operation.\n");
		printf("Input 0 : Print all submission information.\n");
		printf("Input 1 : Print all submission in ascending order by submision count.\n");
		printf("Input 2 : Print all submission in descending order by submision count.\n");
		printf("Input 3 : Print all submission in ascending order by submision date.\n");
		printf("Input 4 : Print all submission in descending order by submision date.\n");
		printf("Input 5 : Back to upper lever.\n");
		int buf;
		scanf("%d", &buf);
		submission t;
		if (buf == 0) {
			//commissaryOperateSubmissionPrint();
			selectSortSubmission(&submission_list, ascendingID);
			printSubmissionInformation(submission_list);
		}
		else if (buf == 1) {
			selectSortSubmission(&submission_list, ascendingCount);
			printSubmissionInformation(submission_list);
		}
		else if (buf == 2) {
			selectSortSubmission(&submission_list, descendingCount);
			printSubmissionInformation(submission_list);
		}
		else if (buf == 3) {
			selectSortSubmission(&submission_list, ascendingDate);
			printSubmissionInformation(submission_list);
		}
		else if (buf == 4) {
			selectSortSubmission(&submission_list, descendingDate);
			printSubmissionInformation(submission_list);
		}
		else if (buf == 5) {
			break;
		}
		else {
			printf("Input Error : Please input again.\n");
		}
	}

	printSubmissionInformation(submission_list);
}

void commissaryOperateSubmission() {

     while(1) {
        printf("------------------------------------------------------------------------\n");
        printf("Please choose the submission operation.\n");
        printf("Input 0 : Print all submission information.\n");
        printf("Input 1 : Add submission.\n");
        printf("Input 2 : Delete submission.\n");
        printf("Input 3 : Update submission.\n");
        printf("Input 4 : Search submission.\n");
        printf("Input 5 : Back to upper lever.\n");
        int buf;
        scanf("%d",&buf);
        submission t;
        if(buf==0) {

			commissaryOperateSubmissionPrint();

        }
        else if(buf==1) {

            printf("Input the submission student id you want to add (For example : I000006): ");
            scanf("%s", t.id);
            printf("Input the class name you want to add (For example : A): ");
            scanf("%s", t.cls);
            printf("Input the course name you want to add (For example : math): ");
            scanf("%s", t.course_name);

            printf("Input the homework id you want to add (For example : m11): ");
            scanf("%s", t.course_id);
            printf("Input the submission date you want to add (For example : 20200509): ");
            scanf("%s", t.submission_time);
            printf("Input the submission count you want to add (For example : 3): ");
            scanf("%s", t.submission_count);
            printf("Input the remark you want to add (For example : NO) : ");
            scanf("%s", t.remark);
            //createClass(class_name);
            //addStudent(&student_list, &t);
            //addHomework(&homework_list, &t);
			addSubmisson(&submission_list, &t);
            printf("The submission %s has been created.\n", t.course_id);
        }
        else if(buf == 2) {
            printf("Input the submission student id you want to delete : ");
            scanf("%s", t.id);
			printf("Input the submission homework id you want to delete : ");
			scanf("%s", t.course_id);

			deleteSubmission(&submission_list, t.id, t.course_id);
            //deleteStudent(&student_list, t.id);
            //deleteClass(class_name);
            //deleteHomework(&homework_list, t.course_id);
            printf("The submission %s and %s has been deleted.\n", t.id, t.course_id);

        }
        else if(buf == 3) {
			printf("Input the submission student id you want to update (For example : I000006): ");
			scanf("%s", t.id);
			printf("Input the class name you want to update (For example : A): ");
			scanf("%s", t.cls);
			printf("Input the course name you want to update (For example : math): ");
			scanf("%s", t.course_name);

			printf("Input the homework id you want to update (For example : m11): ");
			scanf("%s", t.course_id);
			printf("Input new submission date you want to update (For example : 20200509): ");
			scanf("%s", t.submission_time);
			printf("Input new submission count you want to update (For example : 3): ");
			scanf("%s", t.submission_count);
			printf("Input new remark you want to update (For example : NO) : ");
			scanf("%s", t.remark);
            //updateClass(class_name, new_class_name);
            //updateHomework(&homework_list, t.course_id, &t);
			updateSubmission(&submission_list, t.id, t.course_id, &t);
            printf("The homework %s has been updated.\n", t.course_id);
        }
        else if(buf == 4) {
			commissaryOperateSubmissionSearch();
        }
        else if(buf == 5) {
            break;
        }
        else {
            printf("Input Error : Please input again.\n");
        }
    }
}


void commissaryOperation() {
    while(1) {

        printf("------------------------------------------------------------------------\n");
        printf("Please choose the commissary operation.\n");
        printf("Input 0 : Homework.\n");
        printf("Input 1 : Submission.\n");
        printf("Input 2 : Exit.\n");

        int buf;
        scanf("%d",&buf);

        if(buf==0) {

            commissaryOperateHomework();
            continue;
        }
        else if(buf == 1){
            commissaryOperateSubmission();
            continue;
        }
        else if (buf == 2) {
			saveInformation();
            printf("Exiting the system.\n");
            break;
        }
        else {
            printf("Input Error. Please input again.\n");
            continue;
        }
    }


}

void commissaryLogin() {
    printf("------------------------------------------------------------------------\n");
    printf("You are ready to login with the role of commissary. Please input password.\n");
    printf("Password: ");
    char password[100];
    scanf("%s",password);

    if(strcmp(password, "123456")==0) {
        printf("Login successfully.\n");
        printf("------------------------------------------------------------------------\n");

        commissaryOperation();
    }
    else {
        printf("Password Error. Login failed. Exiting the system.");
        exit(-1);
    }
}


void studentViewHomework() {
	commissaryOperateHomeworkPrint();
}
void studentViewOwnHomework() {
	searchAndPrintSubmission(submission_list, student_id);
}
void studentOperation() {
	while (1) {
		printf("------------------------------------------------------------------------\n");
		printf("Please choose the student operation.\n");
		printf("Input 0 : View homework.\n");
		printf("Input 1 : Search the submission of your own homework.\n");
		printf("Input 2 : Exit.\n");

		int buf;
		scanf("%d", &buf);

		if (buf == 0) {
			studentViewHomework();
		}
		else if (buf == 1) {
			studentViewOwnHomework();
		}
		else if (buf == 2) {
			saveInformation();
			printf("Exiting the system.\n");
			break;
		}
		else {
			printf("Input Error. Please input again.\n");
		}
	}
}

void studentLogin(){
    printf("------------------------------------------------------------------------\n");
    printf("You are ready to login with the role of students. Please input your student id and password.\n");
    printf("Students id: ");
    scanf("%s", student_id);

    //放置初始化所有结构体内
    //initStudentsList();
    //printStudentsInformation(student_list);
    if(searchStudent(&student_list, student_id)==NULL) {
        printf("The student is not existed in the system. Please contact the administrator.\n");
        exit(-1);
    }
    printf("Password: ");
    char password[100];
    scanf("%s",password);

    if(strcmp(password, "123456")==0) {
        printf("Login successfully.\n");
        printf("------------------------------------------------------------------------\n");

		studentOperation();

    }
    else {
        printf("Password error. Login failed. Exiting the system.");
        exit(-1);
    }
}



void login() {
    printf("------------------------------------------------------------------------\n");
    printf("Welcome to the operation information management system of the committee.\n");
    printf("------------------------------------------------------------------------\n");


    initInformation();

    while(1) {
        printf("Please confirm your role : \n");
        printf("Input 0 : Administrator.\n");
        printf("Input 1 : Commissary.\n");
        printf("Input 2 : Student.\n");
        scanf("%d", &role);
        if(role==0){
            administratorLogin();
            break;
        }
        else if (role == 1) {
            commissaryLogin();
            break;
        }
        else if (role == 2) {
            studentLogin();
            break;
        }
        else {
            printf("Input Error : Please input again.\n");
        }
    }

}


int main() {

    login();

    return 0;

}

