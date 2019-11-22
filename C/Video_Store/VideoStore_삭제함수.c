#include "VideoStore_head.h"

void delete_user(Us_info* Ushead, Vd_info* Vdhead, in_data temp)
{
	bool user = true;
	if (Ushead->next == NULL) //첫 데이터에 값이 없을 경우 종료
	{
		return;
	}

	Us_info* ptemp;
	Us_info* remove;
	if (strcmp(Ushead->name, temp.input_Username) == 0) //첫 노드가 지울 값일 때
	{
		if (strlen(Ushead->borrow_video_1) == 0 && strlen(Ushead->borrow_video_2) == 0 && strlen(Ushead->borrow_video_3) == 0) //비디오를 가지고 있지 않을때
		{
			remove = Ushead;
			Ushead = remove->next;
			free(remove); //사용자 노드 삭제
			printf("삭제했습니다.");
			user = false; //사용자를 발견했음.
		}
		else //비디오를 하나라도 가지고 있을 때
		{
			Return_Video(Ushead, Vdhead, temp); //반납 함수 호출
			remove = Ushead;
			Ushead = remove->next;
			free(remove); //사용자 삭제
			printf("삭제했습니다.");
			user = false; //사용자를 발견했음
		}
	}
	for (Ushead; Ushead->next != NULL; Ushead = Ushead->next)// 삭제할 사용자를 찾기 위한 사용자 노드 순환
	{
		ptemp = Ushead;
		remove = Ushead->next;
		if (strcmp(remove->name, temp.input_Username) == 0) //저장된 리스트에서 같은 이름을 찾았을 때
		{
			if (remove->next != NULL) //중간값 삭제
			{
				if (strlen(Ushead->borrow_video_1) == 0 && strlen(Ushead->borrow_video_2) == 0 && strlen(Ushead->borrow_video_3) == 0) //비디오를 가지고 있지 않을때
				{
					ptemp = Ushead;
					ptemp->next = remove->next;
					free(remove); //사용자 삭제
					printf("사용자를 삭제했습니다.\n");
					user = false; //사용자를 발견했음
					break;
				}
				else //비디오를 하나라도 가지고 있을 때
				{
					Return_Video(Ushead, Vdhead, temp); // 반납 함수 호출
					ptemp = Ushead;
					ptemp->next = remove->next;
					free(remove); //사용자 삭제
					printf("사용자를 삭제했습니다.\n");
					user = false;//사용자를 발견했음
					break;
				}
			}
			else //마지막값 삭제
			{
				if (strlen(Ushead->borrow_video_1) == 0 && strlen(Ushead->borrow_video_2) == 0 && strlen(Ushead->borrow_video_3) == 0) //비디오를 가지고 있지 않을때
				{
					ptemp->next = NULL;
					free(remove);//사용자 삭제
					printf("사용자를 삭제했습니다.\n");
					user = false;//사용자를 발견했음
					break;
				}
				else//비디오를 하나라도 가지고 있을 때
				{
					Return_Video(Ushead, Vdhead, temp); //반납함수 호출
					ptemp->next = NULL;
					free(remove);//사용자 삭제
					printf("사용자를 삭제했습니다.\n");
					user = false;//사용자를 발견했음
					break;
				}
			}
		}
	}
	if (user) //에러메시지
	{
		printf("해당 사용자가 존재하지 않습니다.\n");
	}
}

void delete_Video(Vd_info* Vdhead, Us_info* Ushead, in_data temp)
{
	bool Video = true;
	if (Vdhead->next == NULL) //첫 데이터에 값이 없을 경우 종료
	{
		return;
	}

	Vd_info* ptemp;
	Vd_info* remove;

	if (strcmp(Vdhead->name, temp.input_Videoname) == 0) //첫 노드가 지울 값일 때
	{
		if (Vdhead->number_of_Video == Vdhead->total_of_Video) // 해당 비디오를 아무도 빌리고 있지 않을 때
		{
			remove = Vdhead;
			Vdhead = remove->next;
			free(remove);//비디오 노드 삭제
			printf("삭제했습니다.");
			Video = false; //비디오 발견
		}
		else //누군가 해당 비디오를 빌리고 있을 때
		{
			for (Ushead; Ushead != NULL; Ushead = Ushead->next) //사용자 노드 순환
			{
				if (strcmp(Ushead->borrow_video_1, Vdhead->name) == 0) // 비디오를 빌리고 있는 사용자를 찾았을 때
				{
					memset(Ushead->borrow_video_1, NULL, sizeof(Ushead->borrow_video_1)); //대여한도 초기화
					remove = Vdhead;
					Vdhead = remove->next;
					free(remove);//비디오 노드 삭제
					printf("삭제했습니다.");
					Video = false;//비디오 발견
				}
				else if (strcmp(Ushead->borrow_video_2, Vdhead->name) == 0)// 비디오를 빌리고 있는 사용자를 찾았을 때
				{
					memset(Ushead->borrow_video_2, NULL, sizeof(Ushead->borrow_video_2)); //대여한도 초기화
					remove = Vdhead;
					Vdhead = remove->next;
					free(remove);//비디오 노드 삭제
					printf("삭제했습니다.");
					Video = false;//비디오 발견
				}
				else if (strcmp(Ushead->borrow_video_3, Vdhead->name) == 0)// 비디오를 빌리고 있는 사용자를 찾았을 때
				{
					memset(Ushead->borrow_video_3, NULL, sizeof(Ushead->borrow_video_3)); //대여한도 초기화
					remove = Vdhead;
					Vdhead = remove->next;
					free(remove);//비디오 노드 삭제
					printf("삭제했습니다.");
					Video = false;//비디오 발견
				}
			}
		}
	}
	for (Vdhead; Vdhead != NULL; Vdhead = Vdhead->next) //삭제할 비디오를 찾기 위한 비디오 노드 순환
	{
		ptemp = Vdhead;
		remove = Vdhead->next;
		if (strcmp(remove->name, temp.input_Videoname) == 0) //저장된 리스트에서 같은 이름을 찾았을 때
		{
			if (remove->next != NULL) //중간값 삭제
			{
				if (remove->number_of_Video == remove->total_of_Video) // 해당 비디오를 아무도 빌리고 있지 않을 때
				{
					ptemp = Vdhead;
					ptemp->next = remove->next; // 삭제할 노드 이후의 노드들과 삭제할 노드 이전의 노드를 연결해 삭제되지않도록함.
					free(remove); //삭제되는 부분
					printf("비디오를 삭제했습니다.\n");
					Video = false; //비디오 발견
					break;
				}
				else// 해당 비디오 하나라도 빌리고 있는 경우
				{
					for (Ushead; Ushead != NULL; Ushead = Ushead->next) //비디오를 빌리고있는 사용자를 찾기 위한 순환
					{
						if (strcmp(Ushead->borrow_video_1, remove->name) == 0) //해당 비디오를 빌리고 있는 사용자를 찾았을 때
						{
							memset(Ushead->borrow_video_1, NULL, sizeof(Ushead->borrow_video_1)); //대여비디오 반납
							ptemp = Vdhead;
							ptemp->next = remove->next; // 삭제할 노드 이후의 노드들과 삭제할 노드 이전의 노드를 연결해 삭제되지않도록함.
							free(remove); //삭제되는 부분
							printf("비디오를 삭제했습니다.\n");
							Video = false;//비디오 발견
							break;
						}
						else if (strcmp(Ushead->borrow_video_2, remove->name) == 0) //해당 비디오를 빌리고 있는 사용자를 찾았을 때
						{
							memset(Ushead->borrow_video_2, NULL, sizeof(Ushead->borrow_video_2));//대여비디오 반납
							ptemp = Vdhead;
							ptemp->next = remove->next; // 삭제할 노드 이후의 노드들과 삭제할 노드 이전의 노드를 연결해 삭제되지않도록함.
							free(remove); //삭제되는 부분
							printf("비디오를 삭제했습니다.\n");
							Video = false;//비디오 발견
							break;
						}
						else if (strcmp(Ushead->borrow_video_3, remove->name) == 0) //해당 비디오를 빌리고 있는 사용자를 찾았을 때
						{
							memset(Ushead->borrow_video_3, NULL, sizeof(Ushead->borrow_video_3));//대여비디오 반납
							ptemp = Vdhead;
							ptemp->next = remove->next; // 삭제할 노드 이후의 노드들과 삭제할 노드 이전의 노드를 연결해 삭제되지않도록함.
							free(remove); //삭제되는 부분
							printf("비디오를 삭제했습니다.\n");
							Video = false;//비디오 발견
							break;
						}
					}
				}

			}
			else //마지막값 삭제
			{
				if (remove->number_of_Video == remove->total_of_Video) // 해당 비디오를 아무도 빌리고 있지 않을 때
				{
					ptemp->next = NULL;
					free(remove); // 비디오 삭제
					printf("비디오를 삭제했습니다.\n");
					Video = false;//비디오 발견
					break;
				}

				else
				{
					for (Ushead; Ushead != NULL; Ushead = Ushead->next)
					{
						if (strcmp(Ushead->borrow_video_1, remove->name) == 0) //해당 비디오를 빌리고 있는 사용자를 찾았을 때
						{
							memset(Ushead->borrow_video_1, NULL, sizeof(Ushead->borrow_video_1));//대여비디오 반납
							ptemp->next = NULL;
							free(remove); // 비디오 삭제
							printf("비디오를 삭제했습니다.\n");
							Video = false;//비디오 발견
							break;
						}
						else if (strcmp(Ushead->borrow_video_2, remove->name) == 0) //해당 비디오를 빌리고 있는 사용자를 찾았을 때
						{
							memset(Ushead->borrow_video_2, NULL, sizeof(Ushead->borrow_video_2));//대여비디오 반납
							ptemp->next = NULL;
							free(remove); // 비디오 삭제
							printf("비디오를 삭제했습니다.\n");
							Video = false;//비디오 발견
							break;
						}
						else if (strcmp(Ushead->borrow_video_3, remove->name) == 0) //해당 비디오를 빌리고 있는 사용자를 찾았을 때
						{
							memset(Ushead->borrow_video_3, NULL, sizeof(Ushead->borrow_video_3));//대여비디오 반납
							ptemp->next = NULL;
							free(remove); // 비디오 삭제
							printf("비디오를 삭제했습니다.\n");
							Video = false;//비디오 발견
							break;
						}
					}
				}
			}
		}
	}
	if (Video)
	{
		printf("해당 비디오가 존재하지 않습니다.\n");
	}
}