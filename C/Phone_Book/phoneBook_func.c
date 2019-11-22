#include "phoneBook_head.h"

void Add_user(PB_list* input, person temp)
{
	PB_list* p = (PB_list*)malloc(sizeof(PB_list)); // 데이터를 저장할 노드에 메모리 할당


	if (input->link == NULL) //첫 데이터 삽입
	{
		if (check_form(temp))
		{
			free(p);
		}

		else
		{
			strcpy(p->number, temp.input_number); //번호 입력
			strcpy(p->name, temp.input_name); //이름 입력
			p->link = input->link; //노드 연결
			input->link = p;
		}
	}

	else
	{
			if (check_form(temp) || check_dp(input, temp)) // 중복체크함수 : false (중복 아님) true (중복)  
			{
				free(p);
			}

			else
			{
				strcpy(p->number, temp.input_number); //번호 입력
				strcpy(p->name, temp.input_name); //이름 입력
				p->link = input->link; //노드 연결
				input->link = p;
				sort_list(input); //정렬
			}
	}
}

bool check_dp (PB_list* p, person temp)
{
	PB_list* dup = p;
	for (dup; dup!= NULL; dup = dup->link)
		{
			if (strcmp(temp.input_name, dup->name) == 0 || strcmp(temp.input_number, dup->number) == 0)
			{
				printf("중복된 사용자가 존재합니다.\n");
					return true;
			}
		}
	return false;
}

bool check_form(person temp)
{
		if (strlen(temp.input_number) == 11)
		{
			return false;
		}
		else
		{
			printf("11자리 미만의 번호는 입력할 수 없습니다.\n");
			return true;
		}
}

void sort_list(PB_list* head)
{
	PB_list* temp = (PB_list*)malloc(sizeof(PB_list));
	PB_list* s_change;
	PB_list* s_change_1;

		for (s_change = head; s_change!= NULL; s_change = s_change->link)
		{
			for (s_change_1 = head->link; s_change_1 != NULL; s_change_1 = s_change_1->link)
			{
				if (strcmp(s_change->name, s_change_1->name) < 0)
				{
					strcpy(temp->name, s_change->name);
					strcpy(temp->number, s_change->number);
					strcpy(s_change->name, s_change_1->name);
					strcpy(s_change->number, s_change_1->number);
					strcpy(s_change_1->name, temp->name);
					strcpy(s_change_1->number, temp->number);
				}
			}
		}
	free(temp);
}

void Search_user(PB_list* head, person temp)
{
	bool user = false;
	PB_list* search = head;
	for (search; search != NULL; search = search->link)
	{
		if (strcmp(search->name, temp.input_name) == 0) //저장된 리스트에서 같은 이름을 찾았을 때
		{
			printf("%s 사용자의 번호는 %s입니다.\n", temp.input_name, search->number);
			user = true;
		}

		else if (strcmp(search->number, temp.input_number) == 0)
		{
			printf("%s 번호는 %s사용자의 번호 입니다.\n", temp.input_number, search->name);
			user = true;
		}
	}
	if (user != true)
	{
		printf("해당 사용자를 찾지 못했습니다.\n");
	}
}

void print_Book(PB_list* head)
{
	PB_list* p = head->link;
	for (p; p != NULL; p = p->link) //헤드 다음 노드에서 출발하여 빈 노드가 나올 때 까지 반복한다.
	{
		printf("이름 : %s", p->name);
		printf("\n번호 : %s\n", p->number);
	}
}


void delete_user(PB_list* head, person temp)
{
	bool user = false;
	if (head->link == NULL) //첫 데이터에 값이 없을 경우 종료
	{
		return;
	}

	PB_list* ptemp;
	PB_list* remove;

	if (strcmp(head->name, temp.input_name) == 0) //첫 노드가 지울 값일 때
	{
		remove = head;
		head = remove->link;
		printf("삭제했습니다.");
		free(remove);
		user = true;
	}
	for (head; head->link != NULL; head = head->link)
	{
		ptemp = head;
		remove = head->link;
		if (strcmp(remove->name, temp.input_name) == 0) //저장된 리스트에서 같은 이름을 찾았을 때
		{
			if (remove->link != NULL) //중간값 삭제
			{
				ptemp = head;
				ptemp->link = remove->link;
				free(remove);
				printf("사용자를 삭제했습니다.\n");
				user = true;
				break;
			}
			else //마지막값 삭제
			{
				ptemp->link = NULL;
				free(remove);
				printf("사용자를 삭제했습니다.\n");
				user = true;
				break;
			}
		}
	}
	if (user != true)
	{
		printf("해당 사용자가 존재하지 않습니다.\n");
	}
}

void change_userinfo(PB_list* head, person temp)
{
	int select;
	bool user = false;
	PB_list* search = head;
	for (head; head != NULL; head = head->link)
	{
		if (strcmp(temp.input_name, head->name) == 0)
		{
			user = true;
			printf("수정할 정보를 골라주세요.\n");
			printf("1. 이름 변경 / 2. 번호 변경 / 3. 전체 변경\n");
			scanf("%d", &select);
			switch (select)
			{
			case 1:
			{
				printf("수정할 이름을 입력해주세요.\n");
				printf("이름 >>");
				scanf("%s", temp.input_name);
				if (check_dp(head, temp)) {}
				else
				{
				strcpy(head->name, temp.input_name);
				printf("이름 변경이 완료되었습니다.\n");
				sort_list(head);
				}
				break;
			}
			case 2 :
			{
				printf("수정할 번호를 입력해주세요.\n");
				printf("번호 >>");
				scanf("%s", temp.input_number);
				if (check_form(temp)) {}
				else
				{
					strcpy(head->number, temp.input_number);
					printf("번호 변경이 완료되었습니다.\n");
				}
				break;
			}
			case 3 :
			{
				printf("수정할 이름과 번호를 입력해주세요.\n");
				printf("이름 >>");
				scanf("%s", temp.input_name);
				printf("번호 >>");
				scanf("%s", temp.input_number);
				if (check_form(temp) || check_dp(head, temp)) {}
				else
				{
					strcpy(head->name, temp.input_name);
					strcpy(head->number, temp.input_number);
					printf("전체 변경이 완료되었습니다.\n");
					sort_list(head);
				}
				break;
			}
			default:
				scanf("%*c", &select); //입력버퍼 초기화
				printf("잘못된 입력입니다. 다시 선택해주십시오.\n");
				break;
			}
		}
	}
	if (user != true)
	{
		printf("해당 사용자가 존재하지 않습니다.\n");
	}
}

void free_mem(PB_list* head)
{
	PB_list* remove;
	while(head!= NULL)
	{
		remove = head->link;
		head->link = NULL;
		free(remove);
		head = head->link;
	}
	free(head);
}
