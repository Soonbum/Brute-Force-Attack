// Brute-Force Attack for encrypted GDL file.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <conio.h>
#include <direct.h>

// ���� ������� �ʴ� ���� �ʱ�ȭ
void initIndexWindow (short *indexWindow)
{
	for (int xx = 0 ; xx < 50 ; ++xx)
		indexWindow [xx] = 0;
}

// �� ��ȣ�� ���� �������� ������Ŵ (���� ������ 0 ����, ���н� -1 ����)
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

	// ---------- ���� ������ ���߰� �ִ��� Ȯ�� (1. LP_XMLConverter.exe ������ �ִ���, 2. ����(source) ���丮 �ȿ� ��ȣȭ�� *.gsm ������ �ִ���)
	// "LP_XMLCOnverter.exe" ������ ���� ���丮 �ȿ� ������ ���� ���� 0
	//result_1 = access ("LP_XMLCOnverter.exe", 0);

	// ���� ���丮 �ȿ� *.gsm ������ ������ ���� ���� -1�� �ƴ�
	//result_2 = _findfirst(".\\source\\*.gsm", &fd);
	//_findclose (result_2);

	// ���� �������� ��� ���
	//if ((result_1 != 0) || (result_2 == -1)) {
	//	printf ("���� ������ LP_XMLConverter.exe�� ������ ��ο� �־�� �մϴ�.\n");
	//	printf ("���� ����(source) �ȿ� ��ȣȭ�� .gsm ������ �־� �νʽÿ�.\n");
	//	return -1;
	//}

	// ---------- ���� ������ ��ȣ Ǯ�� ����
	short	numToCheck = 16;	// ��ȣ �ִ� ���� ��
	char*	chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789~!@#$%^&*()_+[]\\;',./{}|:\"<>?";	// ��ȣ���� �� �� �ִ� ���ڵ��� ����
	short	lenChars = strlen (chars);
	char	combinedStr [50];	// ���յ� ��ȣ�� ���ڿ�
	char	command [100];		// ��ɾ�
	short	indexWindow [50];

	short	endOfWindow;	// ������ ���ΰ�?
	int xx = 0;

	initIndexWindow (indexWindow);	// �ε��� ������ �ʱ�ȭ
	strcpy_s (combinedStr, "");

	// ���ڿ��� �ý��� ��ɾ ����
	while (xx < numToCheck) {
		endOfWindow = nextIndexWindow (indexWindow, xx+1, lenChars);	// �� ��ȣ ����

		// ���ڿ� ����
		for (int yy = 0 ; yy < xx+1 ; ++yy) {
			combinedStr [xx - yy] = chars [ indexWindow [yy] ];
		}
		combinedStr [xx+1] = '\0';

		printf ("%s\n", combinedStr);

		// Ŀ�ǵ� ����
		//system (command);

		// destination ���丮 ���� .xml ���� ���� ���� üũ
		/*
		result_2 = _findfirst (".\\destination\\*.xml", &fd);
		_findclose (result_2);
		if (result_2 != -1) {
			printf ("��ȣ ã�� ����: %s", combinedStr);
			break;
		}
		*/

		// �� �̻� �������� ������
		if (endOfWindow == -1) {
			xx++;
			initIndexWindow (indexWindow);
			strcpy_s (combinedStr, "");
		}
	}

	getch ();	// ȭ���� �ٷ� ������ �ʵ��� ��

	return 0;
}