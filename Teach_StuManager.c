// 老师提供的代码编写参考
#include "StudentManagementSystem.h"

int main()
{
    // 创建头结点
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;

    loadStudent(head);

    while (1)
    {
        welcome();

        char c = _getch();

        switch (c)
        {
        case '1': // 录入学生信息
            inputStudent(head);
            break;
        case '2': // 打印学生信息
            printStudent(head);
            break;
        case '3': // 统计学生人数
            countStudent(head);
            break;
        case '4': // 查找学生信息
            findStudent(head);
            break;
        case '5': // 修改学生信息
            modifyStudent(head);
            break;
        case '6': // 删除学生信息
            deleteStudent(head);
            break;
        case '7': // 按成绩排序
            sortStudent(head);
            break;
        case '8': // 退出系统
            system("cls");
            printf("Bye bye!\n");
            exit(0);
            break;
        default:
            printf("输入错误，请重新输入：\n");
            system("pause");
            system("cls");
            break;
        }
    }
    return 0;
}

void welcome()
{
    printf("*********************************\n");
    printf("*\t学生成绩管理系统*\t\n");
    printf("*********************************\n");
    printf("*\t请选择功能列表*\t\t\n");
    printf("*********************************\n");
    printf("*\t1.录入学生信息\t\t*\n");
    printf("*\t2.打印学生信息\t\t*\n");
    printf("*\t3.统计学生人数\t\t*\n");
    printf("*\t4.查找学生信息\t\t*\n");
    printf("*\t5.修改学生信息\t\t*\n");
    printf("*\t6.删除学生信息\t\t*\n");
    printf("*\t7.按成绩排序\t\t*\n");
    printf("*\t8.退出系统\t\t*\n");
    printf("*********************************\n");
}

void inputStudent(Node *head)
{
    Node *fresh = (Node *)malloc(sizeof(Node));
    fresh->next = NULL;
    printf("请输入学生的学号，姓名，成绩：");
    scanf("%d%s%d", &fresh->student.stuNum, fresh->student.name, &fresh->student.score);

    Node *move = head;
    while (move->next != NULL)
    {
        move = move->next;
    }
    // 将创建的fresh（学生）插入到尾部
    move->next = fresh;

    saveStudent(head);

    // 暂停程序
    system("pause");
    // 清空控制台
    system("cls");
}

void printStudent(Node *head)
{
    Node *move = head->next;
    while (move != NULL)
    {
        printf("学号：%d  姓名：%4s  成绩：%3d\n", move->student.stuNum, move->student.name, move->student.score);
        move = move->next;
    }

    // 暂停程序
    system("pause");
    // 清空控制台
    system("cls");
}

void countStudent(Node *head)
{
    int count = 0;
    Node *move = head->next;
    while (move != NULL)
    {
        count++;
        move = move->next;
    }
    printf("学生的总人数为：%d\n", count);

    // 暂停程序
    system("pause");
    // 清空控制台
    system("cls");
}

void findStudent(Node *head)
{
    int stuNum;
    printf("请输入要查找学生的学号：");
    scanf("%d", &stuNum);

    Node *move = head->next;
    while (move != NULL)
    {
        if (stuNum == move->student.stuNum)
        {
            printf("学号：%d  姓名：%4s  成绩：%3d\n", move->student.stuNum, move->student.name, move->student.score);

            // 暂停程序
            system("pause");
            // 清空控制台
            system("cls");

            return;
        }
        move = move->next;
    }
    printf("未找到学生信息！\n");
}

void saveStudent(Node *head)
{
    // 打开文件
    FILE *file = fopen(".\\stu.info", "w");
    Node *move = head->next;
    while (move != NULL)
    {
        if (fwrite(&move->student, sizeof(Student), 1, file) != 1)
        {
            printf("写入失败！\n");
            return;
        }
        move = move->next;
    }
    fclose(file);
}

void loadStudent(Node *head)
{
    FILE *file = fopen(".\\stu.info", "r");
    // 如果文件为空
    if (!file)
    {
        printf("没有学生文件，跳过读取\n");
        return;
    }

    Node *fresh = (Node *)malloc(sizeof(Node));
    fresh->next = NULL;

    Node *move = head;

    while (fread(&fresh->student, sizeof(Student), 1, file) == 1)
    {
        move->next = fresh;
        move = fresh;

        fresh = (Node *)malloc(sizeof(Student));
        fresh->next = NULL;
    }
    free(fresh); // 最后多定义一个fresh，要将它释放掉
    fclose(file);
    printf("读取成功！！\n");
}

void modifyStudent(Node *head)
{
    int stuNum;
    printf("请输入要修改信息的学生的学号：");
    scanf("%d", &stuNum);

    Node *move = head->next;
    while (move != NULL)
    {
        if (move->student.stuNum == stuNum)
        {
            printf("请输入学生的姓名，成绩：");
            scanf("%s%d", move->student.name, &move->student.score);
            saveStudent(head);
            printf("修改信息成功！！\n");

            // 暂停程序
            system("pause");
            // 清空控制台
            system("cls");

            return;
        }
        move = move->next;
    }
    printf("未找到学生信息！\n");
    // 暂停程序
    system("pause");
    // 清空控制台
    system("cls");
}

void deleteStudent(Node *head)
{
    int stuNum = 0;
    printf("请输入要删除信息的学生的学号：");
    scanf("%d", &stuNum);

    Node *move = head;

    while (move->next != NULL)
    {
        if (move->next->student.stuNum == stuNum)
        {
            Node *temp = move->next;
            move->next = move->next->next;
            free(temp);
            temp = NULL; // 防止其变为野指针
            saveStudent(head);
            printf("删除信息成功！！\n");

            return;
        }
        move = move->next;
    }
    printf("未找到学生信息！\n");
    // 暂停程序
    system("pause");
    // 清空控制台
    system("cls");
}

void sortStudent(Node *head)
{
    Node *save = NULL;
    Node *move = NULL;

    for (Node *turn = head->next; turn != NULL; turn = turn->next)
    {
        for (move = head->next; move != save; move = move->next)
        {
            if (move->student.score > move->next->student.score)
            {
                Student temp = move->student;
                move->student = move->next->student;
                move->next->student = temp;
            }
        }
        save = move;
    }
    printStudent(head);
}