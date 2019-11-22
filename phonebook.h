//
//  phonebook.h
//  cpptest
//
//  the template Created by Jong-Chul Yoon on 13/04/2019.
//  Copyright ? 2019 Jong-Chul Yoon. All rights reserved.
//  Coder : KiWook Lee
 
#ifndef phonebook_h
#define phonebook_h
#define MAX_NUM 100
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

class Person
{
public:
    char m_name[20];
	char m_phone_number[20];
    char m_address[100];
    char m_email[100];
};
 
 
class Phonebook
{
private:
    Person m_list[MAX_NUM];
    int m_num_of_person;


public:
	Phonebook() //������
	{
		m_num_of_person = 0;
	}

public:
    void insert_person(Person input) //person Ŭ������ �� ����
	{

			int res;
			bool phone_num;
			bool search;
			for (int i = 0; i < MAX_NUM; i++)
			{
				res = strcmp(m_list[i].m_name, input.m_name); //����� �̸��� �Էµ� �̸��� ���Ѵ�.
				if (res == 0) //�̸��������� ��, �̸��� �������
				{
					cout << "���� �̸��� �ۼ���  �� �����ϴ�." << endl;
					break;
				}
			}

				phone_num = strlen(input.m_phone_number) < 11; //�Է¹��� ���ڿ��� ���̰� 11���� ���� ��
				for (int j = 0; j < MAX_NUM; j++) 
				{
					if (phone_num == 1) 
					{
						cout << "11�ڸ� �̸��� ��ȭ��ȣ�� �Է��� �� �����ϴ�." << endl;
						break;
					}
					else
					{
						break;
					}
				}
				search = (strchr(input.m_email, '@') == NULL); //�Է¹��� ������ @�� ã�´�.

				while(1) // @�� ã�� �� ���� �ݺ�
				{
					if (search == 1) //@�� ã�� ������ ��
					{
						cout << "@�� ���� ������ �̸����� ����� �� �����ϴ�." << endl;
						break;
					}
					else if (search == 0) // @�� ã���� ��
					{
						break;
					}
				}
				
				if (res == 0 || phone_num == 1 || search == 1) //����� �̸��� �Էµ� �̸��� ���ų�, �Է¹��� ��ȭ��ȣ�� 11�ڸ� �̸��϶�, @ ���� �Է¹��� �̸����ּ� ������ ��
				{
					input = { 0, };
				}
				else //����� �Է� ������ �迭�� �Է� �� �ε��� ����
				{
					m_list[m_num_of_person] = input;
					m_num_of_person++;
				}

				for (int a = 0; a < m_num_of_person; a++) {
					cout << m_list[a].m_name << " " << m_list[a].m_email << " " << m_list[a].m_phone_number << endl;
				}
				
    }
     
	bool search_person(char *name, Person *output) //��� �˻�
	{
		for (int num = 0; num < MAX_NUM; num++)
		{
			if (strcmp(m_list[num].m_name, name) == 0) //�˻��� �̸��� ���� �̸��� ���� ���
				{
				*output = m_list[num]; //�ش� �ε����� m_lis�迭�� ���
					return true;
				}
			}
		return false;
	}
    void sort_and_print() //���� �� ���   ���� 1. ���ڿ��� ���̸����Ѵ�, ����2 ���ĺ������� �����Ѵ�.
    {
		Person temp = { 0, }; //���� �ű� �� ����� �迭 (ũ�Ⱑ ������ ���� 0���� �ʱ�ȭ �Ǿ�����)
		for (int a = 0; a < MAX_NUM; a++)
		{
			for (int b = 0; b < MAX_NUM; b++)
				if (strcmp(m_list[a].m_name,m_list[b].m_name) < 0) // m_list[a].m_name < m_list[b].m_name �� ��
				{
					temp = m_list[b];
					m_list[b] = m_list[a];
					m_list[a] = temp;
				}
		}
		for (int z = 0; z < m_num_of_person; z++) { //���ĵ� ����� ���
			cout << m_list[z].m_name << " " << m_list[z].m_email << " " << m_list[z].m_phone_number << endl;
		}
    }
     
	bool delete_person(char *name) //����
	{
		Person temp = { 0, };
		int next;
		for (int num = 0; num <MAX_NUM; num++) {
			if (strcmp(m_list[num].m_name, name) == 0) //����Ǿ��ִ� �̸��� �����ϰ��� �˻��� �̸��� ���� ��
			{
				m_list[num] = { 0 };//�˻��� �̸��� �����ϴ� �迭�� �ε����� �ʱ�ȭ��Ų��.
				m_list[num] = m_list[num + 1]; //�� ���� �迭�� ���� �����ش�.

			}			
			}
		m_num_of_person--; //�迭 �ϳ��� ������ �����Ǿ����Ƿ�, �ε����� ������ �ϳ� �ٿ��ش�.
		for (int z = 0; z < m_num_of_person; z++) { //������ ��� ���
				cout << m_list[z].m_name << " " << m_list[z].m_email << " " << m_list[z].m_phone_number << endl;
			return true;
		}

	}
};
 
#endif /* phonebook_h */
 

//zzz 01024889409 asd wook605@gmail.com
//aa 01084649409 asd jungang18@naver.com
//aaa 01024021546 asd cjsworldnr@naver.com