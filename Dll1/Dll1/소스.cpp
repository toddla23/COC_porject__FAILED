#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "pch.h"
#include "framework.h"
#include "헤더.h"

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
    "commands": "cc<={SAN} 이성체크\ncc<={행운} 행운\ncc<=1 근력\ncc<=50 건강\
    ncc<=1 크기\ncc<=1 민첩\ncc<=1 외모\ncc<=1 교육 (지식)\ncc<=1 지능 (아이디어)
    \ncc<=1 정신력\n1d3+{DB} 피해(맨손)


    \ncc<=ctrl+shift+V 여기에 복붙\ncc<=1 입력\ncc<=2 예시\ncc<=70 관찰력\ncc<=70 관찰력\ncc<=65 듣기\ncc<=65 자료조사\
    ncc<=5 컴퓨터 사용\ncc<=1 전자기기\ncc<=10 전기수리\ncc<=10 기계수리\ncc<=20 자동차 운전\ncc<=1 중장비 조작\ncc<=1 파일럿()
    \ncc<=10 항법\ncc<=10 추적\ncc<=5 승마\ncc<=5 조련\ncc<=1 폭파\ncc<=1 포격"} }
    */


    int HP = (mainStatus[3] + mainStatus[6]) / 10;
    int MP = mainStatus[5] / 5;
    int SAN = mainStatus[5];
    int LUCK = mainStatus[8];

    ofs << "{ \"kind\": \"character\", \"data\": { \"name\": \"이름 없는 탐사자\", \"status\":[{\"label\":\"HP\",\"value\":\"" << HP << ",\"max\":" << HP << "},"
        << "{\"label\":\"MP\",\"value\":" << MP << ",\"max\":" << MP << "}," << "{\"label\":\"SAN\",\"value\":" << SAN << ",\"max\":" << SAN << "},"
        << "{\"label\":\"행운\",\"value\":" << LUCK << ",\"max\":" << LUCK << "}],"
        << "\"params\":[{\"label\":\"DB\",\"value\":\"1\"}],";



    ofs << "\"commands\": \"cc<={SAN} 이성체크\\ncc<={행운} 행운\\ncc<=" << mainStatus[0] << " 근력\\ncc<=" << mainStatus[3] << " 건강\\"
        << "ncc<=" << mainStatus[6] << "크기\\ncc<=" << mainStatus[7] << " 민첩\\ncc<=" << mainStatus[4] << " 외모\\ncc<=" << mainStatus[1] << " 교육 (지식)\\ncc<=" << mainStatus[2] << "지능 (아이디어)" <<
        "\\ncc<=" << mainStatus[5] << " 정신력\\n1d3+{DB} 피해(맨손)";

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


    string_vector mainStatusName = { "근력", "교육", "지능", "건강", "외모", "정신력", "크기", "민첩", "행운" }; // 여기 꺠지는지 확인 해야함
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
    { "kind": "character", "data": { "name": "이름 없는 탐사자", "status":[{"label":"HP","value":5,"max":5},
    {"label":"MP","value":0,"max":0},{"label":"SAN","value":1,"max":1},
    {"label":"행운","value":1,"max":1}],
    "params":[{"label":"DB","value":"1"}]


    int HP = (mainStatus[3] + mainStatus[6]) / 10;
    int MP = mainStatus[5] / 5;
    int SAN = mainStatus[5];
    int LUCK = mainStatus[8];

    ofs << "{ \"kind\": \"character\", \"data\": { \"name\": \"이름 없는 탐사자\", \"status\":[{\"label\":\"HP\",\"value\":\"" << HP << ",\"max\":" << HP << "},"
    << "{\"label\":\"MP\",\"value\":" << MP <<",\"max\":"<< MP << "}," << "{\"label\":\"SAN\",\"value\":" << SAN << ",\"max\":"<< SAN <<"},"
    <<"{\"label\":\"행운\",\"value\":"<< LUCK << ",\"max\":" <<LUCK << "}],"
    << "\"params\":[{\"label\":\"DB\",\"value\":\"1\"}],";

} */




//시트 한줄에 67개
// 근력 시작 485
// 근력 스탯 위치 489
// 교육 시작 : 493
// 교육 스탯 위치 : 497 
// 601

// 관찰력 시작 : 938
// 관찰력 스탯 위치 : 944

// 스탯 이름이랑 스탯은 6개 차이남
// 다음 스탯이랑은 10개 차이남

// 듣기 시작 : 990

// 다음 라인이랑 차이 : 52

// 총 17라인

// 포격 시작: 1822

// 체력 : (건강 + 크기) / 10
// 이성 : 정신력
// 마력 : 정신력 / 5


// 기능스탯 형식 : "cc<={행운} 행운"        중괄호에 객체명을 넣을 경우 객체에 있는 value를 리턴
// cc<=50 관찰력        객체가 아니라 그냥 값일 경우 값을 넣어 주면됨





/*
{ "kind": "character", "data": { "name": "이름 없는 탐사자", "status":[{"label":"HP","value":5,"max":5},
{"label":"MP","value":0,"max":0},{"label":"SAN","value":1,"max":1},{"label":"행운","value":1,"max":1}],
"params":[{"label":"DB","value":"1"}],
"commands": "cc<={SAN} 이성체크\ncc<={행운} 행운\ncc<=1 근력\ncc<=50 건강
\ncc<=1 크기\ncc<=1 민첩\ncc<=1 외모\ncc<=1 교육 (지식)\ncc<=1 지능 (아이디어)\ncc<=1 정신력\n1d3+{DB} 피해(맨손)
\ncc<=ctrl+shift+V 여기에 복붙\ncc<=1 입력\ncc<=2 예시\ncc<=70 관찰력\ncc<=70 관찰력\ncc<=65 듣기\ncc<=65 자료조사\
ncc<=5 컴퓨터 사용\ncc<=1 전자기기\ncc<=10 전기수리\ncc<=10 기계수리\ncc<=20 자동차 운전\ncc<=1 중장비 조작\ncc<=1 파일럿()
\ncc<=10 항법\ncc<=10 추적\ncc<=5 승마\ncc<=5 조련\ncc<=1 폭파\ncc<=1 포격"} }*/