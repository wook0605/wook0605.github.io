
//
//  main.cpp
//  cpptest
//
//  the template Created by Jong-Chul Yoon on 13/04/2019.
//  Copyright ? 2019 Jong-Chul Yoon. All rights reserved.
//  Coder : KiWook Lee
 
#include "phonebook.h"
using namespace std;
int main() {
     
    int input;
    char N_temp[20];
    Person P_temp;
    Phonebook book;
     
    cout << "전화번호부 V0.2 프로그램을 시작합니다" <<endl;
    while(1)
    {
        cout << "1.사용자입력, 2.사용자검색, 3.정렬후출력, 4.사용자삭제, 5.종료" <<endl;
        cin >> input;
        switch (input) {
            case 1:
                cout << "사용자의 이름, 전화번호, 주소, 이메일을 순서대로 입력하시오." <<endl;
                cin >> P_temp.m_name >> P_temp.m_phone_number >> P_temp.m_address >> P_temp.m_email;
                book.insert_person(P_temp);
                break;
                 
            case 2:
                cout << "검색할 사용자의 이름을 입력하시오." <<endl;
                cin >> N_temp;
                if (book.search_person(N_temp,&P_temp))
                {
                    cout << "이름이 " << N_temp << "인 사용자는 전화번호가 " << P_temp.m_phone_number << " 입니다" <<endl;
                }
                else
                {
                    cout << "사용자를 찾지 못하였습니다." << endl;
                }
                break;
             
            case 3:
                cout << "정렬한 상용자를 출력합니다." << endl;
                book.sort_and_print();
                break;
             
            case 4:
                cout << "삭제할 사용자의 이름을 입력하시오." <<endl;
                cin >> N_temp;
                if (book.delete_person(N_temp))
                {
                    cout << N_temp << " 사용자를 삭제하였습니다" <<endl;
                }
                else
                {
                    cout << "삭제할 사용자를 찾지 못하였습니다." << endl;
                }
                break;
             
            case 5:
                cout << "프로그램을 종료합니다." <<endl;
                return 0;
                 
            default:
                cout << "잘못된 입력. 다시 입력하세요" <<endl;
                break;
        }
    }
     
    return 0;
}
 
