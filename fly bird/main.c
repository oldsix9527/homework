
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<windows.h>


int main()
{
	//��ҳ�����
	printf("\t\t��ӭ����fly birdС��Ϸ\n");
	printf("\t\t��Ϊ��Ϊ��Ϸ��֪:\n");
	printf("\t\t1.����Ҫ�ÿո�ٿ�С���Ծһ����һ������\n");
	printf("\t\t2.�ɳ������ײ�����Ӷ���ʧ��\n");
	printf("\t\t3.���Խ�� ����Խ��\n");
	printf("\n");
	printf("\t\t���뿪ʼ������������:Y/N\n");
	printf("\t\t���������:");


	//��ҳ��ѡ������
	char ch;
	scanf("%c", &ch);
	while (ch != 'Y' || ch != 'N')
	{
		printf("\t\t����������������������:");

		scanf("%c", ch);
		_getch();
	}
	if (ch == 'Y')
	{

	}
	else if (ch == 'N')

		return 0;
}
