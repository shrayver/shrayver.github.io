#ifndef _CLASS
#define _CLASS
#include <stdio.h>
#include <string.h>


#define MAX_CLASS_LEN 100       //班级名字

#define MAX_CLASS_NUMBER 10     //最多创建的班级数量

char classes[MAX_CLASS_NUMBER][MAX_CLASS_LEN];
int classes_length = 0;



void readClasses() {
    FILE * fp;
    if((fp = fopen("classes.txt","r")) == NULL)
    {
        printf("Read Error : classes.txt is not existed.");
        exit(-1);
    }
    char str[MAX_CLASS_LEN];
    //int i = 0;
    while(fscanf(fp,"%s",str)!=EOF) {

        strcpy(classes[classes_length], str);

        //i++;
        classes_length++;

    }
    printf("Class information has been loaded.\n");
}

//查找班级名字，如果存在则返回班级的序号，不存在则返回-1
int searchClass(char *class_name) {

    int i=0;
    for(;i<classes_length;i++) {
        if(strcmp(classes[i], class_name)==0) {
            return i;
        }
    }
    return -1;
}


void printClassesInformation(){
    printf("Class Information is listed as follows.\n");

    int i=0;
    for(;i<classes_length;i++) {
        printf("%s\n", classes[i]);
    }
}

// 修改班级信息
int updateClass(char *class_name, char * new_class_name) {
    int i=searchClass(class_name);

    if(i>=0) {
        strcpy(classes[i], new_class_name);
        return 1;
    }
    return 0;
}

void deleteClass(char *class_name) {
    int i=searchClass(class_name);
    if(i>=0) {
        for(;i<classes_length-1;i++) {
            strcpy(classes[i], classes[i+1]);
            //classes[i] = classes[i+1];
        }
        classes_length--;
    }
}

int createClass(char * class_name) {
    strcpy(classes[classes_length], class_name);
    classes_length++;
    return 1;
}
void saveClassInformation() {

	FILE * fp;
	if ((fp = fopen("classes.txt", "w")) == NULL)
	{
		printf("Write Error : classes.txt is not existed.");
		exit(-1);
	}
	int i = 0;
	for (; i < classes_length; i++) {
		fprintf(fp, "%s\n", classes[i]);
	}
	fclose(fp);
}

#endif // _CLASS


