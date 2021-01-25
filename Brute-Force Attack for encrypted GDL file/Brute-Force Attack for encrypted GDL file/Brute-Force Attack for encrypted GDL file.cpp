// Brute-Force Attack for encrypted GDL file.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include <direct.h>

// 전부 사용하지 않는 셀로 초기화
void initIndexWindow (short *indexWindow)
{
	for (int xx = 0 ; xx < 50 ; ++xx)
		indexWindow [xx] = 0;
}

// 셀 번호를 다음 순번으로 증가시킴 (증가 성공시 0 리턴, 실패시 -1 리턴)
short nextIndexWindow (short *indexWindow, short maxDigit, short lenChars)
{
	for (int xx = 0 ; xx < maxDigit ; ++xx) {

		if (indexWindow [xx] < lenChars-1) {
			indexWindow [xx] ++;
			return 0;
		} else {
			indexWindow [xx] = 0;
			continue;
		}
	}

	return -1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//long	result_1;
	//long	result_2;
	//_finddata_t fd;

	// ---------- 전제 조건을 갖추고 있는지 확인 (1. LP_XMLConverter.exe 파일이 있는지, 2. 하위(source) 디렉토리 안에 암호화된 *.gsm 파일이 있는지)
	// "LP_XMLCOnverter.exe" 파일이 현재 디렉토리 안에 있으면 리턴 값은 0
	//result_1 = access ("LP_XMLCOnverter.exe", 0);

	// 하위 디렉토리 안에 *.gsm 파일이 있으면 리턴 값은 -1이 아님
	//result_2 = _findfirst(".\\source\\*.gsm", &fd);
	//_findclose (result_2);

	// 조건 미충족시 경고문 출력
	//if ((result_1 != 0) || (result_2 == -1)) {
	//	printf ("실행 파일은 LP_XMLConverter.exe와 동일한 경로에 있어야 합니다.\n");
	//	printf ("하위 폴더(source) 안에 암호화된 .gsm 파일을 넣어 두십시오.\n");
	//	return -1;
	//}

	// ---------- 조건 충족시 암호 풀기 시작
	short	numToCheck = 16;	// 암호 최대 글자 수
	char*	chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$%^&*()_+[]\\;',./{}|:\"<>?";	// 암호문에 들어갈 수 있는 문자들의 모음
	short	lenChars = strlen (chars);
	char	combinedStr [50];	// 결합된 암호문 문자열
	char	command [100];		// 명령어
	short	indexWindow [50];

	short	endOfWindow;	// 윈도우 끝인가?
	int xx = 0;

	initIndexWindow (indexWindow);	// 인덱스 윈도우 초기화
	strcpy_s (combinedStr, "");

	// 문자열과 시스템 명령어를 결합
	while (xx < numToCheck) {
		endOfWindow = nextIndexWindow (indexWindow, xx+1, lenChars);	// 셀 번호 증가

		// 문자열 조합
		for (int yy = 0 ; yy < xx+1 ; ++yy) {
			combinedStr [xx - yy] = chars [ indexWindow [yy] ];
		}
		combinedStr [xx+1] = '\0';

		printf ("%s\n", combinedStr);

		// 커맨드 실행
		//system (command);

		// destination 디렉토리 안의 .xml 파일 존재 여부 체크
		/*
		result_2 = _findfirst (".\\destination\\*.xml", &fd);
		_findclose (result_2);
		if (result_2 != -1) {
			printf ("암호 찾기 성공: %s", combinedStr);
			break;
		}
		*/

		// 더 이상 증가하지 않으면
		if (endOfWindow == -1) {
			xx++;
			initIndexWindow (indexWindow);
			strcpy_s (combinedStr, "");
		}
	}

	getch ();	// 화면이 바로 닫히지 않도록 함

	return 0;
}