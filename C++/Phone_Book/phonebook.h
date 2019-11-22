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
	Phonebook() //생성자
	{
		m_num_of_person = 0;
	}

public:
    void insert_person(Person input) //person 클래스에 값 삽입
	{

			int res;
			bool phone_num;
			bool search;
			for (int i = 0; i < MAX_NUM; i++)
			{
				res = strcmp(m_list[i].m_name, input.m_name); //저장된 이름과 입력된 이름을 비교한다.
				if (res == 0) //이름을비교했을 때, 이름이 같은경우
				{
					cout << "같은 이름은 작성할  수 없습니다." << endl;
					break;
				}
			}

				phone_num = strlen(input.m_phone_number) < 11; //입력받은 문자열의 길이가 11보다 작을 때
				for (int j = 0; j < MAX_NUM; j++) 
				{
					if (phone_num == 1) 
					{
						cout << "11자리 미만의 전화번호는 입력할 수 없습니다." << endl;
						break;
					}
					else
					{
						break;
					}
				}
				search = (strchr(input.m_email, '@') == NULL); //입력받은 값에서 @를 찾는다.

				while(1) // @를 찾을 때 까지 반복
				{
					if (search == 1) //@를 찾지 못했을 때
					{
						cout << "@가 없는 형식의 이메일은 사용할 수 없습니다." << endl;
						break;
					}
					else if (search == 0) // @를 찾았을 때
					{
						break;
					}
				}
				
				if (res == 0 || phone_num == 1 || search == 1) //저장된 이름과 입력된 이름이 같거나, 입력받은 전화번호가 11자리 미만일때, @ 없이 입력받은 이메일주소 형식일 때
				{
					input = { 0, };
				}
				else //제대로 입력 했을때 배열에 입력 후 인덱스 증가
				{
					m_list[m_num_of_person] = input;
					m_num_of_person++;
				}

				for (int a = 0; a < m_num_of_person; a++) {
					cout << m_list[a].m_name << " " << m_list[a].m_email << " " << m_list[a].m_phone_number << endl;
				}
				
    }
     
	bool search_person(char *name, Person *output) //사람 검색
	{
		for (int num = 0; num < MAX_NUM; num++)
		{
			if (strcmp(m_list[num].m_name, name) == 0) //검색한 이름과 같은 이름이 나올 경우
				{
				*output = m_list[num]; //해당 인덱스의 m_lis배열을 출력
					return true;
				}
			}
		return false;
	}
    void sort_and_print() //정렬 후 출력   조건 1. 문자열의 길이를비교한다, 조건2 알파벳순으로 정렬한다.
    {
		Person temp = { 0, }; //값을 옮길 때 사용할 배열 (크기가 같지만 값은 0으로 초기화 되어있음)
		for (int a = 0; a < MAX_NUM; a++)
		{
			for (int b = 0; b < MAX_NUM; b++)
				if (strcmp(m_list[a].m_name,m_list[b].m_name) < 0) // m_list[a].m_name < m_list[b].m_name 일 때
				{
					temp = m_list[b];
					m_list[b] = m_list[a];
					m_list[a] = temp;
				}
		}
		for (int z = 0; z < m_num_of_person; z++) { //정렬된 결과를 출력
			cout << m_list[z].m_name << " " << m_list[z].m_email << " " << m_list[z].m_phone_number << endl;
		}
    }
     
	bool delete_person(char *name) //삭제
	{
		Person temp = { 0, };
		int next;
		for (int num = 0; num <MAX_NUM; num++) {
			if (strcmp(m_list[num].m_name, name) == 0) //저장되어있는 이름에 삭제하고자 검색한 이름이 있을 때
			{
				m_list[num] = { 0 };//검색된 이름이 존재하는 배열의 인덱스를 초기화시킨다.
				m_list[num] = m_list[num + 1]; //그 다음 배열의 값을 땡겨준다.

			}			
			}
		m_num_of_person--; //배열 하나의 내용이 삭제되었으므로, 인덱스의 개수를 하나 줄여준다.
		for (int z = 0; z < m_num_of_person; z++) { //삭제한 결과 출력
				cout << m_list[z].m_name << " " << m_list[z].m_email << " " << m_list[z].m_phone_number << endl;
			return true;
		}

	}
};
 
#endif /* phonebook_h */
 

//zzz 01024889409 asd wook605@gmail.com
//aa 01084649409 asd jungang18@naver.com
//aaa 01024021546 asd cjsworldnr@naver.com
