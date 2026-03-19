/*
① 有5个学生，每个学生有3门课程的成绩，从键盘输入学生数据（包括学号，姓名，3门课程成绩），计算出平均成绩，将原有数据和计算出的平均分数存放在磁盘文件stud中
② 将stud文件中的学生数据，按平均分进行排序处理，将已排序的学生数据存入一个新文件stu_sort中
③ 将已排序的学生成绩文件进行插入处理。插入一个学生的3门课程成绩，程序先计算新插入学生的平均成绩，然后将它按成绩高低顺序插入，插入后将结果仍存入原有的stu_sort文件而不另建立新文件
*/

#include <stdio.h>
#include <stdlib.h>

#define N 5

typedef struct _Student
{
    int id;
    char name[20];
    float class1;
    float class2;
    float class3;
    float average;
} Student;

typedef struct _Node
{
    Student student;
    struct _Node *next;
} Node;

void inputStudent(Node *head);
void saveStudent(Node *head, char *filename);
void sortStudent(Node *head, int n);
void insertStudent(Node *head);

int main()
{
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;

    inputStudent(head);
    sortStudent(head, N);
    insertStudent(head);

    return 0;
}

void inputStudent(Node *head)
{
    printf("请输入5个学生的学号，姓名，3门课程成绩：\n");

    Node *move = head;
    for (int i = 0; i < N; i++)
    {
        Node *fresh = (Node *)malloc(sizeof(Node));
        fresh->next = NULL;

        scanf("%d %s %f %f %f", &fresh->student.id, fresh->student.name, &fresh->student.class1, &fresh->student.class2, &fresh->student.class3);

        fresh->student.average = (fresh->student.class1 + fresh->student.class2 + fresh->student.class3) / 3;
        while (move->next != NULL)
        {
            move = move->next;
        }
        move->next = fresh;
        move = head;
    }

    saveStudent(head, "stud.txt");
}

void saveStudent(Node *head, char *filename)
{
    FILE *file = fopen(filename, "w");
    Node *move = head->next;
    while (move != NULL)
    {
        fprintf(file, "学号：%d  姓名：%4s  成绩1：%.1f  成绩2：%.1f  成绩3：%.1f  平均分：%.2f\n", move->student.id, move->student.name, move->student.class1, move->student.class2, move->student.class3, move->student.average);
        move = move->next;
    }
    printf("写入%s成功！！\n", filename);
    fclose(file);
}

void sortStudent(Node *head, int n)
{
    Node *move1, *move2;

    for (int i = 0; i < n - 1; i++)
    {
        move1 = head->next;
        move2 = head->next->next;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (move1->student.average > move2->student.average)
            {
                Student temp = move1->student;
                move1->student = move2->student;
                move2->student = temp;
            }
            move1 = move1->next;
            move2 = move2->next;
            if (move2 == NULL)
            {
                break;
            }
        }
    }
    saveStudent(head, "stu_sort.txt");
}

void insertStudent(Node *head)
{
    Node *move = head;
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;

    printf("输入插入学生的信息（学号，姓名，3门课程成绩）：\n");
    scanf("%d %s %f %f %f", &newNode->student.id, newNode->student.name, &newNode->student.class1, &newNode->student.class2, &newNode->student.class3);

    newNode->student.average = (newNode->student.class1 + newNode->student.class2 + newNode->student.class3) / 3;

    while (move->next != NULL)
    {
        move = move->next;
    }
    move->next = newNode;

    saveStudent(head, "stud.txt");
    sortStudent(head, N + 1);
}
