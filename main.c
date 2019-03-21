#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNING

// �����ĸ����飬�������վ�㣬�˺ţ����룬��ע��ֵ
char webSite[100][20];
char userName[100][20];
char passWord[100][20];
char reMark[100][20];

//����һ��ȫ�ֱ���
int g_count = 0;

//����ʱ��������
void StartPassWord();

//��������
void AddInfo();

//ɾ������
void DelInfo();

//�޸�����
void EditInfo();

//��ѯ����
void FindInfo();

//��ȡ����
void ReadAllInfo();

//��������
void SaveInfo();

//��ʼ������
void InitInfo();

int main(void)
{
    InitInfo();
    int nChoice = 1;

    StartPassWord();
    while(nChoice)
    {
        printf("********************��ӭʹ�����뱾*********************\n");
        printf("                ����������ѡ����в���                 \n");
        printf("                     1����������                       \n");
        printf("                     2��ɾ������                       \n");
        printf("                     3���޸�����                       \n");
        printf("                     4����ѯ����                       \n");
        printf("                     5��ȫ������                       \n");
        printf("                     6����������                       \n");
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
        printf("��ӭ�´�ʹ�ã�\n");

        system("pause");
        return 0;
    }
}

void AddInfo()
{
    printf("������Ҫ�洢�� վ�㣺");
    scanf_s("%s", webSite[g_count], 20);
    printf("��������Ҫ�洢�� �˺ţ�");
    scanf_s("%s", userName[g_count], 20);
    printf("������Ҫ�洢�� ���룺");
    scanf_s("%s", passWord[g_count], 20);
    printf("������Ҫ�洢�� ��ע��");
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

    fscanf_s(pfile, "��ǰ����%d\n", &g_count);
    printf("��ǰ��%d������\n", g_count);
    for(int i = 0; i < g_count; i++)
    {
        printf("��%d�����ݣ�", i+1);
        printf("վ�㣺%s���˺ţ�%s�����룺%s����ע��%s", webSite[i], userName[i], passWord[i], reMark[i]);
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
    fprintf(pfile, "��ǰ����%d\n", g_count);
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
    printf("������Ҫɾ����վ�㣺\n");
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
        printf("ɾ���ɹ�\n");
    }
    else
    {
        printf("����ʧ�ܣ�\n");
    }
    system("pause");
    system("cls");
}

void InitInfo()
{
    FILE *pfile;
    if(fopen_s(&pfile, "data.i", "r") != 0)
    {
        printf("���Ƚ���data.i�ļ�!");
        system("pause");
        exit(1);
    }
    fcanf_s(pfile, "��ǰ����%d\n", &g_count);
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
    printf("������Ҫ���ҵ�����վ�㣺\n");
    scanf_s("%s", aTemp, 20);
    for(int nIndex = 0; nIndex < g_count; nIndex++)
    {
        if(strcmp(aTemp, webSite[nIndex]) == 0)
        {
            nFind = 1;
        }
        if(nFind == 1)
        {
            printf("վ�㣺%s���˺ţ�%s�����룺%s����ע��%s\n", webSite[nIndex], userName[nIndex], passWord[nIndex], reMark[nIndex]);
            break;
        }
    }
    if(nFind = 0)
    {
        printf("����ʧ�ܣ�\n");
    }
    system("pause");
    system("cls");
}

void EditInfo()
{
    char aTemp[20];
    int nFind = 0;

    printf("������Ҫ�޸ĵ�վ�㣺\n");
    scanf_s("%s", aTemp, 20);
    for(int nIndex = 0; nIndex < g_count; nIndex++)
    {
        if(strcmp(aTemp, webSite[nIndex]) == 0)
        {
            nFind = 1;
        }
        if(nFind = 1)
        {
            printf("������Ҫ�޸ĵ� �˺ţ�");
            scanf_s("%s", userName[nIndex], 20);
            printf("������Ҫ�޸ĵ� ���룺");
            scanf_s("%s", passWord[nIndex], 20);
            printf("������Ҫ�޸ĵ� ��ע��");
            scanf_s("%s", reMark[nIndex], 20);
            printf("վ�㣺%s���˺ţ�%s�����룺%s����ע��%s\n", webSite[nIndex], userName[nIndex], passWord[nIndex], reMark[nIndex]);
            SaveInfo();
            break;
        }
    }
    if(nFind == 0)
    {
        printf("����ʧ�ܣ�\n");
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
        printf("�������������룺\n");
        scanf_s("%s", write, 10);
        if(strcmp(write, spw) == 0)
        {
            nSuccess = 1;
            break;
        }
        else
        {
            printf("��������д��󣡻���%d�λ���\n", 3-i);
            system("pause");
            system("cls");
        }

    }
    if(nSuccess = 1)
    {
        printf("������ȷ�����������ʼʹ�ó���\n");
    }
    else
    {
        printf("����ȫ�����󣡰��������������\n");
        system("pause");
        exit(1);
    }
    system("pause");
    system("cls");
}


