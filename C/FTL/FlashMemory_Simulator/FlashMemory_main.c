#include "FlashMemory_head.h"

int main()
{	
	FILE* Flash_Memory = NULL; //플래시메모리
	char Commend[CL]; //명령어를 받을 문자열 배열
	int value = 0; //추출된 값을 받을 변수
	int len = 0; //문자열 길이
	char Write_data[SS];
	memset(Commend, NULL, CL);
	memset(Write_data, NULL, SS);

	printf("도움말 : 입력할 수 있는 명령어는 다음과 같습니다.\n");
	printf("init X MegaByte : X MB 크기의 플래시 메모리 생성\n");
	printf("r 5 : 데이터를 읽어올 섹터 지정\n");
	printf("W 5 : 데이터를 적기위한 섹터 지정\n");
	printf("E 5 : 데이터를 지울 블록 지정\n");
	printf("quit : 프로그램을 종료\n");
	while (true)
	{
		printf("명령어를 입력해주세요>>");
		fgets(Commend,CL,stdin); // 명령어 입력
		strlwr(Commend); // 입력받은 문자 소문자로 바꾸어주기

		if (strstr(Commend,"?") != NULL) // ? 문자를 발견한 경우
		{
			printf("도움말 : 입력할 수 있는 명령어는 다음과 같습니다.\n");
			printf("init X MegaByte : X MB 크기의 플래시 메모리 생성\n");
			printf("R 5 : 5번 섹터의 데이터를 읽어온다.\n");
			printf("W 5 A : 5번 섹터에 A를 적는다.\n");
			printf("E 5 : 5번 블록을 지운다.\n");
		}

		else if (strstr(Commend, "init") != NULL) // 플래시 메모리 생성
		{
			value = ext_num(Commend);//추출한 정수 변수에 입력
			init(Flash_Memory,value);
		}

		else if (strstr(Commend, "r") != NULL) // 해당 섹터의 데이터 읽어오기
		{
			value = ext_num(Commend); //추출한 정수 변수에 입력
			Flash_read(Flash_Memory, value);
		}

		else if (strstr(Commend, "w") != NULL) // 해당 섹터에 데이터 쓰기
		{
			printf("데이터 :");
			fgets(Write_data,SS,stdin); //데이터 입력
			value = ext_num(Commend); //추출한 정수 변수에 입력
			Flash_write(Flash_Memory, value, Write_data);
		}

		else if (strstr(Commend, "e") != NULL) // 해당 블록 삭제하기
		{
			value = ext_num(Commend, value); //추출한 정수 변수에 입력
			Flash_erase(Flash_Memory, value);
		}

		else if (strstr(Commend, "quit") != NULL) // 종료
		{
			return 0;
		}

		else // 잘못된 명령어를 입력했을 경우
		{
			printf("잘못된 명령어입니다.\n");
		}
	}
	return 0;
}