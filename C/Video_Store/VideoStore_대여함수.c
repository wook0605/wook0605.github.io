#include "VideoStore_head.h"

void Borrow_Video(Us_info* Ushead, Vd_info* Vdhead, in_data temp)
{
	Us_info* Us_list = Ushead->next;
	bool user = true; // true면 존재하지않는것, false면 존재하는것
	Vd_info* Vd_list = Vdhead->next;
	bool video = true; // true면 존재하지않는것, false면 존재하는것
	int cash = 0;

	for (Us_list; Us_list != NULL; Us_list = Us_list->next) //사용자를 찾기위해 모든 노드 순환
	{
		if (strcmp(Us_list->name, temp.input_Username) == 0) // 사용자 찾았을 때
		{
			user = false; //사용자가 존재함
			for (Vd_list; Vd_list != NULL; Vd_list = Vd_list->next) //사용자를 찾으면 대여할 비디오를 찾는다.
			{
				if (strcmp(Vd_list->name, temp.input_Videoname) == 0) //대여할 비디오를 찾으면, 해당 비디오의 제고를 줄이고, 사용자의 borrow_Video에 이름을 넣는다.
				{
					video = false; //비디오가 존재한다.
					if (Vd_list->number_of_Video == 0) //비디오의 재고가 없을 때
					{
						video = true; //비디오가 존재하지않음.
					}
					else //비디오의 재고가 있을 때
					{
						cash = Us_list->Money - Vd_list->price; //잔액 확인
						if (strcmp(Us_list->borrow_video_1, Vd_list->name) == 0 || strcmp(Us_list->borrow_video_2, Vd_list->name) == 0 || strcmp(Us_list->borrow_video_3, Vd_list->name) == 0)
						{ //똑같은 비디오를 빌릴 때
							printf("해당 비디오를 이미 빌리고 있습니다.\n");
							return; //기능 종료
						}
						else if (strlen(Us_list->borrow_video_1) == 0) // 비디오를 빌리고 있지 않은 상태
						{
							if (Us_list->Money > Vd_list->price || cash >= 0) //가지고 있는 금액이 비디오의 가격보다 크고, 그 차이가 0이상일때
							{
								strcpy(Us_list->borrow_video_1, Vd_list->name); // 비디오 대여
								Vd_list->number_of_Video -= 1; // 비디오의 재고를 줄인다
								printf("비디오를 대여했습니다.\n");
								Us_list->Money -= Vd_list->price; // 현재 금액에서 비용을 뺀다.
								return; //기능 종료
							}
							else //잔액이 모자를 경우
							{
								printf("잔액이 모자랍니다. 캐시를 충전해주세요.\n");
								return;//기능 종료
							}
						}
						else if (strlen(Us_list->borrow_video_2) == 0) // 비디오를 빌리고 있지 않은 상태
						{
							if (Us_list->Money > Vd_list->price || cash >= 0) //가지고 있는 금액이 비디오의 가격보다 크고, 그 차이가 0이상일때
							{
								strcpy(Us_list->borrow_video_2, Vd_list->name); //비디오 대여
								Vd_list->number_of_Video -= 1; //비디오의 재고를 줄인다.
								printf("비디오를 대여했습니다.\n");
								Us_list->Money -= Vd_list->price; // 현재 금액에서 비용을 뺀다.
								return; //기능 종료
							}
							else //잔액이 모자를 경우
							{
								printf("잔액이 모자랍니다. 캐시를 충전해주세요.\n");
								return;//기능 종료
							}

						}
						else if (strlen(Us_list->borrow_video_3) == 0) //비디오를 빌리고 있지 않은 상태
						{
							if (Us_list->Money > Vd_list->price || cash >= 0) //가지고 있는 금액이 비디오의 가격보다 크고, 그 차이가 0이상일때
							{
								strcpy(Us_list->borrow_video_3, Vd_list->name); //비디오 대여
								Vd_list->number_of_Video -= 1; //비디오의 현 재고를 줄인다.
								printf("비디오를 대여했습니다.\n");
								Us_list->Money -= Vd_list->price; // 현재 금액에서 비용을 뺀다.
								return; //기능 종료
							}
							else // 잔액이 모자를 경우
							{
								printf("잔액이 모자랍니다. 캐시를 충전해주세요.\n");
								return;//기능 종료
							}
						}
						else //사용자가 빌릴 수 있는 한도를 넘어섰을때
						{
							printf("해당 사용자는 대여 한도가 가득찼습니다.\n");
						}
					}
				}
			}
		}
	}

	if (user)
	{
		printf("해당 사용자는 존재하지 않습니다.\n");
	}
	if (video)
	{
		printf("해당 제품이 존재하지 않습니다.\n");
	}
}