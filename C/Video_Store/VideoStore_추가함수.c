#include "VideoStore_head.h"

void Add_Video(Vd_info* Vdinput, in_data temp)
{
	Vd_info* vp = (Vd_info*)malloc(sizeof(Vd_info)); // 데이터를 저장할 노드에 메모리 할당
	memset(vp, NULL, sizeof(Vd_info));
	
	if (Vdinput->next == NULL) //첫 데이터 삽입일 때
	{
		strcpy(vp->name, temp.input_Videoname); //이름 입력
		vp->price = temp.Money; // 비디오 가격 입력
		vp->number_of_Video = temp.number; // 비디오 개수 입력
		vp->total_of_Video = temp.number;//비디오 총량 입력
		vp->next = Vdinput->next; //노드 연결
		Vdinput->next = vp; //노드 연결
	}

	else // 첫 데이터삽입 이후일 때
	{
		if (check_Videodp(Vdinput, temp)) // 중복체크함수 : false (중복 아님) true (중복)  
		{
			free(vp); // 중복이기 때문에 노드가 필요없어서 새로 만든 노드 삭제
			for (Vdinput; Vdinput != NULL; Vdinput = Vdinput->next)
			{
				if (strcmp(Vdinput->name, temp.input_Videoname) == 0)
				{
					Vdinput->number_of_Video += temp.number; // 중복된 비디오의 갯수를 늘려준다.
					Vdinput->total_of_Video += temp.number; // 총 개수 또한 늘려준다
				}
			}
		}

		else
		{
			strcpy(vp->name, temp.input_Videoname); //이름 입력
			vp->price = temp.Money; // 가격 입력
			vp->number_of_Video = temp.number; //현재 개수 입력
			vp->total_of_Video = temp.number; //총 개수 입력
			vp->next = Vdinput->next; //노드 연결
			Vdinput->next = vp; //노드 연결
			sort_Vdlist(Vdinput); //비디오 이름순으로 정렬
		}
	}
}

void Add_user(Us_info* Usinput, in_data temp)
{
	if (Usinput->next == NULL) //첫 데이터 삽입일 때
	{
		if (check_form(temp)) //핸드폰 번호가 11자리 미만일 때 입력하지 않음
		{
			
		}

		else
		{
			Us_info* up = (Us_info*)malloc(sizeof(Us_info)); // 데이터를 저장할 노드에 메모리 할당
			memset(up, NULL, sizeof(Us_info)); // 노드 NULL로 초기화
			strcpy(up->phone_number, temp.input_phoneNumber); //번호 입력
			strcpy(up->name, temp.input_Username); //이름 입력
			up->next = Usinput->next; //노드 연결
			Usinput->next = up; //노드 연결
		}
	}

	else //첫 데이터 삽입 이후
	{
		if (check_form(temp) || check_Userdp(Usinput, temp)) // 중복체크함수 : false (중복 아님) true (중복)  
		{

		}
		else
		{
			Us_info* up = (Us_info*)malloc(sizeof(Us_info)); // 데이터를 저장할 노드에 메모리 할당
			memset(up, NULL, sizeof(Us_info)); //노드 NULL로 초기화
			strcpy(up->phone_number, temp.input_phoneNumber); //번호 입력
			strcpy(up->name, temp.input_Username); //이름 입력
			up->next = Usinput->next; //노드 연결
			Usinput->next = up;
			sort_Uslist(Usinput);

		}
	}
}

void Cash_Recharge(Us_info* Ushead, in_data temp)
{
	int menu;
	for (Ushead; Ushead != NULL; Ushead = Ushead->next) //사용자 노드 순환
	{
		if (strcmp(Ushead->name, temp.input_Username) == 0) //사용자를 찾았을 때
		{
				printf("얼마를 충전하시겠습니까?\n");
				printf("1. 1000원\t2. 2000원\t3. 3000원\t 4. 5000원\t 5. 10000원\n");
				scanf("%d", &menu); //메뉴 선택
				switch (menu)
				{

				case 1:
				{
					Ushead->Money += 1000; // 잔액 + 선택한 금액
					printf("충전을 완료했습니다.\n");
					printf("현재 금액 : %d\n", Ushead->Money); //잔액 출력
					break;
				}

				case 2:
				{
					Ushead->Money += 2000; // 잔액 + 선택한 금액
					printf("충전을 완료했습니다.\n");
					printf("현재 금액 : %d\n", Ushead->Money);//잔액 출력
					break;
				}

				case 3:
				{
					Ushead->Money += 3000; // 잔액 + 선택한 금액
					printf("충전을 완료했습니다.\n");
					printf("현재 금액 : %d\n", Ushead->Money);//잔액 출력
					break;
				}

				case 4:
				{ 
					Ushead->Money += 5000; // 잔액 + 선택한 금액
					printf("충전을 완료했습니다.\n");
					printf("현재 금액 : %d\n", Ushead->Money);//잔액 출력
					break;
				}

				case 5:
				{
					Ushead->Money += 10000; // 잔액 + 선택한 금액
					printf("충전을 완료했습니다.\n");
					printf("현재 금액 : %d\n", Ushead->Money);//잔액 출력
					break;
				}
				default:
				{
					scanf("%*c", &menu); // 입력버퍼 초기화
					printf("잘못된 메뉴입니다.\n");
					break;
				}
					
				}
		}
	}
}