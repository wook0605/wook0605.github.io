#include "dynamic_blockmapping_head.h"

int main()
{
	FILE* Flash_Memory = NULL; //플래시메모리
	FILE* Trace = NULL;
	char Commend[CL]; //명령어를 받을 문자열 배열
	int LSN = 0; //추출된 값을 받을 변수
	char Write_data[513]; // 입력할 데이터
	mtable.write_count = 0;
	mtable.erase_count = 0;
	mtable.no_block = 0;
	mtable.nob = 0;
	mtable.nos = 0;

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

		if (Commend[0] == '?') // ? 문자를 발견한 경우
		{
			printf("도움말 : 입력할 수 있는 명령어는 다음과 같습니다.\n");
			printf("init X MegaByte : X MB 크기의 플래시 메모리 생성\n");
			printf("r 5 : 5번 섹터의 데이터를 읽어온다.\n");
			printf("w 5 A : 5번 섹터에 A를 적는다.\n");
			printf("printtable : 매핑 테이블을 출력한다.\n");
			printf("quit : 프로그램 종료\n");
		}

		else if (Commend[0] == 'i' && strstr(Commend, "init") != NULL) // 플래시 메모리 생성
		{
			LSN = ext_num(Commend, Write_data);//추출한 정수 변수에 입력
			init(Flash_Memory, LSN);
		}

		else if (Commend[0] == 't' && strstr(Commend, "trace") != NULL) //Trace 실행
		{
			printf("실행할 트레이스파일을 선택하세요.\n");
			printf("0 : Copy of KODAK-total\n1: kodak-pattern\n2: kodak-pattern-rule\n3: linux\n4: NIKON-SS32\n");
			fgets(Commend, CL, stdin);
			if (Commend[0] == '0')
			{
				Trace = fopen("Copy of KODAK-total.txt", "r");
				while (!feof(Trace)) //트레이스 파일을 읽어 실험함.
				{
					fgets(Commend, CL, Trace);
					LSN = ext_num(Commend, Write_data); //추출한 정수 변수에 입력
					printf("LSN : %d\n", LSN);
					memset(Write_data, 32, sizeof(char));
					Flash_write(Flash_Memory, LSN, Write_data);
				}
				printf("쓰기 카운트 : %d\t 삭제 카운트 : %d\n", mtable.write_count, mtable.erase_count);
				//fclose(Trace);
			}
			else if (Commend[0] == '1')
			{
				Trace = fopen("kodak-pattern.txt", "r");
				while (!feof(Trace)) //트레이스 파일을 읽어 실험함.
				{
					fgets(Commend, CL, Trace);
					LSN = ext_num(Commend, Write_data); //추출한 정수 변수에 입력
					printf("LSN : %d\n", LSN);
					memset(Write_data, 32, sizeof(char));
					Flash_write(Flash_Memory, LSN, Write_data);
				}
				printf("쓰기 카운트 : %d\t 삭제 카운트 : %d\n", mtable.write_count, mtable.erase_count);
				//fclose(Trace);
			}

			else if (Commend[0] == '2')
			{
				Trace = fopen("kodak-pattern-rule.txt", "r");
				while (!feof(Trace)) //트레이스 파일을 읽어 실험함.
				{
					fgets(Commend, CL, Trace);
					LSN = ext_num(Commend, Write_data); //추출한 정수 변수에 입력
					printf("LSN : %d\n", LSN);
					memset(Write_data, 32, sizeof(char));
					Flash_write(Flash_Memory, LSN, Write_data);
				}
				printf("쓰기 카운트 : %d\t 삭제 카운트 : %d\n", mtable.write_count, mtable.erase_count);
				//fclose(Trace);
			}
		
			else if (Commend[0] == '3')
			{
				Trace = fopen("linux.txt", "r");
				while (!feof(Trace)) //트레이스 파일을 읽어 실험함.
				{
					fgets(Commend, CL, Trace);
					LSN = ext_num(Commend, Write_data); //추출한 정수 변수에 입력
					printf("LSN : %d\n", LSN);
					memset(Write_data, 32, sizeof(char));
					Flash_write(Flash_Memory, LSN, Write_data);
				}
				printf("쓰기 카운트 : %d\t 삭제 카운트 : %d\n", mtable.write_count, mtable.erase_count);
				//fclose(Trace);
			}

			else if (Commend[0] == '4')
			{
				Trace = fopen("NIKON-SS32.txt", "r");
				while (!feof(Trace)) //트레이스 파일을 읽어 실험함.
				{
					fgets(Commend, CL, Trace);
					LSN = ext_num(Commend, Write_data); //추출한 정수 변수에 입력
					printf("LSN : %d\n", LSN);
					memset(Write_data, 32, sizeof(char));
					Flash_write(Flash_Memory, LSN, Write_data);
				}
				printf("쓰기 카운트 : %d\t 삭제 카운트 : %d\n", mtable.write_count, mtable.erase_count);
				//fclose(Trace);
			}
		}

		else if (Commend[0] == 'r' && strstr(Commend, "read") != NULL) // 해당 섹터의 데이터 읽어오기
		{
			LSN = ext_num(Commend, Write_data); //추출한 정수 변수에 입력
			Flash_read(Flash_Memory, LSN);
		}

		else if (Commend[0] == 'w' && strstr(Commend, "write") != NULL) // 해당 섹터에 데이터 쓰기
		{
			LSN = ext_num(Commend, Write_data); //추출한 정수 변수에 입력
			if (strlen(Write_data) == 0)
			{
				memset(Write_data, " ", sizeof(Write_data));
			}
			Flash_write(Flash_Memory, LSN, Write_data);
		}

		else if (Commend[0] == 'p' && strstr(Commend, "printtable") != NULL) //테이블 출력
		{
			print_table();
		}

		else if (Commend[0] == 'q' && strstr(Commend, "quit") != NULL) // 종료
		{
		free(mtable.table);
		free(mtable.FP_loc);
			break;
		}

		else // 잘못된 명령어를 입력했을 경우
		{
			printf("잘못된 명령어입니다.\n");
		}
	}
	return 0;
}