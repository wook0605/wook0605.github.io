#include "phoneBook_head.h"


int main()
{
	PB_list* head = (PB_list*)malloc(sizeof(PB_list)); // 헤드노드 생성
	head->link = NULL; //헤드 노드는 데이터를 저장하지 않음.
	person temp;
	int menu;
	int select;
	while (1)
	{
		printf("=====================================================\n");
		printf("|              메뉴를 선택하십시오.                  |\n");
		printf("| 1. 전화번호 추가                                   |\n");
		printf("| 2. 전화번호 검색                                   |\n");
		printf("| 3. 전화번호 전체보기                               |\n");
		printf("| 4. 전화번호 삭제                                   |\n");
		printf("| 5. 전화번호 수정                                   |\n");
		printf("| 6. 전화번호부 종료                                 |\n");
		printf("=====================================================\n");
		printf("메뉴 선택>>");
		scanf("%d", &menu);

		switch (menu)
		{

		case 1:
		{
			printf("추가할 사용자의 정보를 입력해주십시오.\n");

			printf("이름 :");
			scanf("%s", temp.input_name);
			printf("번호 :");
			scanf("%s", temp.input_number);
			printf("\n");

			Add_user(head, temp);

			break;
		}

		case 2:
		{
			printf(" 1 : 번호로 찾기 / 2 : 이름으로 찾기\n");
			scanf("%d", &select);
			switch (select)
			{
			case 1:
			{
				printf("검색할 사용자의 번호를 입력해주십시오.\n");
				printf("번호 :");
				scanf("%s", temp.input_number);
				Search_user(head, temp);
				break;
			}
			case 2:
			{
				printf("검색할 사용자의 이름을 입력해주십시오.\n");
				printf("이름 :");
				scanf("%s", temp.input_name);
				Search_user(head, temp);
				break;
			}
			default:
			{
				scanf("%*c", &select);
				printf("잘못된 입력입니다.\n");
				break;
			}
			}
		}

		case 3:
		{
			print_Book(head);
			break;
		}

		case 4:
		{
			printf("삭제할 사용자의 이름을 입력해주십시오\n");
			scanf("%s", temp.input_name);
			delete_user(head, temp);
			break;
		}

		case 5:
		{
			printf("변경할 사용자의 이름을 입력해주세요.\n");
			scanf("%s", temp.input_name);
			change_userinfo(head, temp);
			break;
		}

		case 6:
		{
			printf("전화번호부를 종료합니다.\n");
			free_mem(head);
			return 0;
		}

		default:
		{
			scanf("%*c", &menu); //입력버퍼 초기화
			printf("해당 메뉴는 존재하지 않습니다. 다시 입력해주십시오.\n");
			break;
		}
		}
		}
		return 0;
	}