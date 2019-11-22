#include "VideoStore_head.h"

void Save_UsData(FILE* UsDB, Us_info* Ushead) //데이터를 저장하는 함수
{
	UsDB = fopen("User_DB.txt", "w"); // 사용자 데이터를 저장하기 위해쓰기 모드로 파일을 연다.

	if (UsDB == NULL) // 파일이 열리지 않은 경우
	{
		printf("파일이 열리지 않았습니다.\n");
	}

	else
	{
		for (Ushead; Ushead != NULL; Ushead = Ushead->next) //모든 데이터를 파일로 저장하기 위해 노드 순환
		{
			fwrite(Ushead, sizeof(Us_info), 1, UsDB);//데이터를 입력한다.
			fprintf(UsDB, "\n");//개행하여 다음줄에 데이터가 입력되도록 함y
		}
	}
	fclose(UsDB);//파일 닫기

	
}

void Save_VdData(FILE* VdDB, Vd_info* Vdhead) //비디오 데이터를 저장하는 함수
{
	VdDB = fopen("Video_DB.txt", "w");  // 비디오 데이터를 저장하기 위해쓰기 모드로 파일을 연다.

	if (VdDB == NULL) // 파일이 열리지 않을 경우
	{
		printf("파일이 열리지 않았습니다.\n");
		
	}

	else //파일이 열린 경우
	{
		for (Vdhead; Vdhead != NULL; Vdhead = Vdhead->next) //모든 데이터를 파일로 저장하기 위해 노드 순환
		{
			fwrite(Vdhead, sizeof(Vd_info), 1, VdDB); //데이터를 입력한다.
			fprintf(VdDB, "\n"); //개행하여 다음줄에 데이터가 입력되도록 함
		}
	}
	fclose(VdDB); //파일 닫기
}

void Load_Usdata(FILE* UsDB, Us_info* Ushead) //데이터를 불러오는 함수
{
	int size; //파일의 크기를 저장하는 변수

	UsDB = fopen("User_DB.txt", "r"); //리스트에 유저 데이터를 불러오기 위해 파일을 읽기 모드로 연다.

	if (UsDB == NULL) //파일이 열리지 않았을 때
	{
		printf("파일이 열리지 않았습니다.\n"); //에러 메시지 출력
		return; //기능 종료
	}

	else
	{
		fseek(UsDB,0, SEEK_END); //파일이 비었는지 확인하기 위해 파일의 끝으로 보낸다.
		size = ftell(UsDB); //커서가 가진 값을 반환
		if (size == 0) //파일이 가진 데이터가 없을 때
		{
			printf("불러올 데이터가 없습니다.\n");
		}

		else //파일에 데이터가 있을 때
		{
			rewind(UsDB); // 파일의 커서를 맨 앞으로 돌린다.
			while (feof(UsDB) == 0) //파일의 끝까지 반복한다.
			{
				Us_info* up = (Us_info*)malloc(sizeof(Us_info)); //유저 데이터를 저장할 노드 생성
				fread(up, sizeof(Us_info), 1, UsDB); //데이터 읽기
				fscanf(UsDB, "\n"); //다음줄을 읽기 위한 개행
				Ushead->next = up; //노드 연결
				Ushead = Ushead->next; //노드 연결
				up->next = NULL; 
			}
		}
	}

	fclose(UsDB); //사용자 데이터 저장파일 닫기
}

void Load_Vddata(FILE* VdDB, Vd_info* Vdhead) //비디오 데이터를 불러오는 함수
{
	int size; //데이터의 크기 저장하는 함수

	VdDB = fopen("Video_DB.txt", "r"); //리스트에 비디오 데이터를 불러오기 위해 파일을 읽기 모드로 연다.

	if (VdDB == NULL) //파일이 열리지 않은 경우
	{
		printf("파일이 열리지 않았습니다.\n");
		return;//기능 종료
	}

	else
	{
		fseek(VdDB, 0, SEEK_END); //파일이 비었는지 확인하기 위해 파일의 끝으로 보낸다.
		size = ftell(VdDB);//커서가 가진 값을 반환
		if (size == 0) //파일이 가진 데이터가 없을 때
		{
			printf("불러올 데이터가 없습니다.\n");
		}

		else //파일이 가진 데이터가 있을 때
		{
			rewind(VdDB); //파일의 커서를 맨 앞으로 돌린다.
			while (feof(VdDB) == 0)//파일의 끝까지 반복한다.
			{
				Vd_info* vp = (Vd_info*)malloc(sizeof(Vd_info));//비디오 데이터를 저장할 노드를 생성한다.
				fread(vp, sizeof(Vd_info), 1, VdDB); //데이터 읽어서 노드에 삽입
				fscanf(VdDB, "\n"); //다음 줄을 읽기 위한 개행
				Vdhead->next = vp; //노드 연결
				Vdhead = Vdhead->next; //노드 연결
				vp->next = NULL;
			}
		}

	}
	fclose(VdDB);//비디오데이터 저장 파일 닫기
}


void free_Usmem(Us_info* Ushead) //유저 노드 해제
{
	Us_info* Usremove;
	while (Ushead != NULL) //노드가 존재하지 않을 때 까지 반복
	{
		Usremove = Ushead->next;
		Ushead->next = NULL;
		free(Usremove); //노드를 삭제한다.
		Ushead = Ushead->next; //다음 노드로 이동
	}
}

void free_Vdmem(Vd_info* Vdhead) // 비디오 노드 해제
{
	Vd_info* Vdremove;
	while (Vdhead != NULL) //노드가 존재하지 않을 때 까지 반복
	{
		Vdremove = Vdhead->next;
		Vdhead->next = NULL;
		free(Vdremove); //노드를 삭제한다.
		Vdhead = Vdhead->next; //다음 노드로 이동
	}
}