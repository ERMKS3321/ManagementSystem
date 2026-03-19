// 老师提供的代码编写参考
#include <stdio.h>
#include <stdlib.h>
#include <conio.h> // 包含 _getch

// 学生信息
typedef struct _Student
{
    int stuNum;
    char name[20];
    int score;
} Student;

// 结点信息
typedef struct _Node
{
    Student student;
    struct _Node *next;
} Node;

void welcome();
void inputStudent(Node *head);
void printStudent(Node *head);
void countStudent(Node *head);
void findStudent(Node *head);
void saveStudent(Node *head);
void loadStudent(Node *head);
void modifyStudent(Node *head);
void deleteStudent(Node *head);
void sortStudent(Node *head);