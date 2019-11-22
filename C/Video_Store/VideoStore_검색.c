#include "VideoStore_head.h"

void Search_User(Us_info* Ushead, in_data temp) //사용자 검색 함수
{
	bool user = true; //사용자 존재하는지 확인하는 변수
	Us_info* search = Ushead; 
	for (search; search != NULL; search = search->next) //사용자를 찾을 때 까지 사용자 노드 순환
	{
		if (strcmp(search->name, temp.input_Username) == 0) //저장된 리스트에서 같은 이름을 찾았을 때
		{
			if (strlen(search->borrow_video_1) == 0 && strlen(search->borrow_video_2) == 0 && strlen(search->borrow_video_3) == 0) // 대여하고 있는 비디오가 하나도 없을 때
			{
				printf("%s 사용자가 빌리고 있는 비디오는 없습니다.\n", search->name); 
				user = false;
			}
			else // NULL로 초기화하여, 회원이 빌리고있는 비디오의 문자열이 0이 아니면 빌리고있는 비디오가 있는것.
			{
				if (strlen(search->borrow_video_1) != 0) //사용자가 비디오를 빌리고 있을 때
				{
					if (strlen(search->borrow_video_2) != 0) //사용자가 비디오를 빌리고 있을 때
					{
						if (strlen(search->borrow_video_3) != 0)//사용자가 비디오를 빌리고 있을 때
						{
							printf("%s 사용자가 빌리고 있는 비디오는 %s\t%s\t%s 입니다.\n", search->name, search->borrow_video_1, search->borrow_video_2, search->borrow_video_3);
						}
						else //사용자가 비디오를 2개만 빌리고 있을 때
						{
							printf("%s 사용자가 빌리고 있는 비디오는 %s\t%s 입니다.\n", search->name, search->borrow_video_1, search->borrow_video_2);
						}
					}

					else //사용자가 비디오를 1개만 빌리고 있을 때
					{
						printf("%s 사용자가 빌리고 있는 비디오는 %s 입니다.\n", search->name, search->borrow_video_1);
					}
				}

				else if (strlen(search->borrow_video_2) != 0)
				{
					if (strlen(search->borrow_video_3) != 0) //사용자가 비디오를 2개 빌리고 있을 때
					{
						printf("%s 사용자가 대여하고 있는 비디오는 %s\t%s\t 입니다.\n", search->name, search->borrow_video_2, search->borrow_video_3);
					}
					else//사용자가 비디오를 1개만 빌리고 있을 때
					{
						printf("%s 사용자가 대여하고 있는 비디오는 %s\t입니다.\n", search->name, search->borrow_video_2);
					}
				}
				else //사용자가 비디오를 1개만 빌리고 있을 때
				{
					printf("%s사용자가 대여하고 있는 비디오는 %s입니다.\n", search->name, search->borrow_video_3);
				}
				user = false; //사용자가 존재함
			}

		}
	}
	if (user)
	{
		printf("해당 사용자를 찾지 못했습니다.\n");
	}
}

void Search_Video(Vd_info* Vdhead, in_data temp)
{
	bool Video = true; //비디오 존재 판단 변수
	Vd_info* search = Vdhead->next;
	for (search; search != NULL; search = search->next) //비디오를 찾기위해 비디오 노드 순환
	{
		if (strcmp(search->name, temp.input_Videoname) == 0) //저장된 리스트에서 같은 이름을 찾았을 때
		{
			printf("%s 제품의 재고량은 %d / %d이며, 가격은 %d입니다.\n", search->name, search->number_of_Video, search->total_of_Video, search->price);
			Video = false; //비디오가 존재함
		}
	}
	if (Video)
	{
		printf("해당 제품은 존재하지 않습니다.\n");
	}
}