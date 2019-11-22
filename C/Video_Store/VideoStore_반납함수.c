#include "VideoStore_head.h"

void Return_Video(Us_info* Ushead, Vd_info* Vdhead, in_data temp)
{
	Us_info* Us_list = Ushead;
	bool user = true; // true면 존재하지않는것, false면 존재하는것
	Vd_info* Vd_list = Vdhead;
	bool video = true; // true면 존재하지않는것, false면 존재하는것

	int return_menu;
	printf("1 : 한번에 반납하기.\n");
	printf("2 : 하나만 반납하기.\n");
	
	printf("메뉴 선택>>");
	scanf("%d", &return_menu); //메뉴 선택

	switch (return_menu)
	{
	case 1: //한번에 모두 반납하는 메뉴
	{
		for (Us_list; Us_list != NULL; Us_list = Us_list->next) // 이름을 찾기 위한 반복
		{
			if (strcmp(Us_list->name, temp.input_Username) == 0) // 이름을 찾았을 때
			{
				user = false;
				for (Vd_list; Vd_list != NULL; Vd_list = Vd_list->next) //비디오를 찾기 위한 반복
				{
						if (strcmp(Us_list->borrow_video_1, Vd_list->name) == 0) // 빌려간 비디오를 찾았을 때
						{
							video = false;//비디오 존재
							memset(&Us_list->borrow_video_1, NULL, sizeof(Us_list->borrow_video_1)); // 비디오 반납
							Vd_list->number_of_Video += 1; //비디오의 현 재고 증가
							printf("비디오를 반납했습니다.\n");
						}

						else if (strcmp(Us_list->borrow_video_2, Vd_list->name) == 0) // 빌려간 비디오를 찾았을 때
						{
							video = false;//비디오 존재
							memset(&Us_list->borrow_video_2, NULL, sizeof(Us_list->borrow_video_2)); // 비디오 반납
							Vd_list->number_of_Video += 1;//비디오의 현 재고 증가
							printf("비디오를 반납했습니다.\n");
						}

						else if (strcmp(Us_list->borrow_video_3, Vd_list->name) == 0)// 빌려간 비디오를 찾았을 때
						{
							video = false;//비디오 존재
							memset(&Us_list->borrow_video_3, NULL, sizeof(Us_list->borrow_video_3)); // 비디오 반납
							Vd_list->number_of_Video += 1;//비디오의 현 재고 증가
							printf("비디오를 반납했습니다.\n");
						}
				}
			}
		}
		break;
	}
	case 2:
	{
		printf("반납할 제품명을 입력해주세요.\n");
		scanf("%s", temp.input_Videoname); //반납할 비디오 이름 입력
		for (Us_list; Us_list != NULL; Us_list = Us_list->next) //비디오를 빌리고 있는 사용자를 찾기 위한 사용자 노드 순환
		{
			if (strcmp(Us_list->name, temp.input_Username) == 0) //비디오를 빌리고 있는 사용자를 찾았을 대
			{
				user = false;
				for (Vd_list; Vd_list != NULL; Vd_list = Vd_list->next) //비디오 노드 순환
				{
					if (strcmp(Vd_list->name, temp.input_Videoname) == 0) //사용자가 빌리고 있는 비디오와 입력한 비디오가 같을때
					{
						if (strcmp(Us_list->borrow_video_1, temp.input_Videoname) == 0) // 빌려간 비디오를 찾았을 때
						{
							video = false;//비디오 존재
							memset(&Us_list->borrow_video_1, NULL, sizeof(Us_list->borrow_video_1)); //대여한도 비우기
							Vd_list->number_of_Video += 1; //비디오를 반납하여 비디오 현재 재고 증가
							printf("비디오를 반납했습니다.\n");
							return; //기능 종료
						}
						else if (strcmp(Us_list->borrow_video_2, temp.input_Videoname) == 0) // 빌려간 비디오를 찾았을 때
						{
							video = false;//비디오 존재
							memset(&Us_list->borrow_video_2, NULL, sizeof(Us_list->borrow_video_2));//대여한도 비우기
							Vd_list->number_of_Video += 1;//비디오를 반납하여 비디오 현재 재고 증가
							printf("비디오를 반납했습니다.\n");
							return;//기능 종료
						}
						else if (strcmp(Us_list->borrow_video_3, temp.input_Videoname) == 0) // 빌려간 비디오를 찾았을 때
						{
							video = false;//비디오 존재
							memset(&Us_list->borrow_video_3, NULL, sizeof(Us_list->borrow_video_3));//대여한도 비우기
							Vd_list->number_of_Video += 1;//비디오를 반납하여 비디오 현재 재고 증가
							printf("비디오를 반납했습니다.\n");
							return;// 기능 종료
						}
					}
				}
			}
		}
		break;
	}
	default:
	{
		scanf("%*c", &return_menu); //입력버퍼 초기화
		printf("잘못된 메뉴입니다.\n");
		user = false; //출력 방지
		video = false; //출력 방지
	}
		break;
	}
	if (user)// 에러메시지
	{
		printf("해당 사용자는 존재하지 않습니다.\n");
	}
	if (video)//에러메시지
	{
		printf("해당 제품이 존재하지 않거나, 빌린 비디오가 없는 사용자입니다.\n");
	}
}