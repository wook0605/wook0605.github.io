#include "BlockMapping_head.h"

int main()
{
	FILE* Flash_Memory = NULL; //플래시메모리
	char Commend[CL]; //명령어를 받을 문자열 배열
	int LSN = 0; //추출된 값을 받을 변수
	char Write_data[SS]; // 입력할 데이터

	memset(Commend, NULL, CL);
	memset(Write_data, NULL, SS);

	load_table(Flash_Memory); //매핑 테이블을 불러옴

	printf("도움말 : 입력할 수 있는 명령어는 다음과 같습니다.\n");
	printf("? : 도움말  출력\n");
	printf("init X MegaByte : X MB 크기의 플래시 메모리 생성\n");
	printf("read: 5 : 데이터를 읽어올 섹터 지정\n");
	printf("write: 5 : 데이터를 적기위한 섹터 지정\n");
	printf("quit : 프로그램을 종료\n");
	while (true)
	{
		printf("명령어를 입력해주세요>>");
		fgets(Commend, CL, stdin); // 명령어 입력
		strlwr(Commend);

		if (strstr(Commend, "?") != NULL) // ? 문자를 발견한 경우
		{
			printf("도움말 : 입력할 수 있는 명령어는 다음과 같습니다.\n");
			printf("init X MegaByte : X MB 크기의 플래시 메모리 생성\n");
			printf("read 5 : 5번 섹터의 데이터를 읽어온다.\n");
			printf("write 5 A : 5번 섹터에 A를 적는다.\n");
		}

		else if (strstr(Commend, "init") != NULL) // 플래시 메모리 생성
		{
			LSN = ext_num(Commend);//추출한 정수 변수에 입력
			init(Flash_Memory, LSN);
		}

		else if (strstr(Commend, "read") != NULL) // 해당 섹터의 데이터 읽어오기
		{
			LSN = ext_num(Commend); //추출한 정수 변수에 입력
			Flash_read(Flash_Memory, LSN);
		}

		else if (strstr(Commend, "write") != NULL) // 해당 섹터에 데이터 쓰기
		{
			printf("데이터 :");
			fgets(Write_data, SS, stdin); //데이터 입력
			LSN = ext_num(Commend); //추출한 정수 변수에 입력
			Flash_write(Flash_Memory, LSN, Write_data);
		}

		else if (strstr(Commend, "printtable") != NULL) //테이블 출력
		{
			print_table();
		}

		else if (strstr(Commend, "quit") != NULL) // 종료
		{
			quit(Flash_Memory);
			break;
		}

		else // 잘못된 명령어를 입력했을 경우
		{
			printf("잘못된 명령어입니다.\n");
		}
	}
	return 0;
}