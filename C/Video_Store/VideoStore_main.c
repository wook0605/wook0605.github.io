#include "VideoStore_head.h"


int main()
{
	Us_info* Us_head = (Us_info*)malloc(sizeof(Us_info)); //유저 데이터를 관리할 연결리스트 생성
	Us_head->next = NULL;
	Vd_info* Vd_head = (Vd_info*)malloc(sizeof(Vd_info)); //비디오 데이터를 관리할 연결리스트 생성
	Vd_head->next = NULL;
	in_data temp; // 연결리스트에 데이터의 입력할 구조체
	memset(&temp, NULL, sizeof(in_data)); // 데이터를 입력할 구조체를 초기화
	FILE* Us_DB = NULL; // 파일에 유저 데이터를 저장하기 위함
	FILE* Vd_DB = NULL; // 파일에 비디오 데이터를 저장하기 위함
	int menu;
	Load_Usdata(Us_DB, Us_head); // 프로그램을 시작하면 사용자 데이터를 자동으로 불러온다.
	Load_Vddata(Vd_DB, Vd_head); // 프로그램을 시작하면 비디오 데이터를 자동으로 불러온다.
	while (1)
	{
		printf("=====================================================\n");
		printf("|              메뉴를 선택하십시오.                  |\n");
		printf("| 1. 사용자 추가                                     |\n");
		printf("| 2. 비디오 입고                                     |\n");
		printf("| 3. 캐시 충전                                       |\n");
		printf("| 4. 사용자 전체목록                                 |\n");
		printf("| 5. 비디오 전체목록                                 |\n");
		printf("| 6. 정보 수정                                       |\n");
		printf("| 7. 비디오 검색                                     |\n");
		printf("| 8. 사용자 검색                                     |\n");
		printf("| 9. 사용자 삭제                                     |\n");
		printf("| 10. 비디오 삭제                                    |\n");
		printf("| 11. 비디오 대여                                    |\n");
		printf("| 12. 비디오 반납                                    |\n");
		printf("| 13. 비디오 가게 종료                               |\n");
		printf("=====================================================\n");
		printf("메뉴 선택>>");
		scanf("%d", &menu);

		switch (menu)
		{
		case 1:
		{
			memset(&temp,NULL, sizeof(in_data)); // 데이터 입력하는 구조체 초기화
			printf("추가할 사용자의 정보를 입력해주십시오.\n");
			printf("사용자 이름 :");
			scanf("%s", temp.input_Username); //사용자 이름 입력
			printf("핸드폰 번호 :");
			scanf("%s", temp.input_phoneNumber);// 사용자 핸드폰번호 입력
			printf("\n"); //개행
			Add_user(Us_head, temp); //사용자 추가
			break;
		}

		case 2:
		{
			memset(&temp, NULL, sizeof(in_data)); // 데이터 입력하는 구조체 초기화
			printf("입고된 비디오의 정보를 입력해주십시오.\n");
			printf("제품 명 :");
			scanf("%s", temp.input_Videoname); //비디오 이름 입력
			printf("가격 : ");
			scanf("%d", &temp.Money); // 비디오 가격 입력
			printf("개수 : ");
			scanf("%d", &temp.number); // 비디오 개수 입력
			Add_Video(Vd_head, temp); //비디오 입고
			break;
		}

		case 3:
		{
			printf("금액을 충전할 사용자를 입력해주세요.\n");
			scanf("%s", temp.input_Username); //충전할 사용자 이름 입력
			Cash_Recharge(Us_head, temp); //캐시 충전
			break;
		}

		case 4:
		{
			print_AllUser(Us_head); //사용자 전체목록 출력
			break;
		}

		case 5:
		{
			print_AllVideo(Vd_head); //비디오 전체목록 출력
			break;
		}
		case 6:
		{
			change_info(Us_head, Vd_head, temp); //사용자 정보 변경 or 비디오 제고 변경
			break;
		}
		case 7:
		{
			printf("검색할 제품 이름을 입력해주세요.\n");
			scanf("%s", temp.input_Videoname); //검색할 비디오 이름 입력
			Search_Video(Vd_head, temp); //비디오 검색
			break;
		}

		case 8:
		{
			printf("검색할 사용자의 이름을 입력해주세요.\n");
			scanf("%s", temp.input_Username); //검색할 사용자 이름 입력
			Search_User(Us_head, temp); //사용자 검색
			break;
		}

		case 9:
		{
			printf("※주의! 사용자를 삭제하면 남아있는 캐시는 반환되지 않습니다.※\n");
			printf("삭제할 사용자의 이름을 입력하세요\n");
			scanf("%s", temp.input_Username); // 삭제할 사용자 이름 입력
			delete_user(Us_head,Vd_head, temp); //사용자 삭제
			break;
		}

		case 10:
		{
			printf("삭제할 비디오의 이름을 입력하세요\n");
			scanf("%s", temp.input_Videoname); //삭제할 비디오 이름 입력
			delete_Video(Vd_head, Us_head, temp);//비디오 삭제
			break;
		}

		case 11:
		{
			printf("사용자 이름 :");
			scanf("%s", temp.input_Username);
			printf("대여할 제품 이름 :");
			scanf("%s", temp.input_Videoname);
			Borrow_Video(Us_head, Vd_head, temp); //비디오 대여
			break;

		}
		case 12:
		{
			printf("사용자 이름 :");
			scanf("%s", temp.input_Username);
			Return_Video(Us_head, Vd_head, temp); //비디오 반납
			break;
		}
		case 13:
		{
			printf("비디오 가게를 종료합니다.\n");
			Save_UsData(Us_DB, Us_head->next);//파일에 사용자 데이터 저장
			Save_VdData(Vd_DB, Vd_head->next);//파일에 비디오 데이터 저장
			free_Usmem(Us_head); //사용자 노드 해제
			free_Vdmem(Vd_head); //비디오 노드 해제
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