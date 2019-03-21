#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNING

// 定义四个数组，用来存放站点，账号，密码，备注的值
char webSite[100][20];
char userName[100][20];
char passWord[100][20];
char reMark[100][20];

//定义一个全局变量
int g_count = 0;

//启动时输入密码
void StartPassWord();

//增加数据
void AddInfo();

//删除数据
void DelInfo();

//修改数据
void EditInfo();

//查询数据
void FindInfo();

//读取数据
void ReadAllInfo();

//保存数据
void SaveInfo();

//初始化数据
void InitInfo();

int main(void)
{
    InitInfo();
    int nChoice = 1;

    StartPassWord();
    while(nChoice)
    {
        printf("********************欢迎使用密码本*********************\n");
        printf("                请输入以下选项进行操作                 \n");
        printf("                     1、增加数据                       \n");
        printf("                     2、删除数据                       \n");
        printf("                     3、修改数据                       \n");
        printf("                     4、查询数据                       \n");
        printf("                     5、全部数据                       \n");
        printf("                     6、结束程序                       \n");
        printf("*******************************************************\n");
        scanf_s("%d", &nChoice);
        switch(nChoice)
        {
        case 1:
            AddInfo();
            break;
        case 2:
            DelInfo();
            break;
        case 3:
            EditInfo();
            break;
        case 4:
            FindInfo();
            break;
        case 5:
            ReadAllInfo();
            break;
        case 6:
            nChoice = 0;
            break;
        }
        printf("欢迎下次使用！\n");

        system("pause");
        return 0;
    }
}

void AddInfo()
{
    printf("输入需要存储的 站点：");
    scanf_s("%s", webSite[g_count], 20);
    printf("请输入需要存储的 账号：");
    scanf_s("%s", userName[g_count], 20);
    printf("输入需要存储的 密码：");
    scanf_s("%s", passWord[g_count], 20);
    printf("输入需要存储的 备注：");
    scanf_s("%s", reMark[g_count], 20);
    g_count++;
    SaveInfo();
    InitInfo();
    system("pause");
    system("cls");
}

void ReadAllInfo()
{
    FILE *pfile;
    if(fopen_s(&pfile, "data.i", "r") != 0)
    {
        printf("file open fail.");
        exit(1);
    }

    fscanf_s(pfile, "当前个数%d\n", &g_count);
    printf("当前有%d条数据\n", g_count);
    for(int i = 0; i < g_count; i++)
    {
        printf("第%d条数据：", i+1);
        printf("站点：%s，账号：%s，密码：%s，备注：%s", webSite[i], userName[i], passWord[i], reMark[i]);
        printf("\n");

    }
    fclose(pfile);
    system("pause");
    system("cls");
}

void SaveInfo()
{
    for(int j = 0; j < g_count; j++)
    {
        for(int m = 0; m < 20; m++)
        {
            webSite[j][m] ^= 5;
            userName[j][m] ^= 5;
            passWord[j][m] ^= 5;
            reMark[j][m] ^= 5;
        }
    }
    FILE *pfile;
    if(fopen_s(&pfile, "data.i", "w") != 0)
    {
        printf("File open fail");
        exit(1);
    }
    fseek(pfile, 0, SEEK_SET);
    fprintf(pfile, "当前个数%d\n", g_count);
    for(int i =0; i < g_count; i++)
    {
        fwrite(webSite[i], 20, 1, pfile);
        fwrite(userName[i], 20, 1, pfile);
        fwrite(passWord[i], 20, 1, pfile);
        fwrite(reMark[i], 20, 1, pfile);
        fprintf(pfile, "\n");
    }
    fclose(pfile);
}

void DelInfo()
{
    char aTemp[20];
    int nFind = 0;
    int nIndex = 0;
    printf("请输入要删除的站点：\n");
    scanf_s("%s", aTemp, 20);
    for(; nIndex < g_count; nIndex)
    {
        if(strcmp(aTemp, webSite[nIndex]) == 0)
            {
                nFind = 1;
                break;
            }
    }
    if(nFind == 1)
    {
        for(int i = nIndex; i < g_count; i++)
        {
            strcpy_s(webSite[i], 20, webSite[i+1]);
            strcpy_s(userName[i], 20, userName[i+1]);
            strcpy_s(passWord[i], 20, passWord[i+1]);
            strcpy_s(reMark[i], 20, reMark[i+1]);
        }
        g_count--;
        SaveInfo();
        InitInfo();
        printf("删除成功\n");
    }
    else
    {
        printf("查找失败！\n");
    }
    system("pause");
    system("cls");
}

void InitInfo()
{
    FILE *pfile;
    if(fopen_s(&pfile, "data.i", "r") != 0)
    {
        printf("请先建立data.i文件!");
        system("pause");
        exit(1);
    }
    fcanf_s(pfile, "当前个数%d\n", &g_count);
    for(int i =0; i < g_count; i++)
    {
        fread(webSite[i], 20, 1, pfile);
        fread(userName[i], 20, 1, pfile);
        fread(passWord[i], 20, 1, pfile);
        fread(reMark[i], 20, 1, pfile);
        fscanf_s(pfile, "\n");
    }
    for(int j = 0; j < g_count; j++)
    {
        for(int m = 0; m < 20; m++)
        {
            webSite[j][m] ^= 5;
            userName[j][m] ^= 5;
            passWord[j][m] ^= 5;
            reMark[j][m] ^= 5;
        }
    }
    fclose(pfile);
}

void FindInfo()
{
    char aTemp[2];
    int nFind = 20;
    printf("请输入要查找的数据站点：\n");
    scanf_s("%s", aTemp, 20);
    for(int nIndex = 0; nIndex < g_count; nIndex++)
    {
        if(strcmp(aTemp, webSite[nIndex]) == 0)
        {
            nFind = 1;
        }
        if(nFind == 1)
        {
            printf("站点：%s，账号：%s，密码：%s，备注：%s\n", webSite[nIndex], userName[nIndex], passWord[nIndex], reMark[nIndex]);
            break;
        }
    }
    if(nFind = 0)
    {
        printf("查找失败！\n");
    }
    system("pause");
    system("cls");
}

void EditInfo()
{
    char aTemp[20];
    int nFind = 0;

    printf("请输入要修改的站点：\n");
    scanf_s("%s", aTemp, 20);
    for(int nIndex = 0; nIndex < g_count; nIndex++)
    {
        if(strcmp(aTemp, webSite[nIndex]) == 0)
        {
            nFind = 1;
        }
        if(nFind = 1)
        {
            printf("输入需要修改的 账号：");
            scanf_s("%s", userName[nIndex], 20);
            printf("输入需要修改的 密码：");
            scanf_s("%s", passWord[nIndex], 20);
            printf("输入需要修改的 备注：");
            scanf_s("%s", reMark[nIndex], 20);
            printf("站点：%s，账号：%s，密码：%s，备注：%s\n", webSite[nIndex], userName[nIndex], passWord[nIndex], reMark[nIndex]);
            SaveInfo();
            break;
        }
    }
    if(nFind == 0)
    {
        printf("查找失败！\n");
    }
    system("pause");
    system("cls");
}

void StartPassWord()
{
    char spw[10] = "abcd";
    char write[10] = "";
    int nSuccess = 0;

    for(int i = 1; i <= 3; i++)
    {
        printf("请输入启动密码：\n");
        scanf_s("%s", write, 10);
        if(strcmp(write, spw) == 0)
        {
            nSuccess = 1;
            break;
        }
        else
        {
            printf("你的输入有错误！还有%d次机会\n", 3-i);
            system("pause");
            system("cls");
        }

    }
    if(nSuccess = 1)
    {
        printf("输入正确！按任意键开始使用程序\n");
    }
    else
    {
        printf("输入全部错误！按任意键结束程序\n");
        system("pause");
        exit(1);
    }
    system("pause");
    system("cls");
}


