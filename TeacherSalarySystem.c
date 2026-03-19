#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FILENAME "D:\\myc\\teacher.dat"
#define FILENAME_TXT "D:\\myc\\teacher.txt"

// 教师结构体
typedef struct teacher
{
    char id[10];    // 教师号
    char name[20];  // 姓名
    char gender;    // 性别 (M/F)
    char dept[30];  // 单位名称
    char addr[50];  // 家庭住址
    char phone[15]; // 联系电话

    // 工资相关字段
    float base;      // 基本工资
    float allowance; // 津贴
    float subsidy;   // 生活补贴
    float gross;     // 应发工资

    // 扣款项
    float phone_bill;     // 电话费
    float water_electric; // 水电费
    float rent;           // 房租
    float tax;            // 所得税
    float san_fee;        // 卫生费
    float housing;        // 公积金
    float deductions;     // 合计扣款
    float net;            // 实发工资

    struct teacher *next; // 下一个结点指针
} Node;

// 函数声明
void menu(Node *head);
void readdate(Node *head);
void modifyTeacher(Node *head);
void deleteTeacher(Node *head);
void browse2();
void browsetxt();
void searchAndPrintTeacher(Node *head);

void save2(Node *head, char fn[], char fs[]);
void savetxt(Node *head, char fn[], char fs[]);
void calculate(Node *t);
void clearInputBuffer();
void create(Node *head);
Node *findTeacher(Node *head, char *id);
void freeList(Node *head);

int main()
{
    // 创建头结点
    Node *head = (Node *)malloc(sizeof(Node));
    head->next = NULL;

    menu(head);
    freeList(head);
    return 0;
}

void menu(Node *head)
{
    int sel;
    do
    {
        system("cls");
        printf("*******************************************\n");
        printf("*          教师工资管理系统              *\n");
        printf("*******************************************\n");
        printf("*          请选择功能列表                *\n");
        printf("*******************************************\n");
        printf("*     1. 录入教师信息                    *\n");
        printf("*     2. 修改教师信息                    *\n");
        printf("*     3. 删除教师信息                    *\n");
        printf("*     4. 浏览二进制文件教师信息          *\n");
        printf("*     5. 浏览文本文件教师信息            *\n");
        printf("*     6. 按教师号查找并打印该教师信息    *\n");
        printf("*     7. 退出系统                        *\n");
        printf("*******************************************\n");

        do
        {
            printf("请选择操作(1-7): ");
            scanf("%d", &sel);
            clearInputBuffer();
        } while (!(sel >= 1 && sel <= 7));

        switch (sel)
        {
        case 1:
            readdate(head); // 录入教师信息
            break;
        case 2:
            modifyTeacher(head); // 修改教师信息
            break;
        case 3:
            deleteTeacher(head); // 删除教师信息
            break;
        case 4:
            browse2(); // 浏览二进制文件教师信息
            system("pause");
            break;
        case 5:
            browsetxt(); // 浏览文本文件教师信息
            system("pause");
            break;
        case 6:
            searchAndPrintTeacher(head); // 按教师号查找并打印该教师信息
            system("pause");
            break;
        case 7:
            printf("系统已退出。\n");
            break;
        }
    } while (sel != 7);
}
// 录入教师信息
void readdate(Node *head)
{
    int sel;
    char yn;

    do
    {
        system("cls");
        printf("1----初次录入\n");
        printf("2----添加记录\n");
        printf("3----返回主菜单\n");
        printf("请选择操作(1-3): ");
        scanf("%d", &sel);
        clearInputBuffer();

        if (sel == 3)
            continue;

        // 无论“初次”还是“添加”，先清空链表（后续重新加载/创建）
        freeList(head);
        head->next = NULL;

        if (sel == 1)
        {
            printf("初次录入将新建文件，确认吗？(y/n): ");
            yn = getchar();
            clearInputBuffer();
            if (yn != 'y' && yn != 'Y')
            {
                break;
            }
        }
        else if (sel == 2)
        {
            // 添加记录：先从文件加载已有数据
            FILE *fp = fopen(FILENAME, "rb");
            if (fp != NULL)
            {
                Node temp;
                Node *curr = head;
                while (fread(&temp, sizeof(Node) - sizeof(Node *), 1, fp) == 1)
                {
                    Node *p = (Node *)malloc(sizeof(Node));
                    memcpy(p, &temp, sizeof(Node) - sizeof(Node *));
                    p->next = NULL;
                    curr->next = p;
                    curr = p;
                }
                fclose(fp);
            }
        }
        // 创建新数据（追加到链表）
        create(head);
        save2(head, FILENAME, "wb");
        savetxt(head, FILENAME_TXT, "w");

        printf("操作成功完成！\n");
        system("pause");
    } while (sel != 3);
}
// 修改教师信息
void modifyTeacher(Node *head)
{
    char id[10];
    printf("请输入要修改的教师号: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';

    Node *t = findTeacher(head, id);
    if (t == NULL)
    {
        printf("未找到该教师！\n");
        system("pause");
        return;
    }

    printf("\n--- 当前教师信息 ---\n");
    printf("教师号: %s\n", t->id);
    printf("姓名: %s\n", t->name);
    printf("性别: %c\n", t->gender);
    printf("单位: %s\n", t->dept);
    printf("地址: %s\n", t->addr);
    printf("电话: %s\n", t->phone);

    printf("\n--- 工资信息 ---\n");
    printf("基本工资: %.2f\n", t->base);
    printf("津贴: %.2f\n", t->allowance);
    printf("生活补贴: %.2f\n", t->subsidy);
    printf("应发工资: %.2f\n", t->gross);

    printf("\n--- 扣款信息 ---\n");
    printf("电话费: %.2f\n", t->phone_bill);
    printf("水电费: %.2f\n", t->water_electric);
    printf("房租: %.2f\n", t->rent);
    printf("所得税: %.2f\n", t->tax);
    printf("卫生费: %.2f\n", t->san_fee);
    printf("公积金: %.2f\n", t->housing);
    printf("合计扣款: %.2f\n", t->deductions);
    printf("实发工资: %.2f\n", t->net);

    printf("\n--- 修改信息 ---\n");
    printf("新姓名(当前: %s): ", t->name);
    fgets(t->name, 20, stdin);
    t->name[strcspn(t->name, "\n")] = '\0';

    printf("新性别(M/F, 当前: %c): ", t->gender);
    scanf(" %c", &t->gender);
    t->gender = toupper(t->gender);
    clearInputBuffer();

    printf("新单位名称(当前: %s): ", t->dept);
    fgets(t->dept, 30, stdin);
    t->dept[strcspn(t->dept, "\n")] = '\0';

    printf("新家庭住址(当前: %s): ", t->addr);
    fgets(t->addr, 50, stdin);
    t->addr[strcspn(t->addr, "\n")] = '\0';

    printf("新联系电话(当前: %s): ", t->phone);
    fgets(t->phone, 15, stdin);
    t->phone[strcspn(t->phone, "\n")] = '\0';

    printf("\n--- 修改工资信息 ---\n");
    printf("新基本工资(当前: %.2f): ", t->base);
    scanf("%f", &t->base);

    printf("新津贴(当前: %.2f): ", t->allowance);
    scanf("%f", &t->allowance);

    printf("新生活补贴(当前: %.2f): ", t->subsidy);
    scanf("%f", &t->subsidy);

    printf("\n--- 修改扣款信息 ---\n");
    printf("新电话费(当前: %.2f): ", t->phone_bill);
    scanf("%f", &t->phone_bill);

    printf("新水电费(当前: %.2f): ", t->water_electric);
    scanf("%f", &t->water_electric);

    printf("新房租(当前: %.2f): ", t->rent);
    scanf("%f", &t->rent);

    printf("新所得税(当前: %.2f): ", t->tax);
    scanf("%f", &t->tax);

    printf("新卫生费(当前: %.2f): ", t->san_fee);
    scanf("%f", &t->san_fee);

    printf("新公积金(当前: %.2f): ", t->housing);
    scanf("%f", &t->housing);

    // 重新计算工资
    calculate(t);

    // 保存到文件
    save2(head, FILENAME, "wb");
    savetxt(head, FILENAME_TXT, "w");

    printf("\n教师信息修改成功！\n");
    system("pause");
}
// 删除教师信息
void deleteTeacher(Node *head)
{
    char id[10];
    printf("请输入要删除的教师号: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';

    Node *prev = head;
    Node *current = head->next;

    while (current != NULL)
    {
        if (strcmp(current->id, id) == 0)
        {
            prev->next = current->next;
            free(current);

            // 保存到文件
            save2(head, FILENAME, "wb");
            savetxt(head, FILENAME_TXT, "w");

            printf("删除教师成功！\n");
            system("pause");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("未找到该教师！\n");
    system("pause");
}
// 浏览二进制文件
void browse2()
{
    FILE *fp;
    Node t;

    if ((fp = fopen(FILENAME, "rb")) == NULL)
    {
        printf("无法打开文件 %s\n", FILENAME);
        return;
    }

    printf("\n--- 教师信息列表(二进制文件) ---\n");
    while (fread(&t, sizeof(Node) - sizeof(Node *), 1, fp) == 1)
    {
        printf("教师号: %s\n", t.id);
        printf("姓名: %s\n", t.name);
        printf("性别: %c\n", t.gender);
        printf("单位: %s\n", t.dept);
        printf("电话: %s\n", t.phone);
        printf("实发工资: %.2f\n", t.net);
        printf("----------------------------\n");
    }

    fclose(fp);
}
// 浏览文本文件
void browsetxt()
{
    FILE *fp;
    char ch;

    if ((fp = fopen(FILENAME_TXT, "r")) == NULL)
    {
        printf("无法打开文件 %s\n", FILENAME_TXT);
        return;
    }

    printf("\n--- 教师信息列表(文本文件) ---\n");
    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }

    fclose(fp);
}
// 查找并打印教师信息
void searchAndPrintTeacher(Node *head)
{
    char id[10];
    printf("请输入要查找的教师号: ");
    fgets(id, 10, stdin);
    id[strcspn(id, "\n")] = '\0';

    Node *t = findTeacher(head, id);
    if (t == NULL)
    {
        printf("未找到该教师！\n");
        return;
    }

    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("教师号: %s  姓名: %s  性别: %c  单位: %s  电话: %s\n",
           t->id, t->name, t->gender, t->dept, t->phone);
    printf("地址: %s\n", t->addr);

    printf("工资信息: 基本工资: %.2f  津贴: %.2f  生活补贴: %.2f  应发工资: %.2f\n",
           t->base, t->allowance, t->subsidy, t->gross);

    printf("扣款信息: 电话费: %.2f  水电费: %.2f  房租: %.2f  所得税: %.2f  ",
           t->phone_bill, t->water_electric, t->rent, t->tax);
    printf("卫生费: %.2f  公积金: %.2f  合计扣款: %.2f  实发工资: %.2f\n",
           t->san_fee, t->housing, t->deductions, t->net);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
}

// 保存到二进制文件
void save2(Node *head, char fn[], char fs[])
{
    FILE *fp;
    Node *p;

    if ((fp = fopen(fn, fs)) == NULL)
    {
        printf("无法打开文件 %s\n", fn);
        exit(1);
    }

    p = head->next;
    while (p != NULL)
    {
        // 不保存next指针
        fwrite(p, sizeof(Node) - sizeof(Node *), 1, fp);
        p = p->next;
    }

    fclose(fp);
}
// 保存到文本文件
void savetxt(Node *head, char fn[], char fs[])
{
    FILE *fp;
    Node *p;

    if ((fp = fopen(fn, fs)) == NULL)
    {
        printf("无法打开文件 %s\n", fn);
        exit(1);
    }

    p = head->next;
    while (p != NULL)
    {
        fprintf(fp, "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        fprintf(fp, "教师号: %s  姓名: %s  性别: %c  单位: %s  电话: %s\n",
                p->id, p->name, p->gender, p->dept, p->phone);
        fprintf(fp, "地址: %s\n", p->addr);

        fprintf(fp, "工资信息: 基本工资: %.2f  津贴: %.2f  生活补贴: %.2f  应发工资: %.2f\n",
                p->base, p->allowance, p->subsidy, p->gross);

        fprintf(fp, "扣款信息: 电话费: %.2f  水电费: %.2f  房租: %.2f  所得税: %.2f  ",
                p->phone_bill, p->water_electric, p->rent, p->tax);
        fprintf(fp, "卫生费: %.2f  公积金: %.2f  合计扣款: %.2f  实发工资: %.2f\n",
                p->san_fee, p->housing, p->deductions, p->net);
        fprintf(fp, "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");

        p = p->next;
    }

    fclose(fp);
}
// 计算教师工资
void calculate(Node *t)
{
    // 计算应发工资
    t->gross = t->base + t->allowance + t->subsidy;

    // 计算合计扣款
    t->deductions = t->phone_bill + t->water_electric + t->rent + t->tax + t->san_fee + t->housing;

    // 计算实发工资
    t->net = t->gross - t->deductions;
}
// 清空输入缓冲区
void clearInputBuffer()
{
    while (getchar() != '\n')
        ;
}
// 创建教师数据
void create(Node *head)
{
    Node *last = head;
    char yn;

    // 找到链表末尾
    while (last->next != NULL)
    {
        last = last->next;
    }

    do
    {
        Node *p = (Node *)malloc(sizeof(Node));
        if (p == NULL)
        {
            printf("内存分配失败！\n");
            exit(1);
        }

        printf("\n--- 教师信息录入 ---\n");
        printf("教师号: ");
        fgets(p->id, 10, stdin);
        p->id[strcspn(p->id, "\n")] = '\0';

        printf("姓名: ");
        fgets(p->name, 20, stdin);
        p->name[strcspn(p->name, "\n")] = '\0';

        printf("性别(M/F): ");
        scanf(" %c", &p->gender);
        p->gender = toupper(p->gender);
        clearInputBuffer();

        printf("单位名称: ");
        fgets(p->dept, 30, stdin);
        p->dept[strcspn(p->dept, "\n")] = '\0';

        printf("家庭住址: ");
        fgets(p->addr, 50, stdin);
        p->addr[strcspn(p->addr, "\n")] = '\0';

        printf("联系电话: ");
        fgets(p->phone, 15, stdin);
        p->phone[strcspn(p->phone, "\n")] = '\0';

        printf("\n--- 工资信息录入 ---\n");
        printf("基本工资: ");
        scanf("%f", &p->base);

        printf("津贴: ");
        scanf("%f", &p->allowance);

        printf("生活补贴: ");
        scanf("%f", &p->subsidy);

        printf("\n--- 扣款信息录入 ---\n");
        printf("电话费: ");
        scanf("%f", &p->phone_bill);

        printf("水电费: ");
        scanf("%f", &p->water_electric);

        printf("房租: ");
        scanf("%f", &p->rent);

        printf("所得税: ");
        scanf("%f", &p->tax);

        printf("卫生费: ");
        scanf("%f", &p->san_fee);

        printf("公积金: ");
        scanf("%f", &p->housing);

        // 计算工资
        calculate(p);

        p->next = NULL;

        // 添加到链表末尾
        last->next = p;
        last = p;

        printf("\n继续添加吗？(y/n): ");
        yn = getchar();
        clearInputBuffer();
    } while (yn == 'Y' || yn == 'y');
}
// 查找教师
Node *findTeacher(Node *head, char *id)
{
    Node *p = head->next;
    while (p != NULL)
    {
        if (strcmp(p->id, id) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}
// 释放链表内存
void freeList(Node *head)
{
    Node *current = head->next;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    head->next = NULL;
}
