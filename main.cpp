#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char** argv) {
    
    
    string str_buf;         
    fstream fs; 
    
    fs.open("data_ANSI.csv",ios::in);
    
    int num = 0;

    int line = 938, X = 938, nextline = 52, dummy = 938;
    int cnt = 0, flag = 0;

    vector<string> status;
    vector<string> level;


    while(!fs.eof())
    {
        getline(fs,str_buf,',');

        if(str_buf != "")
        {   
                
            if(num == X && num > 900 && num < 1900)
            {   
                //cout<<"status name : " << str_buf<< ", location: " << num << endl;
                status.push_back(str_buf);
                flag = 1;
                
            }
            if(num == X + 6 && num > 900 && num < 1900)
            {   
                if(flag == 1)
                {    
                    //cout<<"status level : " << str_buf<< ", location: " << num << endl;
                    level.push_back(str_buf);
                    flag = 0;
                }

                if(cnt < 3)
                {                    
                    X = X + 10;
                    cnt++;
                }
                else
                {
                    X = line + nextline;
                    line = line + nextline;
                    dummy = X;
                    cnt = 0;
                }

            }

        }
            num++;
    }
    fs.close();
    cout << "end";

    for(int i = 0; i < status.size(); i++)
    {
        cout << "staus name: " << status[i] << ", status level: " << level[i] <<endl;
    }
    
    return 0;
}

//시트 한줄에 67개
// 근력 시작 485
// 관찰력 시작 : 938
// 관찰력 스탯 위치 : 944

// 스탯 이름이랑 스탯은 6개 차이남
// 다음 스탯이랑은 10개 차이남

// 듣기 시작 : 990

// 다음 라인이랑 차이 : 52

// 총 17라인

// 포격 시작: 1822
