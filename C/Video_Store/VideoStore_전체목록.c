#include "VideoStore_head.h"

void print_AllUser(Us_info* Ushead)
{
	Us_info* up = Ushead->next;
	for (up; up != NULL; up = up->next) //사용자 노드 순환
	{
		printf("사용자 이름 : %s\n", up->name);
		printf("사용자 핸드폰 번호 : %s\n", up->phone_number);
		if (strlen(up->borrow_video_1) == 0 && strlen(up->borrow_video_2) == 0 && strlen(up->borrow_video_3) == 0) //대여한도가 비어있는 상태일 때
		{
			printf("대여하고 있는 비디오는 없습니다.\n");
		}
		else //대여 한도가 하나라도 비어있을 경우
		{
			if (strlen(up->borrow_video_1) != 0) // 대여하고 있는 비디오가 있을때
			{
				if (strlen(up->borrow_video_2) != 0)// 대여하고 있는 비디오가 있을때 
				{
					if (strlen(up->borrow_video_3) != 0)// 대여하고 있는 비디오가 있을때
					{
						printf("대여하고 있는 비디오는 %s,%s,%s 입니다.\n", up->borrow_video_1, up->borrow_video_2, up->borrow_video_3);
					}
					else
					{
						printf("대여하고 있는 비디오는 %s,%s 입니다.\n", up->borrow_video_1, up->borrow_video_2);
					}
				}

				else
				{
					printf("대여하고 있는 비디오는 %s 입니다.\n", up->borrow_video_1);
				}
			}

			else if (strlen(up->borrow_video_2) != 0) // 대여하고 있는 비디오가 있을때
			{
				if (strlen(up->borrow_video_3) != 0) // 대여하고 있는 비디오가 있을때
				{
					printf("사용자가 대여하고 있는 비디오는 %s,%s 입니다.\n", up->borrow_video_2, up->borrow_video_3);
				}
				else
				{
					printf("사용자가 대여하고 있는 비디오는 %s 입니다.\n", up->borrow_video_2);
				}
			}
			else 
			{
				printf("사용자가 대여하고 있는 비디오는 %s 입니다.\n", up->borrow_video_3);
			}
		}
		printf("현재 충전된 캐시 : %d\n", up->Money);
	}
}

void print_AllVideo(Vd_info* Vdhead)
{
	Vd_info* vp = Vdhead->next;
	for (vp; vp != NULL; vp = vp->next) //비디오노드 순환
	{
		printf("비디오 이름 : %s\n", vp->name);
		printf("비디오 가격 : %d\n", vp->price);
		printf("비디오 개수(현재개수 / 총 개수) : %d/%d\n", vp->number_of_Video,vp->total_of_Video);
	}
}