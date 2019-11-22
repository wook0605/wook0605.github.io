#include "VideoStore_head.h"

void sort_Uslist(Us_info* Ushead) //사용자 정렬 (오름차순)
{
	Us_info* temp = (Us_info*)malloc(sizeof(Us_info)); //데이터를 옮길 때 사용할 임시 노드 생성
	Us_info* s_change;
	Us_info* s_change_1;

	for (s_change = Ushead; s_change != NULL; s_change = s_change->next) //사용자 노드 순환(헤드 노드부터)
	{
		for (s_change_1 = Ushead->next; s_change_1 != NULL; s_change_1 = s_change_1->next) //사용자 노드 순환(헤드노드  다음노드부터)
		{
			if (strcmp(s_change->name, s_change_1->name) < 0) //s_change의 이름이 s_change_1의 이름보다 아스키 코드 값이 작을 때
			{
				strcpy(temp->name, s_change->name); //임시노드에 데이터 저장
				strcpy(temp->phone_number, s_change->phone_number); //임시노드에 데이터 저장
				temp->Money = s_change->Money; //임시노드에 데이터 저장
				strcpy(temp->borrow_video_1, s_change->borrow_video_1); //임시노드에 데이터 저장
				strcpy(temp->borrow_video_2, s_change->borrow_video_2); //임시노드에 데이터 저장
				strcpy(temp->borrow_video_3, s_change->borrow_video_3); //임시노드에 데이터 저장

				strcpy(s_change->name, s_change_1->name); // 옮겨질 데이터
				strcpy(s_change->phone_number, s_change_1->phone_number); // 옮겨질 데이터
				s_change->Money = s_change_1->Money; // 옮겨질 데이터
				strcpy(s_change->borrow_video_1, s_change_1->borrow_video_1); // 옮겨질 데이터
				strcpy(s_change->borrow_video_2, s_change_1->borrow_video_2); // 옮겨질 데이터
				strcpy(s_change->borrow_video_3, s_change_1->borrow_video_3); // 옮겨질 데이터

				strcpy(s_change_1->name, temp->name); //임시 노드에 저장된 데이터 옮기기
				strcpy(s_change_1->phone_number, temp->phone_number); //임시 노드에 저장된 데이터 옮기기
				s_change_1->Money = temp->Money; //임시 노드에 저장된 데이터 옮기기
				strcpy(s_change_1->borrow_video_1, temp->borrow_video_1); //임시 노드에 저장된 데이터 옮기기
				strcpy(s_change_1->borrow_video_2, temp->borrow_video_2); //임시 노드에 저장된 데이터 옮기기
				strcpy(s_change_1->borrow_video_3, temp->borrow_video_3); //임시 노드에 저장된 데이터 옮기기
			}
		}
	}
	free(temp); //임시노드 삭제
}


void sort_Vdlist(Vd_info* Vdhead) //비디오 정렬 (오름차순)
{
	Vd_info* temp = (Vd_info*)malloc(sizeof(Vd_info)); //데이터를 옮길 때 사용할 임시 노드 생성
	Vd_info* s_change;
	Vd_info* s_change_1;

	for (s_change = Vdhead; s_change != NULL; s_change = s_change->next)//비디오 노드 순환(헤드노드부터)
	{
		for (s_change_1 = Vdhead->next; s_change_1 != NULL; s_change_1 = s_change_1->next) //비디오 노드 순환(헤드노드 다음 노드부터)
		{
			if (strcmp(s_change->name, s_change_1->name) < 0)//s_change의 이름이 s_change_1의 이름보다 아스키 코드 값이 작을 때
			{
				strcpy(temp->name, s_change->name); //임시노드에 데이터 저장
				temp->price = s_change->price; //임시 노드에 데이터 저장
				temp->number_of_Video = s_change->number_of_Video; //임시 노드에 데이터 저장
				temp->total_of_Video = s_change->total_of_Video; //임시 노드에 데이터 저장

				strcpy(s_change->name, s_change_1->name); //옮겨질 데이터
				s_change->price = s_change_1->price; //옮겨질 데이터
				s_change->number_of_Video = s_change_1->number_of_Video; //옮겨질 데이터
				s_change->total_of_Video = s_change_1->total_of_Video; //옮겨질 데이터
				
				strcpy(s_change_1->name, temp->name); //임시 노드에 저장된 데이터 옮기기
				s_change_1->price = temp->price; //임시 노드에 저장된 데이터 옮기기
				s_change_1->number_of_Video = temp->number_of_Video; //임시 노드에 저장된 데이터 옮기기
				s_change_1->total_of_Video = temp->total_of_Video; //임시 노드에 저장된 데이터 옮기기
			}
		}
	}
	free(temp); //임시노드 삭제
}


void change_info(Us_info* Ushead, Vd_info* Vdhead, in_data temp) //정보 변경
{
	int select, menu, num;
	bool user = true;
	bool video = true;
	Us_info* search_user = Ushead;
	Vd_info* search_video = Vdhead;
	
	printf("변경할 정보를 선택해주십시오.\n");
	printf("1 : 비디오 정보 변경\t2 : 사용자 정보 변경\n");
	scanf("%d", &menu); //메뉴 선택1

	switch (menu)
	{
	case 1:
	{
		printf("어떤 정보를 변경할까요?\n");
		printf("1. 비디오 재고 변경\t2. 비디오 가격 변경\n");
		scanf("%d", &select); //메뉴 선택2
		switch (select)
		{
		case 1 :
		{
			printf("재고를 변경할 비디오의 이름을 입력해주세요\n");
			scanf("%s", temp.input_Username); //비디오 이름 입력
			for (search_video; search_video != NULL; search_video = search_video->next) //입력된 비디오를 찾기 위한 반복
			{
				if (strcmp(temp.input_Videoname, search_video->name) == 0) //입력된 비디오를 찾았을 때
				{
					if (search_video->number_of_Video == search_video->total_of_Video) //누군가 빌리고 있는 상태가 아닐 때
					{
						video = false; //비디오 발견
						printf("수량을 변경해주십시오.\n");
						scanf("%d", &search_video->number_of_Video); //비디오 수량 변경
						search_video->total_of_Video = search_video->number_of_Video; //비디오 수량 변경
						break;
					}

					else //누군가 빌리고 있는 상태일 때
					{
						num = search_video->total_of_Video - search_video->number_of_Video; //총 개수에서 현재 개수를 뺀 값을 저장한다.
						video = false; //비디오 발견
						printf("수량을 변경해주십시오.\n");
						scanf("%d", &search_video->number_of_Video); //비디오 수량 변경
						search_video->total_of_Video = search_video->number_of_Video + num; //갯수가 바뀐 후, 총 개수에 차이를 더한다.
						break;
					}

				}
			}
			break;
		}
		case 2 : 
		{
			printf("가격을 변경할 비디오의 이름을 입력해주세요\n");
			scanf("%s", temp.input_Username); //비디오 이름 입력
			for (search_video; search_video != NULL; search_video = search_video->next) //입력된 비디오를 찾기 위한 반복
			{
				if (strcmp(temp.input_Videoname, search_video->name) == 0) //비디오를 찾았을 때
				{
					video = false; //비디오 발견
					printf("변경할 가격을 입력해주세요\n");
					scanf("%d", &search_video->price); //비디오 가격 변경
					printf("변경된 가격은 %d 입니다.", search_video->price); //비디오 가격 출력
					break;
				}
			}
			break;
		}
		default:
		{
			scanf("%*c", &select); // 입력버퍼 초기화
			video = false;
			printf("잘못된 입력입니다.\n");
			break;
		}
		}

		if (video) //반복이 끝난 이후 한번만 출력하기 위해서
		{
			printf("해당 제품은 존재하지 않습니다.\n");
		}
		break;
	}

	case 2:
	{
		printf("수정할 사용자의 이름을 입력해주세요\n");
		scanf("%s", temp.input_Username); //사용자 이름 입력
		for (search_user; search_user != NULL; search_user = search_user->next) //사용자 이름 찾기 위한 반복
		{
			if (strcmp(temp.input_Username, search_user->name) == 0) // 사용자 이름 찾았을 때
			{
				user = false; //사용자 발견
				printf("메뉴를 선택하십시오.\n");
				printf("1 : 이름변경\t2 : 번호변경\t3 : 이름/번호 변경\n");
				scanf("%d", &select); //메뉴 선택2
				switch (select)
				{
				case 1:
				{
					printf("수정할 이름을 입력해주세요.\n");
					printf("이름 >>");
					scanf("%s", temp.input_Username); //사용자 이름 입력
					if (check_Userdp(search_user, temp)) {} //새로 입력된 이름이 중복일 때 입력하지 않음.
					else //중복이 아닐 때
					{
						strcpy(search_user->name, temp.input_Username); //사용자 이름 변경
						printf("이름 변경이 완료되었습니다.\n");
						sort_Uslist(Ushead); //변경된 이름 정렬
					}
					break;
				}
				case 2:
				{
					printf("수정할 번호를 입력해주세요.\n");
					printf("번호 >>");
					scanf("%s", temp.input_phoneNumber); //변경할 핸드폰 번호 입력
					if (check_form(temp)) {} //입력한 번호가 형태에 맞지 않은 경우 입력 안함
					else//입력한 핸드폰 번호가 형태에 맞는 경우
					{
						strcpy(search_user->phone_number, temp.input_phoneNumber); //핸드폰 번호 변경
						printf("번호 변경이 완료되었습니다.\n");
					}
					break;
				}
				case 3:
				{
					printf("수정할 이름과 번호를 입력해주세요.\n");
					printf("이름 >>");
					scanf("%s", temp.input_Username); //변경할 이름 입력
					printf("번호 >>");
					scanf("%s", temp.input_phoneNumber); //변경할 번호 입력
					if (check_form(temp) || check_Userdp(search_user, temp)) {} //사용자 이름이 중복이거나 번호가 형태에 맞지 않는 경우 입력하지 않음
					else // 사용자 정보가 조건을 통과했을때
					{
						strcpy(search_user->name, temp.input_Username); //사용자 이름 변경
						strcpy(search_user->phone_number, temp.input_phoneNumber); //사용자 번호 변경
						printf("전체 변경이 완료되었습니다.\n");
						sort_Uslist(Ushead); //변경된 이름 정렬
					}
					break;
				}
				default:
				{
					scanf("%*s", &select); //입력버퍼 초기화
					user = false;
					printf("잘못된 입력입니다.\n");
					break;
				}

				}
			}
		}
		break;
	}
	default:
	{
		scanf("%*c", &menu); //입력버퍼 초기화
		printf("잘못된 입력입니다.\n");
		break;
	}
	if (user)

	{
		printf("해당 사용자가 존재하지 않습니다.\n");
	}
	}

}