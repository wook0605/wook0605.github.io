#include "FlashMemory_head.h"

void Flash_write(FILE* Flash_memory, int write_place, char* write_data)
{
	int ws = (write_place * SS);  // 지정한 섹터를 가르키기 위한 값
	int file_end = 0;
	char read_data[SS];
	bool OverWrite = false;

	 Flash_memory = fopen("Flash_Memory.txt","r+"); //파일을 읽기/쓰기 모드로 연다.

	if (Flash_memory == NULL)
	{
		printf("파일이 열리지 않았습니다.\n");
	}

	else
	{
		fseek(Flash_memory, 0, SEEK_END); //파일의 끝으로 간다.
		file_end = ftell(Flash_memory); //파일이 가지고 있는 문자의 길이를 잰다.
		rewind(Flash_memory);// 파일 포인터를 다시 맨앞으로

		if (ws == 0) //첫 섹터에 쓰는 경우
		{
			fgets(read_data, SS, Flash_memory); // 데이터가 있는지 확인하기 위해 데이터 읽어오기

			for (int i = 0; i < SS; i++)
			{
				if (read_data[i] != 32 && read_data[i] != 0) // 스페이스바와 NULL문자 외에 데이터 존재시 오버라이트.
				{
					OverWrite = true;
				}
			}

			if (OverWrite) //오버라이트 에러 일때
			{
				printf("OverWrite Error!!\n"); //오버라이트 에러 출력
			}

			else //데이터를 쓸 수 있을 때
			{
				rewind(Flash_memory);
				fputs(write_data, Flash_memory); //바로 입력
				printf("Done!\n");
			}
		}

		else //첫 섹터가 아닌 경우
		{
			if (file_end / 512 <= write_place) //영역을 초과해서 읽는 경우
			{
				printf("영역을 초과했습니다.\n");
			}

			else
			{
				fseek(Flash_memory, ws, SEEK_SET); // 섹터 찾기
				fgets(read_data, SS, Flash_memory);// 데이터가 있는지 없는지 검사하기 위해 읽기

				for (int i = 0; i < SS; i++)
				{
					if (read_data[i] != 32 && read_data[i] != 0) // 스페이스바와 NULL문자 외에 데이터 존재시 오버라이트.
					{
						OverWrite = true;
					}
				}

				if (OverWrite) //오버라이트 에러일때
				{
					printf("OverWrite error!\n"); // 오버라이트 에러 출력
				}

				else // 데이터를 쓸 수 있을때
				{
					rewind(Flash_memory);
					fseek(Flash_memory, ws, SEEK_SET);
					fputs(write_data, Flash_memory);
					printf("Done!\n");
				}
			}
		}

		fclose(Flash_memory); //파일을 닫는다.
	}

	

}