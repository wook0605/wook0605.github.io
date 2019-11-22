
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
     
    cout << "��ȭ��ȣ�� V0.2 ���α׷��� �����մϴ�" <<endl;
    while(1)
    {
        cout << "1.������Է�, 2.����ڰ˻�, 3.���������, 4.����ڻ���, 5.����" <<endl;
        cin >> input;
        switch (input) {
            case 1:
                cout << "������� �̸�, ��ȭ��ȣ, �ּ�, �̸����� ������� �Է��Ͻÿ�." <<endl;
                cin >> P_temp.m_name >> P_temp.m_phone_number >> P_temp.m_address >> P_temp.m_email;
                book.insert_person(P_temp);
                break;
                 
            case 2:
                cout << "�˻��� ������� �̸��� �Է��Ͻÿ�." <<endl;
                cin >> N_temp;
                if (book.search_person(N_temp,&P_temp))
                {
                    cout << "�̸��� " << N_temp << "�� ����ڴ� ��ȭ��ȣ�� " << P_temp.m_phone_number << " �Դϴ�" <<endl;
                }
                else
                {
                    cout << "����ڸ� ã�� ���Ͽ����ϴ�." << endl;
                }
                break;
             
            case 3:
                cout << "������ ����ڸ� ����մϴ�." << endl;
                book.sort_and_print();
                break;
             
            case 4:
                cout << "������ ������� �̸��� �Է��Ͻÿ�." <<endl;
                cin >> N_temp;
                if (book.delete_person(N_temp))
                {
                    cout << N_temp << " ����ڸ� �����Ͽ����ϴ�" <<endl;
                }
                else
                {
                    cout << "������ ����ڸ� ã�� ���Ͽ����ϴ�." << endl;
                }
                break;
             
            case 5:
                cout << "���α׷��� �����մϴ�." <<endl;
                return 0;
                 
            default:
                cout << "�߸��� �Է�. �ٽ� �Է��ϼ���" <<endl;
                break;
        }
    }
     
    return 0;
}
 
