/*
学生信息管理系统设计
实现以下功能：
1) 系统以菜单方式工作；
2) 学生信息录入功能（学生信息用文件保存）；".//stu.txt"
3) 学生信息浏览功能；
4) 查询、排序功能（至少两种查询依据和两种排序依据）；
5) 学生信息删除、修改功能。
备注：学生信息包括：学号，姓名，年龄，性别，出生年月，地址，电话，E-mail等。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 学生信息
typedef struct _Student
{
    int stuNum;
    char name[20];
    int age;
    char gender[20];
    char birth[20];
    char address[30];
    char phoneNum[20];
    char Email[20];
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
void findStudentByStuNum(Node *head);
void findStudentByName(Node *head);
void saveStudent(Node *head, char *filename);
void loadStudent(Node *head);
void modifyStudent(Node *head);
void deleteStudent(Node *head);
void sortStudentByStuNum(Node *head);
void sortStudentByBirth(Node *head);
void clearInputBuffer();
void freeList(Node *head);

int main()
{
    // 创建头结点
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;

    loadStudent(head);

    while (1)
    {
        welcome();

        char c = getchar(); // 获取单个字符
        clearInputBuffer(); // 清空输入缓冲区

        switch (c)
        {
        case '1': // 录入学生信息
            inputStudent(head);
            break;
        case '2': // 打印学生信息
            printStudent(head);
            break;
        case '3': // 按学号查找学生信息
            findStudentByStuNum(head);
            break;
        case '4': // 按姓名查找学生信息
            findStudentByName(head);
            break;
        case '5': // 修改学生信息
            modifyStudent(head);
            break;
        case '6': // 删除学生信息
            deleteStudent(head);
            break;
        case '7': // 按学号排序
            sortStudentByStuNum(head);
            break;
        case '8': // 按出生年月排序
            sortStudentByBirth(head);
            break;
        case '9': // 退出系统
            system("cls");
            printf("Bye bye!\n");
            freeList(head);
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
    printf("***********************************\n");
    printf("*        学生信息管理系统       *\n");
    printf("***********************************\n");
    printf("*        请选择功能列表         *\n");
    printf("***********************************\n");
    printf("*     1.录入学生信息            *\n");
    printf("*     2.打印学生信息            *\n");
    printf("*     3.按学号查找学生信息      *\n");
    printf("*     4.按姓名查找学生信息      *\n");
    printf("*     5.修改学生信息            *\n");
    printf("*     6.删除学生信息            *\n");
    printf("*     7.按学号排序              *\n");
    printf("*     8.按出生年月排序          *\n");
    printf("*     9.退出系统                *\n");
    printf("***********************************\n");
    printf("请选择操作(1-9): ");
}

void inputStudent(Node *head)
{
    Node *fresh = (Node *)malloc(sizeof(Node));
    fresh->next = NULL;
    // 输入学生信息
    printf("请输入学生信息：\n");
    printf("学号: ");
    scanf("%d", &fresh->student.stuNum);

    printf("姓名: ");
    scanf("%19s", fresh->student.name);

    printf("年龄: ");
    scanf("%d", &fresh->student.age);

    printf("性别: ");
    scanf("%19s", fresh->student.gender);

    printf("出生年月(YYYY-MM-DD): ");
    scanf("%19s", fresh->student.birth);

    printf("地址: ");
    scanf("%49s", fresh->student.address);

    printf("电话: ");
    scanf("%19s", fresh->student.phoneNum);

    printf("E-mail: ");
    scanf("%19s", fresh->student.Email);

    clearInputBuffer(); // 清空输入缓冲区

    Node *move = head;
    while (move->next != NULL)
    {
        move = move->next;
    }
    // 将创建的fresh（学生）插入到尾部
    move->next = fresh;

    saveStudent(head, ".\\stu.txt");

    clearInputBuffer(); // 清空输入缓冲区

    // 暂停程序
    system("pause");
    // 清空控制台
    system("cls");
}

void printStudent(Node *head)
{
    printf("\n%-10s %-20s %-5s %-10s %-15s %-30s %-15s %-20s\n",
           "学号", "姓名", "年龄", "性别", "出生日期", "地址", "电话", "Email");
    printf("------------------------------------------------------------------------------------------------\n");

    Node *move = head->next;
    while (move != NULL)
    {
        printf("%-10d %-20s %-5d %-10s %-15s %-30s %-15s %-20s\n",
               move->student.stuNum,
               move->student.name,
               move->student.age,
               move->student.gender,
               move->student.birth,
               move->student.address,
               move->student.phoneNum,
               move->student.Email);
        move = move->next;
    }
    printf("------------------------------------------------------------------------------------------------\n");

    // 暂停程序
    system("pause");
    // 清空控制台
    system("cls");
}

void findStudentByStuNum(Node *head)
{
    int stuNum;
    printf("请输入要查找学生的学号：");
    scanf("%d", &stuNum);
    clearInputBuffer(); // 清空输入缓冲区

    Node *move = head->next;
    while (move != NULL)
    {
        if (stuNum == move->student.stuNum)
        {
            printf("学号: %d 姓名: %19s 年龄: %d "
                   "性别: %19s 出生年月(YYYY-MM-DD): %19s "
                   "地址: %49s 电话: %19s E-mail: %19s",
                   move->student.stuNum,
                   move->student.name,
                   move->student.age,
                   move->student.gender,
                   move->student.birth,
                   move->student.address,
                   move->student.phoneNum,
                   move->student.Email);

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

void findStudentByName(Node *head)
{
    char name[20];
    printf("请输入要查找学生的姓名：");
    scanf("%s", name);
    clearInputBuffer(); // 清空输入缓冲区

    Node *move = head->next;
    while (move != NULL)
    {
        if (strcmp(name, move->student.name) == 0)
        {
            printf("学号: %d 姓名: %19s 年龄: %d "
                   "性别: %19s 出生年月(YYYY-MM-DD): %19s "
                   "地址: %49s 电话: %19s E-mail: %19s",
                   move->student.stuNum,
                   move->student.name,
                   move->student.age,
                   move->student.gender,
                   move->student.birth,
                   move->student.address,
                   move->student.phoneNum,
                   move->student.Email);

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

void saveStudent(Node *head, char *filename)
{
    FILE *file = fopen(filename, "w");
    Node *move = head->next;
    while (move != NULL)
    {
        fprintf(file, "%d %s %d %s %s %s %s %s\n",
                move->student.stuNum,
                move->student.name,
                move->student.age,
                move->student.gender,
                move->student.birth,
                move->student.address,
                move->student.phoneNum,
                move->student.Email);
        move = move->next;
    }
    printf("写入%s成功！！\n", filename);
    fclose(file);
}

void loadStudent(Node *head)
{
    FILE *file = fopen(".\\stu.txt", "r");
    // 如果文件为空
    if (!file)
    {
        printf("没有学生文件，跳过读取\n");
        return;
    }

    Node *move = head; // 移动指针，用于链表连接

    while (1)
    {
        Node *fresh = (Node *)malloc(sizeof(Node));
        fresh->next = NULL;

        // 使用 fscanf 读取文本数据
        int readResult = fscanf(file, "%d %19s %d %19s %19s %49s %19s %19s",
                                &fresh->student.stuNum,
                                fresh->student.name,
                                &fresh->student.age,
                                fresh->student.gender,
                                fresh->student.birth,
                                fresh->student.address,
                                fresh->student.phoneNum,
                                fresh->student.Email);

        // 如果读取失败（EOF 或格式不匹配），释放 fresh 并退出循环
        if (readResult != 8)
        {
            free(fresh);
            break;
        }

        // 连接链表
        move->next = fresh;
        move = fresh;
    }

    fclose(file);
    printf("读取成功！！\n");
}

void modifyStudent(Node *head)
{
    int stuNum;
    printf("请输入要修改信息的学生的学号：");
    scanf("%d", &stuNum);
    clearInputBuffer(); // 清空输入缓冲区

    Node *move = head->next;
    while (move != NULL)
    {
        if (move->student.stuNum == stuNum)
        {
            printf("请输入学生的");
            printf("姓名: ");
            scanf("%19s", move->student.name);

            printf("年龄: ");
            scanf("%d", &move->student.age);

            printf("性别: ");
            scanf("%19s", move->student.gender);

            printf("出生年月(YYYY-MM-DD): ");
            scanf("%19s", move->student.birth);

            printf("地址: ");
            scanf("%49s", move->student.address);

            printf("电话: ");
            scanf("%19s", move->student.phoneNum);

            printf("E-mail: ");
            scanf("%19s", move->student.Email);

            saveStudent(head, ".//stu.txt");
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
    clearInputBuffer(); // 清空输入缓冲区

    Node *move = head;

    while (move->next != NULL)
    {
        if (move->next->student.stuNum == stuNum)
        {
            Node *temp = move->next;
            move->next = move->next->next;
            free(temp);
            temp = NULL; // 防止其变为野指针
            saveStudent(head, ".//stu.txt");
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

void sortStudentByStuNum(Node *head)
{
    Node *save = NULL;
    Node *move = NULL;

    for (Node *turn = head->next; turn != NULL; turn = turn->next)
    {
        for (move = head->next; move != save; move = move->next)
        {
            if (move->student.stuNum > move->next->student.stuNum)
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

void sortStudentByBirth(Node *head)
{
    Node *save = NULL;
    Node *move = NULL;

    for (Node *turn = head->next; turn != NULL; turn = turn->next)
    {
        for (move = head->next; move != save; move = move->next)
        {
            if (strcmp(move->student.birth, move->next->student.birth) > 0)
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

void clearInputBuffer()
{
    while (getchar() != '\n')
        ;
}

void freeList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }
}
