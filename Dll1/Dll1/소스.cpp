#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "pch.h"
#include "framework.h"
#include "���.h"

using std::vector;
using namespace std;

typedef vector<int> int_vector;
typedef vector<string> string_vector;

int testfunc(int n)
{
    return n + 1;
}

void readCSVfile(string path, int_vector& mainStatus, string_vector& skillStatus, int_vector& skillLevel)
{
    string str_buf;
    fstream fs;

    fs.open(path, ios::in);

    int num = 0;

    int MS = 489, MSnextline = 104, MSdummy = 489;
    int line = 938, skillLocation = 938, nextline = 52, dummy = 938;
    int cnt = 0, flag = 0;



    while (!fs.eof())
    {
        getline(fs, str_buf, ',');

        if (str_buf != "")
        {
            if (num > 480 && num < 715)
            {
                if (num == MS)
                {
                    mainStatus.push_back(stoi(str_buf));
                    if (MS - MSdummy != 0 && (MS - MSdummy) / 8 % 2 == 0)
                    {
                        MSdummy = MSdummy + MSnextline;
                        MS = MSdummy;
                    }
                    else
                        MS = MS + 8;
                }
            }
        }

        if (str_buf != "")
        {

            if (num == skillLocation && num > 900 && num < 1900)
            {
                //cout<<"status name : " << str_buf<< ", location: " << num << endl;
                skillStatus.push_back(str_buf);
                flag = 1;

            }
            if (num == skillLocation + 6 && num > 900 && num < 1900)
            {
                if (flag == 1)
                {
                    //cout<<"status level : " << str_buf<< ", location: " << num << endl;
                    skillLevel.push_back(stoi(str_buf));
                    flag = 0;
                }

                if (cnt < 3)
                {
                    skillLocation = skillLocation + 10;
                    cnt++;
                }
                else
                {
                    skillLocation = line + nextline;
                    line = line + nextline;
                    dummy = skillLocation;
                    cnt = 0;
                }

            }

        }
        num++;
    }
    fs.close();

}

void printStatus(int_vector mainStatus, string_vector skillStatus, int_vector skillLevel)
{
    ofstream ofs;
    ofs.open("text_data.txt", ios::out);

    /*
    "commands": "cc<={SAN} �̼�üũ\ncc<={���} ���\ncc<=1 �ٷ�\ncc<=50 �ǰ�\
    ncc<=1 ũ��\ncc<=1 ��ø\ncc<=1 �ܸ�\ncc<=1 ���� (����)\ncc<=1 ���� (���̵��)
    \ncc<=1 ���ŷ�\n1d3+{DB} ����(�Ǽ�)


    \ncc<=ctrl+shift+V ���⿡ ����\ncc<=1 �Է�\ncc<=2 ����\ncc<=70 ������\ncc<=70 ������\ncc<=65 ���\ncc<=65 �ڷ�����\
    ncc<=5 ��ǻ�� ���\ncc<=1 ���ڱ��\ncc<=10 �������\ncc<=10 ������\ncc<=20 �ڵ��� ����\ncc<=1 ����� ����\ncc<=1 ���Ϸ�()
    \ncc<=10 �׹�\ncc<=10 ����\ncc<=5 �¸�\ncc<=5 ����\ncc<=1 ����\ncc<=1 ����"} }
    */


    int HP = (mainStatus[3] + mainStatus[6]) / 10;
    int MP = mainStatus[5] / 5;
    int SAN = mainStatus[5];
    int LUCK = mainStatus[8];

    ofs << "{ \"kind\": \"character\", \"data\": { \"name\": \"�̸� ���� Ž����\", \"status\":[{\"label\":\"HP\",\"value\":\"" << HP << ",\"max\":" << HP << "},"
        << "{\"label\":\"MP\",\"value\":" << MP << ",\"max\":" << MP << "}," << "{\"label\":\"SAN\",\"value\":" << SAN << ",\"max\":" << SAN << "},"
        << "{\"label\":\"���\",\"value\":" << LUCK << ",\"max\":" << LUCK << "}],"
        << "\"params\":[{\"label\":\"DB\",\"value\":\"1\"}],";



    ofs << "\"commands\": \"cc<={SAN} �̼�üũ\\ncc<={���} ���\\ncc<=" << mainStatus[0] << " �ٷ�\\ncc<=" << mainStatus[3] << " �ǰ�\\"
        << "ncc<=" << mainStatus[6] << "ũ��\\ncc<=" << mainStatus[7] << " ��ø\\ncc<=" << mainStatus[4] << " �ܸ�\\ncc<=" << mainStatus[1] << " ���� (����)\\ncc<=" << mainStatus[2] << "���� (���̵��)" <<
        "\\ncc<=" << mainStatus[5] << " ���ŷ�\\n1d3+{DB} ����(�Ǽ�)";

    for (int i = 0; i < skillStatus.size(); i++)
    {
        ofs << "\\ncc<=" << skillLevel[i] << " " << skillStatus[i];
    }
    ofs << "\"} }";

}

int func(char* chPath)
{
    string path(chPath);

    ofstream ofs;
    ofs.open("text_data.txt", ios::out);


    string_vector mainStatusName = { "�ٷ�", "����", "����", "�ǰ�", "�ܸ�", "���ŷ�", "ũ��", "��ø", "���" }; // ���� �������� Ȯ�� �ؾ���
    int_vector mainStatuslevel;

    string_vector skillStatus;
    int_vector skillLevel;

    readCSVfile(path, mainStatuslevel, skillStatus, skillLevel);

    /* for(int i = 0; i < mainStatuslevel.size(); i++)
    {
        ofs << mainStatusName[i] << " : " << mainStatuslevel[i] <<endl;
    }

    ofs << "-----------------------------------------" <<endl;

    for(int i = 0; i < skillStatus.size(); i++)
    {
        ofs << skillStatus[i] << " : " << skillLevel[i] <<endl;
    }
    ofs << "-----------------------------------------------" <<endl;
 */

 //printMainStatus(mainStatuslevel);

 //cout << endl;

    printStatus(mainStatuslevel, skillStatus, skillLevel);

    //cout << endl;

    cout << "[codes are successfully done]" << endl;

    return 0;
}

/* void printMainStatus(vector<int> mainStatus)
{
    ofstream ofs;
    ofs.open("text_data.txt", ios::out); */

    /*
    { "kind": "character", "data": { "name": "�̸� ���� Ž����", "status":[{"label":"HP","value":5,"max":5},
    {"label":"MP","value":0,"max":0},{"label":"SAN","value":1,"max":1},
    {"label":"���","value":1,"max":1}],
    "params":[{"label":"DB","value":"1"}]


    int HP = (mainStatus[3] + mainStatus[6]) / 10;
    int MP = mainStatus[5] / 5;
    int SAN = mainStatus[5];
    int LUCK = mainStatus[8];

    ofs << "{ \"kind\": \"character\", \"data\": { \"name\": \"�̸� ���� Ž����\", \"status\":[{\"label\":\"HP\",\"value\":\"" << HP << ",\"max\":" << HP << "},"
    << "{\"label\":\"MP\",\"value\":" << MP <<",\"max\":"<< MP << "}," << "{\"label\":\"SAN\",\"value\":" << SAN << ",\"max\":"<< SAN <<"},"
    <<"{\"label\":\"���\",\"value\":"<< LUCK << ",\"max\":" <<LUCK << "}],"
    << "\"params\":[{\"label\":\"DB\",\"value\":\"1\"}],";

} */




//��Ʈ ���ٿ� 67��
// �ٷ� ���� 485
// �ٷ� ���� ��ġ 489
// ���� ���� : 493
// ���� ���� ��ġ : 497 
// 601

// ������ ���� : 938
// ������ ���� ��ġ : 944

// ���� �̸��̶� ������ 6�� ���̳�
// ���� �����̶��� 10�� ���̳�

// ��� ���� : 990

// ���� �����̶� ���� : 52

// �� 17����

// ���� ����: 1822

// ü�� : (�ǰ� + ũ��) / 10
// �̼� : ���ŷ�
// ���� : ���ŷ� / 5


// ��ɽ��� ���� : "cc<={���} ���"        �߰�ȣ�� ��ü���� ���� ��� ��ü�� �ִ� value�� ����
// cc<=50 ������        ��ü�� �ƴ϶� �׳� ���� ��� ���� �־� �ָ��





/*
{ "kind": "character", "data": { "name": "�̸� ���� Ž����", "status":[{"label":"HP","value":5,"max":5},
{"label":"MP","value":0,"max":0},{"label":"SAN","value":1,"max":1},{"label":"���","value":1,"max":1}],
"params":[{"label":"DB","value":"1"}],
"commands": "cc<={SAN} �̼�üũ\ncc<={���} ���\ncc<=1 �ٷ�\ncc<=50 �ǰ�
\ncc<=1 ũ��\ncc<=1 ��ø\ncc<=1 �ܸ�\ncc<=1 ���� (����)\ncc<=1 ���� (���̵��)\ncc<=1 ���ŷ�\n1d3+{DB} ����(�Ǽ�)
\ncc<=ctrl+shift+V ���⿡ ����\ncc<=1 �Է�\ncc<=2 ����\ncc<=70 ������\ncc<=70 ������\ncc<=65 ���\ncc<=65 �ڷ�����\
ncc<=5 ��ǻ�� ���\ncc<=1 ���ڱ��\ncc<=10 �������\ncc<=10 ������\ncc<=20 �ڵ��� ����\ncc<=1 ����� ����\ncc<=1 ���Ϸ�()
\ncc<=10 �׹�\ncc<=10 ����\ncc<=5 �¸�\ncc<=5 ����\ncc<=1 ����\ncc<=1 ����"} }*/